/* AKD */
ec_pdo_entry_info_t akd_pdo_entries[] = {
    /* RxPdo 0x1600 */
    { 0x6040, 0x00, 16 }, /* DS402 command word */
    { 0x607A, 0x00, 32 }, /* target position */

    /* TxPDO 0x1a00 */
    { 0x6041, 0x00, 16 }, /* DS402 status word */

    /* the maximum length for PDO is 8 bytes, so create another PDO
       for actual velocity and position */

    /* TxPDO 0x1a01 */
    { 0x606C, 0x00, 32 }, /* actual velocity, in rpm */
    { 0x6063, 0x00, 32 }, /* actual position */
};

ec_pdo_info_t akd_pdos[] = {
    { 0x1600, 2, akd_pdo_entries + 0 },
    { 0x1a00, 1, akd_pdo_entries + 2 },
    { 0x1a01, 2, akd_pdo_entries + 3 },

};

ec_sync_info_t akd_syncs[] = {
    { 0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE },
    { 1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE },
    { 2, EC_DIR_OUTPUT, 1, akd_pdos + 0, EC_WD_DISABLE },
    { 3, EC_DIR_INPUT, 2, akd_pdos + 1, EC_WD_DISABLE },
    { 0xFF }
};
