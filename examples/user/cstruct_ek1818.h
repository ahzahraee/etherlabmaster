/* Slave "EK1818"
 * Vendor ID:       0x00000002
 * Product code:    0x071a2c52
 * Revision number: 0x00110000
 */

ec_pdo_entry_info_t  ek1818_pdo_entries[] = {
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

ec_pdo_info_t  ek1818_pdos[] = {
    {0x1600, 1,  ek1818_pdo_entries + 0}, /* Channel 9 */
    {0x1601, 1,  ek1818_pdo_entries + 1}, /* Channel 10 */
    {0x1602, 1,  ek1818_pdo_entries + 2}, /* Channel 11 */
    {0x1603, 1,  ek1818_pdo_entries + 3}, /* Channel 12 */
    {0x1a00, 1,  ek1818_pdo_entries + 4}, /* Channel 1 */
    {0x1a01, 1,  ek1818_pdo_entries + 5}, /* Channel 2 */
    {0x1a02, 1,  ek1818_pdo_entries + 6}, /* Channel 3 */
    {0x1a03, 1,  ek1818_pdo_entries + 7}, /* Channel 4 */
    {0x1a04, 1,  ek1818_pdo_entries + 8}, /* Channel 5 */
    {0x1a05, 1,  ek1818_pdo_entries + 9}, /* Channel 6 */
    {0x1a06, 1,  ek1818_pdo_entries + 10}, /* Channel 7 */
    {0x1a07, 1,  ek1818_pdo_entries + 11}, /* Channel 8 */
};

ec_sync_info_t  ek1818_syncs[] = {
    {0, EC_DIR_OUTPUT, 4,  ek1818_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT, 8,  ek1818_pdos + 4, EC_WD_DISABLE},
    {0xff}
};
