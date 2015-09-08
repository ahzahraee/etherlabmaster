/*
 * main_epos3.c
 *
 *  Created on: Jul 17, 2015
 *      Author: AHZ
 */

#include "stdio.h"

#include "Eth_Igh_Interface.h"

#include "cstruct_el6900.h"

#define n_domains 1

#define SDO

// Slave's position on the bus
#define EL6900Pos  0, 1

//Vendor ID, Product Code
#define BECKHOFF_EL6900 	BECKHOFF_VendorId, BECKHOFF_EL6900_ProductCode

#ifdef SDO
ec_sdo_request_t *el6900_sdo_1;
ec_sdo_request_t *el6900_sdo_2;
#endif

// slave configuration structures
ec_slave_config_t *sc_el6900 = NULL;
static ec_slave_config_state_t el6900_state = {};

// PDO entries' byte offset in the process data
unsigned int off_el6900_6000_1;		// off_el6900_pdoindex_subindex
unsigned int off_el6900_6000_2;
unsigned int off_el6900_6000_3;
unsigned int off_el6900_f100_0f;
unsigned int bit_pos_el6900_f100_0f;	// pdo entry is not byte alligned, bit position is needed
unsigned int off_el6900_f100_10;
unsigned int bit_pos_el6900_f100_10;	// pdo entry is not byte alligned, bit position is needed
unsigned int off_el6900_f100_01;

// process data

const static ec_pdo_entry_reg_t domain_0_regs[] = {
		//{EL6900Pos, BECKHOFF_EL6900, 0xf200, 0x01, &off_el6900_Control},
		{EL6900Pos, BECKHOFF_EL6900, 0x6000, 0x01, &off_el6900_6000_1},	/* FSOE Command */
		{EL6900Pos, BECKHOFF_EL6900, 0x6000, 0x02, &off_el6900_6000_2}, /* FSOE ConnID */
		{EL6900Pos, BECKHOFF_EL6900, 0x6000, 0x03, &off_el6900_6000_3}, /* FSOE CRC 001 */
		{EL6900Pos, BECKHOFF_EL6900, 0xf100, 0x0f, &off_el6900_f100_0f, &bit_pos_el6900_f100_0f}, /* TxPDO State */
		{EL6900Pos, BECKHOFF_EL6900, 0xf100, 0x10, &off_el6900_f100_10, &bit_pos_el6900_f100_10}, /* TxPDO Toggle */
		{EL6900Pos, BECKHOFF_EL6900, 0xf100, 0x01, &off_el6900_f100_01}, /* Safety Project State */
		{}
};

static unsigned int blink = 0;

void cyclic_task()
{
	Eth_Read_PDO(0);

	check_domain_state(0);
	check_master_state();
	check_slave_config_state("EL6900", sc_el6900, &el6900_state);

    if (el6900_state.operational) {
			printf("EL6900 TxPDO State : %u \n", EC_READ_BIT(domains_pd[0] + off_el6900_f100_0f, bit_pos_el6900_f100_0f) );
			printf("EL6900 Safety Project State : 0x%02X \n", EC_READ_U8(domains_pd[0] + off_el6900_f100_01));
    }

	Eth_Write_PDO(0);
}


int main(int argc, char **argv) {
	uint8_t *data_sdo_1 = NULL;
	uint8_t *data_sdo_2 = NULL;
	size_t data_sdo_1_size = 1;

    printf("Initialising Ethercat master...\n");
    Eth_Initialise_Ethercat(0, 0);

    printf("Configuring Ethercat master...\n");
    Eth_Initialise_Environnement(0, -19, 1, 0, n_domains, domain_0_regs, NULL, NULL, NULL);

    sc_el6900 = Eth_Enregistre_un_Esclave(el6900_syncs, EL6900Pos, BECKHOFF_EL6900);

//    epos3_sdo_1 = Eth_Create_SDO_Channel(sc_el6900, 0x6040, 0, 2, 500);
//    epos3_sdo_2 = Eth_Create_SDO_Channel(sc_epos3, 0xf050, 2, 4, 500);

    Eth_Start_Ethercat(n_domains);

    //read sdo
    //data_sdo_1 = Eth_Read_SDO( epos3_sdo_1 );

//    if (!data_sdo_1)
//    	printf("Reading SDO 1 failed.\n");
//    else
//        printf("SDO1 = %d\n", data_sdo_1[0]);


//    Eth_Read_SDO_Master(	0,
//    						0x60f6,
//							1,
//							data_sdo_1,
//							1,
//							&data_sdo_1_size,
//							NULL);

    Eth_Add_Cyclic_Func (cyclic_task);
}
