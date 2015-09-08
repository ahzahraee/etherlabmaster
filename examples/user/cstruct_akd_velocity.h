/* AKD */
ec_pdo_entry_info_t akd_pdo_entries[] = {
    /* RxPdo 0x1600 */
    { 0x6040, 0x00, 16 }, /* DS402 command word */
    { 0x60FF, 0x00, 32 }, /* target velocity, milli rpm  */

    /* TxPDO 0x1a00 */
    { 0x6041, 0x00, 16 }, /* DS402 status word */
    { 0x606C, 0x00, 32 }, /* actual velocity, in milli rpm */
};

ec_pdo_info_t akd_pdos[] = {
    { 0x1600, 2, akd_pdo_entries + 0 },
    { 0x1a00, 2, akd_pdo_entries + 2 },
    { 0x1a01, 1, akd_pdo_entries + 4 },
};

ec_sync_info_t akd_syncs[] = {
    { 0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE },
    { 1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE },
    { 2, EC_DIR_OUTPUT, 1, akd_pdos + 0, EC_WD_DISABLE },
    { 3, EC_DIR_INPUT, 2, akd_pdos + 1, EC_WD_DISABLE },
    { 0xFF }
};
