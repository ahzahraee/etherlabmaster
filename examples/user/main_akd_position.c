/*
 * main_akd_position.c
 *
 *  Created on: Jul 17, 2015
 *      Author: AHZ

 Prerequises: the servo drive is already configured with AKD Workbench:

 DRV.TYPE 2
 DRV.CMDSOURCE 1
 DRV.OPMODE 0
 FBUS.PARAM04 1
 FBUS.PLLSAMPLEPERIOD 4

 Note: To run this example at a lower frequency (for example 100 Hz), disable
       fieldbus supervision (FBUS.PARAM04 0) to avoid permanent F125 fault.
*/

#include "stdio.h"
#include "Eth_Igh_Interface.h"
#include "cstruct_akd_position.h"

/* 						Application parameters						 */
// cyclic task period
#define period_sec	0
#define period_usec	1000
#define TASK_PERIODE	(period_sec + period_usec*1e-6)
#define TASK_FREQUENCY 1/TASK_PERIODE
#define TIMEOUT_CLEAR_ERROR  (1*TASK_FREQUENCY) /* clearing error timeout */
#define TARGET_POSITION      0

#define AKD_STS_MASK       0xAFF  /* mask to remove manufacturer special bits and target_reached */
#define AKD_STS_SWION_DIS  0x250  /* switched on disabled */
#define AKD_STS_RDY_SWION  0x231  /* ready to switch on   */
#define AKD_STS_SWION_ENA  0x233  /* switched on enabled  */
#define AKD_STS_ERROR      0x218  /* error                */

#define AKD_CMD_ENA_QSTOP  0x00   /* enable quick stop   */
#define AKD_CMD_DIS_QSTOP  0x06   /* disable quick stop  */
#define AKD_CMD_ENA_SWION  0x07   /* enable switched  on */
#define AKD_CMD_ENA_OP     0x0F   /* enable operation    */
#define AKD_CMD_CLR_ERROR  0x80   /* clear error         */

/*					 Ethercat					 */

#define n_domains 1
#define AKDPos  0, 0	// Slaves position on the bus
#define Kollmorgen_AKD 	AKD_VendorId, AKD_Pxxx_06_NBCC_E000_ProductCode   //Vendor ID, Product Code
ec_slave_config_t *sc_akd = NULL;
ec_slave_config_state_t s_akd = {};

/* PDO entries offsets */
static struct {
    unsigned int ctrl_word;
    unsigned int target_position;
    unsigned int status_word;
    unsigned int act_velocity;
    unsigned int act_position;
} offset;

const static ec_pdo_entry_reg_t domain_0_regs[] = {
    { AKDPos, Kollmorgen_AKD, 0x6040, 0, &offset.ctrl_word },
    { AKDPos, Kollmorgen_AKD, 0x607A, 0, &offset.target_position },
    { AKDPos, Kollmorgen_AKD, 0x6041, 0, &offset.status_word },
    { AKDPos, Kollmorgen_AKD, 0x606C, 0, &offset.act_velocity },
    { AKDPos, Kollmorgen_AKD, 0x6063, 0, &offset.act_position},
    {}
};


void cyclic_task()
{
    static unsigned int timeout_error = 0;
    static uint16_t command = AKD_CMD_ENA_QSTOP;
    static int32_t target_position = TARGET_POSITION;

    uint16_t status;    /* DS402 status register, without manufacturer bits */
    float act_velocity; /* actual velocity in rpm */
    int act_position; /* actual position in encoder unit */

	Eth_Read_PDO(0);

	check_domain_state(0);
	check_master_state();
	check_slave_config_state("AKD", sc_akd, &s_akd);

	if (s_akd.operational) {
	    /* read inputs */
	    status = EC_READ_U16(domains_pd[0] + offset.status_word) & AKD_STS_MASK;
	    act_velocity = EC_READ_S32(domains_pd[0] + offset.act_velocity)/1000.0;
	    act_position = EC_READ_S32(domains_pd[0] + offset.act_position);

	    /* DS402 CANopen over EtherCAT status machine */
	    if (status == AKD_STS_SWION_DIS && command != AKD_CMD_DIS_QSTOP) {
		printf( "AKD: disable quick stop\n" );
	        command = AKD_CMD_DIS_QSTOP;

	    } else if (status == AKD_STS_RDY_SWION && command != AKD_CMD_ENA_SWION ) {
		printf("AKD: enable switch on\n" );
	        command = AKD_CMD_ENA_SWION;

	    } else if ( status == AKD_STS_SWION_ENA  && command != AKD_CMD_ENA_OP ) {
		printf("AKD: start operation\n" );
	        command = AKD_CMD_ENA_OP;

	    } else if ( status == AKD_STS_ERROR && command != AKD_CMD_CLR_ERROR ) {
		if ( timeout_error ) {
		    if (timeout_error == TIMEOUT_CLEAR_ERROR) {
			printf( "AKD: ERROR, wait for timeout\n" );
		    }
		    timeout_error--;
		} else {
		    timeout_error = TIMEOUT_CLEAR_ERROR;
		    command = AKD_CMD_CLR_ERROR;
		    printf( "AKD: clear error now\n" );
		}
	    } else {
		/* print actual values, once per second */
		static time_t prev_second = 0;
		time_t now = time(NULL);
		if ( now != prev_second ) {
		    printf( "AKD: actual velocity = %.1f rpm, actual position = %d, target_pos = %d\n",
			    act_velocity, act_position, target_position );
		    prev_second = now;
		}
	    }

	    /* write output */
	    EC_WRITE_S32( domains_pd[0] + offset.target_position, target_position );
	    EC_WRITE_U16( domains_pd[0] + offset.ctrl_word, command );
	}

	Eth_Write_PDO(0);
}


int main(int argc, char **argv) {

    printf("Initialising Ethercat master...\n");
    Eth_Initialise_Ethercat(0, 0);

    printf("Configuring Ethercat master...\n");
    Eth_Initialise_Environnement(0, -19, period_sec, period_usec, n_domains, domain_0_regs, NULL, NULL, NULL);

    sc_akd = Eth_Enregistre_un_Esclave(akd_syncs, AKDPos, Kollmorgen_AKD);

    /* Configure AKD flexible PDO */
    printf("Configuring AKD with flexible PDO...\n");
    /* Clear RxPdo */
    ecrt_slave_config_sdo8( sc_akd, 0x1C12, 0, 0 ); /* clear sm pdo 0x1c12 */
    ecrt_slave_config_sdo8( sc_akd, 0x1600, 0, 0 ); /* clear RxPdo 0x1600 */
    ecrt_slave_config_sdo8( sc_akd, 0x1601, 0, 0 ); /* clear RxPdo 0x1601 */
    ecrt_slave_config_sdo8( sc_akd, 0x1602, 0, 0 ); /* clear RxPdo 0x1602 */
    ecrt_slave_config_sdo8( sc_akd, 0x1603, 0, 0 ); /* clear RxPdo 0x1603 */

    /* Define RxPdo */
    ecrt_slave_config_sdo32( sc_akd, 0x1600, 1, 0x60400010 ); /* 0x6040:0/16bits, control word */
    ecrt_slave_config_sdo32( sc_akd, 0x1600, 2, 0x607A0020 ); /* 0x60C1:1/32bits target position*/
    ecrt_slave_config_sdo8( sc_akd, 0x1600, 0, 2 ); /* set number of PDO entries for 0x1600 */

    ecrt_slave_config_sdo16( sc_akd, 0x1C12, 1, 0x1600 ); /* list all RxPdo in 0x1C12:1-4 */
    ecrt_slave_config_sdo8( sc_akd, 0x1C12, 0, 1 ); /* set number of RxPDO */

    /* Clear TxPdo */
    ecrt_slave_config_sdo8( sc_akd, 0x1C13, 0, 0 ); /* clear sm pdo 0x1c13 */
    ecrt_slave_config_sdo8( sc_akd, 0x1A00, 0, 0 ); /* clear TxPdo 0x1A00 */
    ecrt_slave_config_sdo8( sc_akd, 0x1A01, 0, 0 ); /* clear TxPdo 0x1A01 */
    ecrt_slave_config_sdo8( sc_akd, 0x1A02, 0, 0 ); /* clear TxPdo 0x1A02 */
    ecrt_slave_config_sdo8( sc_akd, 0x1A03, 0, 0 ); /* clear TxPdo 0x1A03 */

    /* Define TxPdo */
    ecrt_slave_config_sdo32( sc_akd, 0x1A00, 1, 0x60410010 ); /* 0x6041:0/16bits, status word */
    ecrt_slave_config_sdo8( sc_akd, 0x1A00, 0, 1 ); /* set number of PDO entries for 0x1A00 */

    ecrt_slave_config_sdo32( sc_akd, 0x1A01, 1, 0x606C0020 );  /* 0x606c:0/32bits, act velocity */
    ecrt_slave_config_sdo32( sc_akd, 0x1A01, 2, 0x60630020 );  /* 0x6063:0/32bits, act position */
    ecrt_slave_config_sdo8( sc_akd, 0x1A01, 0, 2 ); /* set number of PDO entries for 0x1A01 */

    ecrt_slave_config_sdo16( sc_akd, 0x1C13, 1, 0x1A00 ); /* list all TxPdo in 0x1C13:1-4 */
    ecrt_slave_config_sdo16( sc_akd, 0x1C13, 2, 0x1A01 ); /* list all TxPdo in 0x1C13:1-4 */
    ecrt_slave_config_sdo8( sc_akd, 0x1C13, 0, 2 ); /* set number of TxPDO */


    /* set operation mode */
    ecrt_slave_config_sdo8( sc_akd, 0x6060, 0, 8 ); /* set cyclic synchronous position mode (csp) */


    if ( Eth_Configurer_un_Esclave(akd_syncs, sc_akd) ) {
    	printf("Failed to configure slave PDOs.\n");
    	exit( EXIT_FAILURE );
    }

    Eth_Start_Ethercat(n_domains);

    Eth_Add_Cyclic_Func (cyclic_task);
}
