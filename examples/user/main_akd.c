/*
 * main_epos3.c
 *
 *  Created on: Jul 17, 2015
 *      Author: AHZ
 */

#include "stdio.h"

#include "Eth_Igh_Interface.h"

#include "cstruct_akd_new.h"

#define n_domains 1

//#define SDO

// Slaves position on the bus
#define AKDPos  0, 0

//Vendor ID, Product Code
#define KOLLMORGEN_AKD 	AKD_VendorId, AKD_Pxxx_06_NBCC_E000_ProductCode

#ifdef SDO
ec_sdo_request_t *akd_sdo_1;
ec_sdo_request_t *akd_sdo_2;
#endif

ec_slave_config_t *sc_akd = NULL;
ec_slave_config_state_t s_akd = {};

// PDO entries' byte offset in the process data
static unsigned int off_akd_ctrlword;
static unsigned int off_akd_status;
static unsigned int off_akd_analog_in;
static unsigned int off_akd_digital_in;
static unsigned int off_akd_act_velocity;
static unsigned int off_akd_act_pos;

// process data

const static ec_pdo_entry_reg_t domain_0_regs[] = {
//    {AKDPos, KOLLMORGEN_AKD, 0x6040, 0, &off_akd_ctrlword},
//    {AKDPos, KOLLMORGEN_AKD, 0x6041, 0, &off_akd_status},
//    {AKDPos, KOLLMORGEN_AKD, 0x3470, 4, &off_akd_analog_in},
//    {AKDPos, KOLLMORGEN_AKD, 0x60FD, 0, &off_akd_digital_in},
//    {AKDPos, KOLLMORGEN_AKD, 0x606C, 0, &off_akd_act_velocity},
//    {AKDPos, KOLLMORGEN_AKD, 0x6063, 0, &off_akd_act_pos},
    {}
};

// cyclic task period
#define period_sec	1
#define period_usec	0

static unsigned int blink = 0;

void cyclic_task()
{
	Eth_Read_PDO(0);

	check_domain_state(0);
	check_master_state();
	check_slave_config_state("AKD", sc_akd, &s_akd);

	if (s_akd.operational) {
	       printf("AKD act_velocity = %8.3f rpm, act_pos = %d , %10.3f\n",
		   EC_READ_S32(domains_pd[0] + off_akd_act_velocity)/1000.0,
		   EC_READ_S32(domains_pd[0] + off_akd_act_pos),
		   EC_READ_S32(domains_pd[0] + off_akd_act_pos)/16.0
	       );

	       printf( "AKD analog in = %x %3.3f V, DigitalIn = %x\n",
		   EC_READ_S16(domains_pd[0] + off_akd_analog_in),
		   EC_READ_S16(domains_pd[0] + off_akd_analog_in)*5.0/0x3300,
		   EC_READ_U32(domains_pd[0] + off_akd_digital_in)
	       );
	}

	Eth_Write_PDO(0);
}


int main(int argc, char **argv) {

	uint8_t *data_sdo_1 = NULL;
	uint8_t *data_sdo_2 = NULL;
	//size_t data_sdo_1_size = 1;

    printf("Initialising Ethercat master...\n");
    Eth_Initialise_Ethercat(0, 0);

    printf("Configuring Ethercat master...\n");
    Eth_Initialise_Environnement(0, -19, period_sec, period_usec, n_domains, domain_0_regs, NULL, NULL, NULL);

    sc_akd = Eth_Enregistre_un_Esclave(akd_syncs, AKDPos, KOLLMORGEN_AKD);

//    epos3_sdo_1 = Eth_Create_SDO_Channel(sc_epos3, 0x6040, 0, 2, 500);
//    epos3_sdo_2 = Eth_Create_SDO_Channel(sc_epos3, 0xf050, 2, 4, 500);

    Eth_Start_Ethercat(n_domains);

    //read sdo
/*
    data_sdo_1 = Eth_Read_SDO( epos3_sdo_1 );

    if (!data_sdo_1)
    	printf("Reading SDO 1 failed.\n");
    else
        printf("SDO1 = %d\n", data_sdo_1[0]);
*/

//    Eth_Read_SDO_Master(	0,
//    						0x60f6,
//							1,
//							data_sdo_1,
//							1,
//							&data_sdo_1_size,
//							NULL);

    Eth_Add_Cyclic_Func (cyclic_task);
}
