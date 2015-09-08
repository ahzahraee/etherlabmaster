/*
 +-------------------------------------------------------------------------+
 |                                                                         |
 |     Projet  :   Ethercat                                                |
 |                                                                         |
 |     Module  :   Eth_Igh_Interface.h                                       |
 |     Version :   1.0                                                   |
 |                                                                         |
 |     Auteur  :   Ali HASSAN ZAHRAEE                                             |
 |     Date    :   07/07/2015                                              |
 |                                                                         |
 +-------------------------------------------------------------------------+
 |                                                                         |
 |     Description  :  Interface Ethercat en utilisant la pile Igh         |
 |     																	   |
 +-------------------------------------------------------------------------+
 |                                                                         |
 |     Historique   :                                                      |
 |     -----------                                                         |
 |                                                                         |
 +-------------------------------------------------------------------------+
 */

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

/****************************************************************************/

#include "Eth_Igh_Interface.h"

/****************************************************************************/


// EtherCAT
static ec_master_t* master = NULL;
ec_master_state_t master_state = {};

static ec_domain_t* domains[MAX_DOMAINS] = {NULL, NULL, NULL, NULL};
static ec_domain_state_t domain_states[MAX_DOMAINS] = {{}, {}, {}, {}};
//static uint8_t* domains_pd[MAX_DOMAINS] = {NULL, NULL, NULL, NULL};
const ec_pdo_entry_reg_t* domains_regs[4];

static struct sigaction sa;
static struct itimerval tv;
static struct timeval ct;


/****************************************************************************/


static void signal_handler(int signum) {
    switch (signum) {
        case SIGALRM:
            ;
            break;
    }
}


unsigned int Eth_Print_Time() {
    gettimeofday(&ct, NULL);
    printf("%u.%06u\n", ct.tv_sec, ct.tv_usec);
    return 0;
}

int Eth_Initialise_Ethercat(		unsigned int	Master_Index,			/* [in]  Index du maitre à initialiser; 0 si un seul master							*/
									EC_T_DWORD	Avec_DCM	)				/* [in]  avec ou sans DCM															*/
{
    printf("\t Creating Ethercat master...\n");
    master = ecrt_request_master(Master_Index);
    if (!master) {
    	fprintf(stderr, "Creating Ethercat master %d failed!", Master_Index);
        return -1;
    }
    else
    	return 0;
}

int Eth_Initialise_Environnement(	unsigned int Master_Index,		/* [in]  Pointer to Ethercat master		*/
									unsigned int priority,				/* [in]	 Process priority				*/
									unsigned int period_s,				/* [in] Cyclic task period in seconds	*/
									unsigned int period_us,				/* [in] Cyclic task period in microseconds	*/
									EC_T_DWORD	Num_Domains,			/* [in]  Number of domains 				*/
									const ec_pdo_entry_reg_t domain_0_regs[],
									const ec_pdo_entry_reg_t domain_1_regs[],
									const ec_pdo_entry_reg_t domain_2_regs[],
									const ec_pdo_entry_reg_t domain_3_regs[] )
{
	int domain_index;
	pid_t pid;

	domains_regs[0] = domain_0_regs;
	domains_regs[1] = domain_1_regs;
	domains_regs[2] = domain_2_regs;
	domains_regs[3] = domain_3_regs;

    printf("\t Creating domains...\n");
	if (Num_Domains < MAX_DOMAINS) {
		// Creating domains
		for (domain_index = 0; domain_index < Num_Domains; domain_index++) {
			domains[domain_index] = ecrt_master_create_domain(master);
			if (!domains[domain_index]) {
				return -1;
			}
		}

	    printf("\t Setting task priority...\n");
	    pid = getpid();
	    if (setpriority(PRIO_PROCESS, pid, priority))
	        fprintf(stderr, "Warning: Failed to set priority: %s\n", strerror(errno));

	    printf("\t Configuring timer...\n");
		// setting up signal handler for timing
	    sa.sa_handler = signal_handler;
	    sigemptyset(&sa.sa_mask);
	    sa.sa_flags = 0;
	    if (sigaction(SIGALRM, &sa, 0)) {
	        fprintf(stderr, "Failed to install signal handler!\n");
	        return -1;
	    }

	    // setting up timer values for cyclic task
		tv.it_interval.tv_sec = period_s;
		tv.it_interval.tv_usec = period_us;
		tv.it_value.tv_sec = period_s;		// First timer tick will be delayed for 1 period from timer start
		tv.it_value.tv_usec = period_us;
	}
	else {
		fprintf(stderr, "Number of domains must be smaller than %d. Creating Ethercat domains failed!", MAX_DOMAINS);
        return -1;
	}
}

ec_slave_config_t* Eth_Enregistre_un_Esclave(		 ec_sync_info_t syncs[],
											 	 	 uint16_t alias, uint16_t position,
											 	 	 uint32_t vendor_id, uint32_t product_code ) {

	ec_slave_config_t *slave_config;
	slave_config = ecrt_master_slave_config(master, alias, position, vendor_id, product_code );
	if (slave_config == NULL) {
		fprintf(stderr, "Failed to get slave configuration.\n");
		return NULL;
	}

	return slave_config;
}

int Eth_Configurer_un_Esclave(		ec_sync_info_t syncs[],
									ec_slave_config_t*	slave_config	) {

	return ecrt_slave_config_pdos(slave_config, EC_END, syncs);
}

ec_sdo_request_t* Eth_Create_SDO_Channel(		ec_slave_config_t *sc,
								uint16_t index,
								uint8_t subindex,
								size_t size,
								uint32_t timeout)
{
	ec_sdo_request_t *sdo = NULL;

    printf("Creating SDO channel %d : %d...\n", index, subindex);
    sdo = ecrt_slave_config_create_sdo_request(sc, index, subindex, size);

    if (!sdo) {
        fprintf(stderr, "Failed to create SDO request.\n");
        return NULL;
    }
    ecrt_sdo_request_timeout(sdo, timeout); // set the timeout (in ms) for the sdo request

    return sdo;
}

int Eth_Start_Ethercat (		EC_T_DWORD	Num_Domains		)			/* [in]  Number of domains 				*/
{
	int domain_index;

	printf("Starting Ethercat...\n");
	// Configuring domains i.e. associating slaves' PDO entries with domains
	if (ecrt_domain_reg_pdo_entry_list(domains[domain_index], domains_regs[domain_index])) {
		fprintf(stderr, "PDO entry registration failed!\n");
		return -1;
	}

	if (ecrt_master_activate(master)) {
		fprintf(stderr, "Starting Ethercat master failed.\n");
		return;
	}
	else {
		for (domain_index = 0; domain_index < Num_Domains; domain_index++) {
			if (!(domains_pd[domain_index] = ecrt_domain_data(domains[domain_index]))) {
				fprintf(stderr, "Getting mapped domain process data memory failed.\n");
				return;
			}
		}
	}
	return 0;
}

int Eth_Add_Cyclic_Func (		void (*Fonction_Cyclique)()	)		/* [in]  Pointer to cyclic function 	*/
{
	// starting cyclic task timer
	if (setitimer(ITIMER_REAL, &tv, NULL)) {
		fprintf(stderr, "Failed to start timer: %s\n", strerror(errno));
		return 1;
	}
	else {
		printf("Ethercat Timer Set.\n");
	}

    while (1) {
        pause();

        Fonction_Cyclique();
    }
	return 0;
}

void Eth_Read_PDO( unsigned int Domain_Index ) {
	ecrt_master_receive(master);
	ecrt_domain_process(domains[Domain_Index]);
}


void Eth_Write_PDO( unsigned int Domain_Index ) {
    ecrt_domain_queue(domains[Domain_Index]);
    ecrt_master_send(master);
}

uint8_t* Eth_Read_SDO(ec_sdo_request_t *sdo_server)
{
	uint8_t *data = NULL;
	ec_request_state_t state;

	state =	ecrt_sdo_request_state(sdo_server);
	switch (state) {
		case EC_REQUEST_UNUSED: //
			//ecrt_sdo_request_index(sdo_server, 0xf050, 0);
			ecrt_sdo_request_read(sdo_server); // trigger read
			break;
		case EC_REQUEST_BUSY:
			fprintf(stderr, "Still busy...\n");
			break;
		case EC_REQUEST_ERROR:
			fprintf(stderr, "Failed to read SDO!\n");
			break;
	}
	if (state == EC_REQUEST_UNUSED) {
		state =	ecrt_sdo_request_state(sdo_server);
		switch (state) {
			case EC_REQUEST_SUCCESS: // server not used
				data = ecrt_sdo_request_data(sdo_server);
				break;
			case EC_REQUEST_BUSY:
				break;
			case EC_REQUEST_ERROR:
				fprintf(stderr, "Failed to read SDO!\n");
				break;
		}
		while (state == EC_REQUEST_BUSY) {
			fprintf(stderr, "SDO server busy...\n");
			usleep(1000000); // wait for 1000 ms
			state =	ecrt_sdo_request_state(sdo_server);
			if (state == EC_REQUEST_SUCCESS) {
				data = ecrt_sdo_request_data(sdo_server);
				break;
			}
		}
	}

    return data;
}

void read_sdo(ec_sdo_request_t *sdo)
{
    switch (ecrt_sdo_request_state(sdo)) {
        case EC_REQUEST_UNUSED: // request was not used yet
            ecrt_sdo_request_read(sdo); // trigger first read
            break;
        case EC_REQUEST_BUSY:
            fprintf(stderr, "Still busy...\n");
            break;
        case EC_REQUEST_SUCCESS:
            fprintf(stderr, "SDO value: 0x%04X\n",
                    EC_READ_U16(ecrt_sdo_request_data(sdo)));
            ecrt_sdo_request_read(sdo); // trigger next read
            break;
        case EC_REQUEST_ERROR:
            fprintf(stderr, "Failed to read SDO!\n");
            ecrt_sdo_request_read(sdo); // retry reading
            break;
    }
}

int Eth_Read_SDO_Master(	uint16_t 	slave_position,
							uint16_t 	index,
							uint8_t 	subindex,
							uint8_t * 	target,
							size_t 	target_size,
							size_t * 	result_size,
							uint32_t * 	abort_code ) {

	return ecrt_master_sdo_upload(	master,
									slave_position,
									index,
									subindex,
									target,
									target_size,
									result_size,
									abort_code);

}

//
//int Eth_Write_SDO(		ec_sdo_request_t *sdo_server,
//						uint8_t *data)
//{
//	int sdo_write_ret;
//
//	size_t size = ecrt_sdo_request_data_size(sdo_server);
//
//    switch (ecrt_sdo_request_state(sdo_server)) {
//        case EC_REQUEST_UNUSED: // server was not used yet
//            ecrt_sdo_request_write(sdo_server); // trigger first write
//            break;
//        case EC_REQUEST_BUSY:
//            fprintf(stderr, "Still busy...\n");
//            break;
//        case EC_REQUEST_SUCCESS:
//        	if(!(sdo_write_ret = ec_sdo_request_copy_data(sdo_server, data, size))) {
//        		printf("Failed to write to SDO channel.\n");
//        		return sdo_write_ret;
//    		}
//        	ecrt_sdo_request_write(sdo_server); // trigger next read
//            break;
//        case EC_REQUEST_ERROR:
//            fprintf(stderr, "Failed to read SDO!\n");
//            ecrt_sdo_request_write(sdo_server); // retry reading
//            break;
//    }
//
//    return 0;
//}

void check_domain_state(unsigned int domain_index) {
	ec_domain_state_t ds;

	ecrt_domain_state(domains[domain_index], &ds);

	if (ds.working_counter != domain_states[domain_index].working_counter)
		printf("Domain1: WC %u.\n", ds.working_counter);
	if (ds.wc_state != domain_states[domain_index].wc_state)
		printf("Domain1: State %u.\n", ds.wc_state);

	domain_states[domain_index] = ds;
}

void check_master_state(void)
{
    ec_master_state_t ms;

    ecrt_master_state(master, &ms);

    if (ms.slaves_responding != master_state.slaves_responding)
        printf("%u slave(s).\n", ms.slaves_responding);
    if (ms.al_states != master_state.al_states)
        printf("AL states: 0x%02X.\n", ms.al_states);
    if (ms.link_up != master_state.link_up)
        printf("Link is %s.\n", ms.link_up ? "up" : "down");

    master_state = ms;
}


void check_slave_config_state(char *slavename, ec_slave_config_t *slaveconfig, ec_slave_config_state_t *slaveconfig_state)
{
    ec_slave_config_state_t s;

    ecrt_slave_config_state(slaveconfig, &s);

    if (s.al_state != slaveconfig_state->al_state)
        printf("%s : State 0x%02X.\n", slavename, s.al_state);
    if (s.online != slaveconfig_state->online)
        printf("%s : %s.\n", slavename, s.online ? "online" : "offline");
    if (s.operational != slaveconfig_state->operational)
        printf("%s : %soperational.\n",
        		slavename, s.operational ? "" : "Not ");

    *slaveconfig_state = s;
}
