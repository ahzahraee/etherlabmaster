/* Master 0, Slave 0, "EPOS3"
 * Vendor ID:       0x000000fb
 * Product code:    0x64400000
 * Revision number: 0x22100000
 */

ec_pdo_entry_info_t epos3_pdo_entries[] = {
    {0x6040, 0x00, 16}, /* 0x6040:00 */
    {0x607a, 0x00, 32}, /* 0x607A:00 */
    {0x60b0, 0x00, 32}, /* 0x60B0:00 */
    {0x60b1, 0x00, 32}, /* 0x60B1:00 */
    {0x60b2, 0x00, 16}, /* 0x60B2:00 */
    {0x6060, 0x00, 8}, /* 0x6060:00 */
    {0x2078, 0x01, 16}, /* 0x2078:01 */
    {0x60b8, 0x00, 16}, /* 0x60B8:00 */
    {0x6041, 0x00, 16}, /* 0x6041:00 */
    {0x6064, 0x00, 32}, /* 0x6064:00 */
    {0x606c, 0x00, 32}, /* 0x606C:00 */
    {0x6077, 0x00, 16}, /* 0x6077:00 */
    {0x6061, 0x00, 8}, /* 0x6061:00 */
    {0x2071, 0x01, 16}, /* 0x2071:01 */
    {0x60b9, 0x00, 16}, /* 0x60B9:00 */
    {0x60ba, 0x00, 32}, /* 0x60BA:00 */
    {0x60bb, 0x00, 32}, /* 0x60BB:00 */
};

ec_pdo_info_t epos3_pdos[] = {
    {0x1600, 8, epos3_pdo_entries + 0}, /* 1st receive PDO Mapping */
    {0x1a00, 9, epos3_pdo_entries + 8}, /* 1st transmit PDO Mapping */
};

ec_sync_info_t epos3_syncs[] = {
    {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
    {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
    {2, EC_DIR_OUTPUT, 1, epos3_pdos + 0, EC_WD_ENABLE},
    {3, EC_DIR_INPUT, 1, epos3_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

