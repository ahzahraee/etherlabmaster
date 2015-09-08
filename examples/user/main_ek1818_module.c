/*
 * main_ek1818_module.c
 *
 *  Created on: Jul 7, 2015
 *      Author: sybot
 */

#include "stdio.h"

#include "Eth_Igh_Interface.h"

#include "cstruct_ek1818.h"

#define n_domains 1


// Slaves position on the bus
#define EK1818Pos  0, 0

//Vendor ID, Product Code
#define Beckhoff_EK1818 0x00000002, 0x071a2c52

ec_slave_config_t *sc_ek1818 = NULL;
static ec_slave_config_state_t ek1818_state = {};


// PDO entries' byte offset in the process data
unsigned int off_ek1818_out;
unsigned int off_ek1818_in;
// process data

const static ec_pdo_entry_reg_t domain_0_regs[] = {
    		{EK1818Pos,  Beckhoff_EK1818, 0x7000, 1, &off_ek1818_out},
			{EK1818Pos,  Beckhoff_EK1818, 0x6000, 1, &off_ek1818_in},
			{}
};

// cyclic task
static unsigned int blink = 0;
//#define PRINT_TIME



void cyclic_task()
{
	#ifdef PRINT_TIME
	Eth_Print_Time();
	#endif

	Eth_Read_PDO(0);

	check_domain_state(0);
	check_master_state();
	check_slave_config_state("EK1818", sc_ek1818, &ek1818_state);

    // calculate new process data
    blink = !blink;

    if (ek1818_state.operational) {
		#if 1
			// prepare process data to write
			EC_WRITE_U8(domains_pd[0] + off_ek1818_out, blink ? 0x0F : 0x0F); //write 1 to out2, out3 OR write 1 to out1, and out4
		#endif

		#if 0
			// print out process data
			printf("EK1818 inputs: \n In1 %u \n In2 %u \n In3 %u \n In4 %u \n In5 %u \n In6 %u \n In7 %u \n In8 %u \n",
					EC_READ_BIT(domains_pd[0] + off_ek1818_in, 0),
					EC_READ_BIT(domains_pd[0] + off_ek1818_in, 1),
					EC_READ_BIT(domains_pd[0] + off_ek1818_in, 2),
					EC_READ_BIT(domains_pd[0] + off_ek1818_in, 3),
					EC_READ_BIT(domains_pd[0] + off_ek1818_in, 4),
					EC_READ_BIT(domains_pd[0] + off_ek1818_in, 5),
					EC_READ_BIT(domains_pd[0] + off_ek1818_in, 6),
					EC_READ_BIT(domains_pd[0] + off_ek1818_in, 7),
					EC_READ_BIT(domains_pd[0] + off_ek1818_in, 8) );
		#endif
    }
	Eth_Write_PDO(0);
}

int main(int argc, char **argv) {

	printf("Initialising Ethercat master...\n");
    Eth_Initialise_Ethercat(0, 0);

    printf("Configuring Ethercat master...\n");
    Eth_Initialise_Environnement(0, -19, 1, 0, n_domains, domain_0_regs, NULL, NULL, NULL);

    sc_ek1818 = Eth_Enregistre_un_Esclave(ek1818_syncs, EK1818Pos, Beckhoff_EK1818);

    Eth_Start_Ethercat(n_domains);
    Eth_Add_Cyclic_Func (cyclic_task);
}
