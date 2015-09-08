/* Master 0, Slave 14, "AKD"
 * Vendor ID:       0x0000006a
 * Product code:    0x00414b44
 * Revision number: 0x00000002
 */

ec_pdo_entry_info_t akd_pdo_entries[] = {
    /* RxPdo 0x1600 */
    { 0x6040, 0x00, 16 }, /* DS402 command word */
    { 0x6071, 0x00, 16 }, /* target torque, in 1/1000 of nominal torque */
    /* TxPDO 0x1a00 */
    { 0x6041, 0x00, 16 }, /* DS402 status word */
    { 0x606C, 0x00, 32 }, /* actual velocity, in rpm */
};

ec_pdo_info_t akd_pdos[] = {
    { 0x1600, 2, akd_pdo_entries + 0 },
    { 0x1a00, 2, akd_pdo_entries + 2 },
};

ec_sync_info_t akd_syncs[] = {
    { 0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE },
    { 1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE },
    { 2, EC_DIR_OUTPUT, 1, akd_pdos + 0, EC_WD_DISABLE },
    { 3, EC_DIR_INPUT, 1, akd_pdos + 1, EC_WD_DISABLE },
    { 0xFF }
};

