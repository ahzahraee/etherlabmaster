/*****************************************************************************
 *
 *  $Id: main.c,v 6a6dec6fc806 2012/09/19 17:46:58 fp $
 *
 *  Copyright (C) 2007-2009  Florian Pose, Ingenieurgemeinschaft IgH
 *
 *  This file is part of the IgH EtherCAT Master.
 *
 *  The IgH EtherCAT Master is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License version 2, as
 *  published by the Free Software Foundation.
 *
 *  The IgH EtherCAT Master is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 *  Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with the IgH EtherCAT Master; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  ---
 *
 *  The license mentioned above concerns the source code only. Using the
 *  EtherCAT technology and brand is only permitted in compliance with the
 *  industrial property and similar rights of Beckhoff Automation GmbH.
 *
 ****************************************************************************/

// Example of communicating with an EK1818 module on the bus

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

/****************************************************************************/

#include "ecrt.h"

/****************************************************************************/

// Application parameters
#define FREQUENCY 100
#define PRIORITY 1

// Optional features
#define CONFIGURE_PDOS  1
#define SDO_ACCESS      0

/****************************************************************************/

// EtherCAT
static ec_master_t *master = NULL;
static ec_master_state_t master_state = {};

static ec_domain_t *domain1 = NULL;
static ec_domain_state_t domain1_state = {};

//static ec_slave_config_t *sc_ana_in = NULL;
//static ec_slave_config_state_t sc_ana_in_state = {};
static ec_slave_config_t *sc_ek1818 = NULL;
static ec_slave_config_state_t sc_ek1818_state = {};

// Timer
static unsigned int sig_alarms = 0;
static unsigned int user_alarms = 0;

/****************************************************************************/

// process data
static uint8_t *domain1_pd = NULL;

//#define BusCouplerPos  0, 0
//#define DigOutSlavePos 0, 2
//#define AnaInSlavePos  0, 3
//#define AnaOutSlavePos 0, 4
#define EK1818Pos  0, 0

//#define Beckhoff_EL3102 0x00000002, 0x0c1e3052
#define Beckhoff_EK1818 0x00000002, 0x071a2c52	 //Vendor ID, Product Code

// offsets for PDO entries
//static unsigned int off_ana_in_status;
//static unsigned int off_ana_in_value;
//static unsigned int off_ana_out;
//static unsigned int off_dig_out;
static unsigned int off_ek1818_out1;

//const static ec_pdo_entry_reg_t domain1_regs[] = {
//    {AnaInSlavePos,  Beckhoff_EL3102, 0x3101, 1, &off_ana_in_status},
//    {AnaInSlavePos,  Beckhoff_EL3102, 0x3101, 2, &off_ana_in_value},
//    {AnaOutSlavePos, Beckhoff_EL4102, 0x3001, 1, &off_ana_out},
//    {DigOutSlavePos, Beckhoff_EL2032, 0x3001, 1, &off_dig_out},
//    {}
//};

const static ec_pdo_entry_reg_t domain1_regs[] = {
    {EK1818Pos,  Beckhoff_EK1818, 0x7000, 1, &off_ek1818_out1}
};

static unsigned int counter = 0;
static unsigned int blink = 0;

/*****************************************************************************/

#if CONFIGURE_PDOS

// Analog in --------------------------

//static ec_pdo_entry_info_t el3102_pdo_entries[] = {
//    {0x3101, 1,  8}, // channel 1 status
//    {0x3101, 2, 16}, // channel 1 value
//    {0x3102, 1,  8}, // channel 2 status
//    {0x3102, 2, 16}, // channel 2 value
//    {0x6401, 1, 16}, // channel 1 value (alt.)
//    {0x6401, 2, 16}  // channel 2 value (alt.)
//};
//
//static ec_pdo_info_t el3102_pdos[] = {
//    {0x1A00, 2, el3102_pdo_entries},
//    {0x1A01, 2, el3102_pdo_entries + 2}
//};
//
//static ec_sync_info_t el3102_syncs[] = {
//    {2, EC_DIR_OUTPUT},
//    {3, EC_DIR_INPUT, 2, el3102_pdos},
//    {0xff}
//};


/* Master 0, Slave 0, "EK1818"
 * Vendor ID:       0x00000002
 * Product code:    0x071a2c52
 * Revision number: 0x00110000
 */

ec_pdo_entry_info_t slave_0_pdo_entries[] = {
    {0x7000, 0x01, 1}, /* Output */
    {0x7010, 0x01, 1}, /* Output */
    {0x7020, 0x01, 1}, /* Output */
    {0x7030, 0x01, 1}, /* Output */
    {0x6000, 0x01, 1}, /* Input */
    {0x6010, 0x01, 1}, /* Input */
    {0x6020, 0x01, 1}, /* Input */
    {0x6030, 0x01, 1}, /* Input */
    {0x6040, 0x01, 1}, /* Input */
    {0x6050, 0x01, 1}, /* Input */
    {0x6060, 0x01, 1}, /* Input */
    {0x6070, 0x01, 1}, /* Input */
};

ec_pdo_info_t slave_0_pdos[] = {
    {0x1600, 1, slave_0_pdo_entries + 0}, /* Channel 9 */
    {0x1601, 1, slave_0_pdo_entries + 1}, /* Channel 10 */
    {0x1602, 1, slave_0_pdo_entries + 2}, /* Channel 11 */
    {0x1603, 1, slave_0_pdo_entries + 3}, /* Channel 12 */
    {0x1a00, 1, slave_0_pdo_entries + 4}, /* Channel 1 */
    {0x1a01, 1, slave_0_pdo_entries + 5}, /* Channel 2 */
    {0x1a02, 1, slave_0_pdo_entries + 6}, /* Channel 3 */
    {0x1a03, 1, slave_0_pdo_entries + 7}, /* Channel 4 */
    {0x1a04, 1, slave_0_pdo_entries + 8}, /* Channel 5 */
    {0x1a05, 1, slave_0_pdo_entries + 9}, /* Channel 6 */
    {0x1a06, 1, slave_0_pdo_entries + 10}, /* Channel 7 */
    {0x1a07, 1, slave_0_pdo_entries + 11}, /* Channel 8 */
};

ec_sync_info_t slave_0_syncs[] = {
    {0, EC_DIR_OUTPUT, 4, slave_0_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT, 8, slave_0_pdos + 4, EC_WD_DISABLE},
    {0xff}
};

#endif

/*****************************************************************************/

#if SDO_ACCESS
static ec_sdo_request_t *sdo;
#endif

/*****************************************************************************/

void check_domain1_state(void)
{
    ec_domain_state_t ds;

    ecrt_domain_state(domain1, &ds);

    if (ds.working_counter != domain1_state.working_counter)
        printf("Domain1: WC %u.\n", ds.working_counter);
    if (ds.wc_state != domain1_state.wc_state)
        printf("Domain1: State %u.\n", ds.wc_state);

    domain1_state = ds;
}

/*****************************************************************************/

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

/*****************************************************************************/

void check_slave_config_states(void)
{
    ec_slave_config_state_t s;

    ecrt_slave_config_state(sc_ek1818, &s);

    if (s.al_state != sc_ek1818_state.al_state)
        printf("AnaIn: State 0x%02X.\n", s.al_state);
    if (s.online != sc_ek1818_state.online)
        printf("AnaIn: %s.\n", s.online ? "online" : "offline");
    if (s.operational != sc_ek1818_state.operational)
        printf("AnaIn: %soperational.\n",
                s.operational ? "" : "Not ");

    sc_ek1818_state = s;
}

/*****************************************************************************/

#if SDO_ACCESS
void read_sdo(void)
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
#endif

/****************************************************************************/

void cyclic_task()
{
    // receive process data
    ecrt_master_receive(master);
    ecrt_domain_process(domain1);

    // check process data state (optional)
    check_domain1_state();

    if (counter) {
        counter--;
    } else { // do this at 1 Hz
        counter = FREQUENCY;

        // calculate new process data
        blink = !blink;

        // check for master state (optional)
        check_master_state();

        // check for islave configuration state(s) (optional)
        check_slave_config_states();

#if SDO_ACCESS
        // read process data SDO
        read_sdo();
#endif

    }

#if 0
    // read process data
    printf("AnaIn: state %u value %u\n",
            EC_READ_U8(domain1_pd + off_ana_in_status),
            EC_READ_U16(domain1_pd + off_ana_in_value));
#endif

#if 1
    // write process data
    EC_WRITE_U8(domain1_pd + off_ek1818_out1, blink ? 0x06 : 0x09);
#endif

    // send process data
    ecrt_domain_queue(domain1);
    ecrt_master_send(master);
}

/****************************************************************************/

void signal_handler(int signum) {
    switch (signum) {
        case SIGALRM:
            sig_alarms++;
            break;
    }
}

/****************************************************************************/

int main(int argc, char **argv)
{
    ec_slave_config_t *sc;
    struct sigaction sa;
    struct itimerval tv;

    master = ecrt_request_master(0);
    if (!master)
        return -1;

    domain1 = ecrt_master_create_domain(master);
    if (!domain1)
        return -1;

    if (!(sc_ek1818 = ecrt_master_slave_config(
                    master, EK1818Pos, Beckhoff_EK1818))) {
        fprintf(stderr, "Failed to get slave configuration.\n");
        return -1;
    }

#if SDO_ACCESS
    fprintf(stderr, "Creating SDO requests...\n");
    if (!(sdo = ecrt_slave_config_create_sdo_request(sc_ana_in, 0x3102, 2, 2))) {
        fprintf(stderr, "Failed to create SDO request.\n");
        return -1;
    }
    ecrt_sdo_request_timeout(sdo, 500); // ms
#endif

#if CONFIGURE_PDOS
    printf("Configuring PDOs...\n");
    if (ecrt_slave_config_pdos(sc_ek1818, EC_END, slave_0_syncs)) {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
    }
#endif

    // Create configuration EK1818
    sc = ecrt_master_slave_config(master, EK1818Pos, Beckhoff_EK1818);
    if (!sc)
        return -1;

    if (ecrt_domain_reg_pdo_entry_list(domain1, domain1_regs)) {
        fprintf(stderr, "PDO entry registration failed!\n");
        return -1;
    }

    printf("Activating master...\n");
    if (ecrt_master_activate(master))
        return -1;

    if (!(domain1_pd = ecrt_domain_data(domain1))) {
        return -1;
    }

#if PRIORITY
    pid_t pid = getpid();
    if (setpriority(PRIO_PROCESS, pid, -19))
        fprintf(stderr, "Warning: Failed to set priority: %s\n",
                strerror(errno));
#endif

    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGALRM, &sa, 0)) {
        fprintf(stderr, "Failed to install signal handler!\n");
        return -1;
    }

    printf("Starting timer...\n");
    tv.it_interval.tv_sec = 0;
    tv.it_interval.tv_usec = 1000000 / FREQUENCY;
    tv.it_value.tv_sec = 0;
    tv.it_value.tv_usec = 1000;
    if (setitimer(ITIMER_REAL, &tv, NULL)) {
        fprintf(stderr, "Failed to start timer: %s\n", strerror(errno));
        return 1;
    }

    printf("Started.\n");
    while (1) {
        pause();

#if 0
        struct timeval t;
        gettimeofday(&t, NULL);
        printf("%u.%06u\n", t.tv_sec, t.tv_usec);
#endif

        while (sig_alarms != user_alarms) {
            cyclic_task();
            user_alarms++;
        }
    }

    return 0;
}

/****************************************************************************/
