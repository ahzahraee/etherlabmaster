/* Master 0, Slave 14, "AKD"
 * Vendor ID:       0x0000006a
 * Product code:    0x00414b44
 * Revision number: 0x00000002
 */

ec_pdo_entry_info_t akd_pdo_entries[] = {
    {0x6040, 0x00, 16},
    {0x6040, 0x00, 16},
    {0x6060, 0x00, 8},
    {0x6040, 0x00, 16},
    {0x607a, 0x00, 32},
    {0x6040, 0x00, 16},
    {0x60ff, 0x00, 32},
    {0x6041, 0x00, 16},
    {0x6041, 0x00, 16},
    {0x6061, 0x00, 8},
    {0x6041, 0x00, 16},
    {0x6064, 0x00, 32},
    {0x6041, 0x00, 16},
    {0x606c, 0x00, 32},
};

ec_pdo_info_t akd_pdos[] = {
    {0x1600, 1, akd_pdo_entries + 0},
    {0x1601, 2, akd_pdo_entries + 1},
    {0x1602, 2, akd_pdo_entries + 3},
    {0x1603, 2, akd_pdo_entries + 5},
    {0x1a00, 1, akd_pdo_entries + 7},
    {0x1a01, 2, akd_pdo_entries + 8},
    {0x1a02, 2, akd_pdo_entries + 10},
    {0x1a03, 2, akd_pdo_entries + 12},
};

ec_sync_info_t akd_syncs[] = {
    {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
    {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
    {2, EC_DIR_OUTPUT, 4, akd_pdos + 0, EC_WD_DISABLE},
    {3, EC_DIR_INPUT, 4, akd_pdos + 4, EC_WD_DISABLE},
    {0xff}
};

