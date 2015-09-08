/* Master 0, Slave 14, "AKD"
 * Vendor ID:       0x0000006a
 * Product code:    0x00414b44
 * Revision number: 0x00000002
 */

ec_pdo_entry_info_t akd_pdo_entries[] = {
    {0x6040, 0x00, 16},
    {0x60c1, 0x01, 32},
    {0x6041, 0x00, 16},
    {0x3470, 0x04, 16},
    {0x60fd, 0x00, 32},
    {0x606c, 0x00, 32},
    {0x6063, 0x00, 32},
};

ec_pdo_info_t akd_pdos[] = {
    {0x1600, 2, akd_pdo_entries + 0},
    {0x1a00, 3, akd_pdo_entries + 2},
    {0x1a01, 2, akd_pdo_entries + 5},
};

ec_sync_info_t akd_syncs[] = {
    {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
    {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
    {2, EC_DIR_OUTPUT, 1, akd_pdos + 0, EC_WD_DISABLE},
    {3, EC_DIR_INPUT, 2, akd_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

