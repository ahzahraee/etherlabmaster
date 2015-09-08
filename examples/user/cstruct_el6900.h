/* Master 0, Slave 1, "EL6900"
 * Vendor ID:       0x00000002
 * Product code:    0x1af43052
 * Revision number: 0x00120000
 */

ec_pdo_entry_info_t el6900_pdo_entries[] = {
    {0x7000, 0x01, 8}, /* FSOE Command */
    {0x7001, 0x01, 8}, /* SubIndex 001 */
    {0x7000, 0x03, 16}, /* FSOE CRC 001 */
    {0x7000, 0x02, 16}, /* FSOE ConnID */
    {0x7010, 0x01, 8}, /* FSOE Command */
    {0x7011, 0x01, 8}, /* SubIndex 001 */
    {0x7010, 0x03, 16}, /* FSOE CRC 001 */
    {0x7010, 0x02, 16}, /* FSOE ConnID */
    {0x7020, 0x01, 8}, /* FSOE Command */
    {0x7021, 0x01, 8}, /* SubIndex 001 */
    {0x7020, 0x03, 16}, /* FSOE CRC 001 */
    {0x7020, 0x02, 16}, /* FSOE ConnID */
    {0x7030, 0x01, 8}, /* FSOE Command */
    {0x7031, 0x01, 8}, /* SubIndex 001 */
    {0x7030, 0x03, 16}, /* FSOE CRC 001 */
    {0x7030, 0x02, 16}, /* FSOE ConnID */
    {0x7040, 0x01, 8}, /* FSOE Command */
    {0x7041, 0x01, 8}, /* SubIndex 001 */
    {0x7040, 0x03, 16}, /* FSOE CRC 001 */
    {0x7040, 0x02, 16}, /* FSOE ConnID */
    {0x7050, 0x01, 8}, /* FSOE Command */
    {0x7051, 0x01, 8}, /* SubIndex 001 */
    {0x7050, 0x03, 16}, /* FSOE CRC 001 */
    {0x7050, 0x02, 16}, /* FSOE ConnID */
    {0xf201, 0x01, 1}, /* SubIndex 001 */
    {0xf201, 0x02, 1}, /* SubIndex 002 */
    {0xf201, 0x03, 1}, /* SubIndex 003 */
    {0xf201, 0x04, 1}, /* SubIndex 004 */
    {0xf201, 0x05, 1}, /* SubIndex 005 */
    {0xf201, 0x06, 1}, /* SubIndex 006 */
    {0xf201, 0x07, 1}, /* SubIndex 007 */
    {0xf201, 0x08, 1}, /* SubIndex 008 */
    {0xf200, 0x01, 16}, /* Control */
    {0x6000, 0x01, 8}, /* FSOE Command */
    {0x6001, 0x01, 8}, /* SubIndex 001 */
    {0x6000, 0x03, 16}, /* FSOE CRC 001 */
    {0x6000, 0x02, 16}, /* FSOE ConnID */
    {0x6010, 0x01, 8}, /* FSOE Command */
    {0x6011, 0x01, 8}, /* SubIndex 001 */
    {0x6010, 0x03, 16}, /* FSOE CRC 001 */
    {0x6010, 0x02, 16}, /* FSOE ConnID */
    {0x6020, 0x01, 8}, /* FSOE Command */
    {0x6021, 0x01, 8}, /* SubIndex 001 */
    {0x6020, 0x03, 16}, /* FSOE CRC 001 */
    {0x6020, 0x02, 16}, /* FSOE ConnID */
    {0x6030, 0x01, 8}, /* FSOE Command */
    {0x6031, 0x01, 8}, /* SubIndex 001 */
    {0x6030, 0x03, 16}, /* FSOE CRC 001 */
    {0x6030, 0x02, 16}, /* FSOE ConnID */
    {0x6040, 0x01, 8}, /* FSOE Command */
    {0x6041, 0x01, 8}, /* SubIndex 001 */
    {0x6040, 0x03, 16}, /* FSOE CRC 001 */
    {0x6040, 0x02, 16}, /* FSOE ConnID */
    {0x6050, 0x01, 8}, /* FSOE Command */
    {0x6051, 0x01, 8}, /* SubIndex 001 */
    {0x6050, 0x03, 16}, /* FSOE CRC 001 */
    {0x6050, 0x02, 16}, /* FSOE ConnID */
    {0xf980, 0x03, 16}, /* Project CRC */
    {0xf100, 0x01, 3}, /* Safety Project State */
    {0x0000, 0x00, 4}, /* Gap */
    {0xf100, 0x08, 1}, /* Login Active */
    {0xf100, 0x09, 1}, /* Input Size Mismatch */
    {0xf100, 0x0a, 1}, /* Output Size Mismatch */
    {0x0000, 0x00, 4}, /* Gap */
    {0xf100, 0x0f, 1}, /* TxPDO State */
    {0xf100, 0x10, 1}, /* TxPDO Toggle */
};

ec_pdo_info_t el6900_pdos[] = {
    {0x1600, 4, el6900_pdo_entries + 0}, /* FSOE RxPDO-Map 001 */
    {0x1601, 4, el6900_pdo_entries + 4}, /* FSOE RxPDO-Map 002 */
    {0x1602, 4, el6900_pdo_entries + 8}, /* FSOE RxPDO-Map 003 */
    {0x1603, 4, el6900_pdo_entries + 12}, /* FSOE RxPDO-Map 004 */
    {0x1604, 4, el6900_pdo_entries + 16}, /* FSOE RxPDO-Map 005 */
    {0x1605, 4, el6900_pdo_entries + 20}, /* FSOE RxPDO-Map 006 */
    {0x17f0, 8, el6900_pdo_entries + 24}, /* DEVICE RxPDO-Map Standard In Vars */
    {0x17ff, 1, el6900_pdo_entries + 32}, /* DEVICE RxPDO-Map Control */
    {0x1a00, 4, el6900_pdo_entries + 33}, /* FSOE TxPDO-Map 001 */
    {0x1a01, 4, el6900_pdo_entries + 37}, /* FSOE TxPDO-Map 002 */
    {0x1a02, 4, el6900_pdo_entries + 41}, /* FSOE TxPDO-Map 003 */
    {0x1a03, 4, el6900_pdo_entries + 45}, /* FSOE TxPDO-Map 004 */
    {0x1a04, 4, el6900_pdo_entries + 49}, /* FSOE TxPDO-Map 005 */
    {0x1a05, 4, el6900_pdo_entries + 53}, /* FSOE TxPDO-Map 006 */
    {0x1bfb, 1, el6900_pdo_entries + 57}, /* DEVICE TxPDO-Map Device Info Data */
    {0x1bff, 8, el6900_pdo_entries + 58}, /* DEVICE TxPDO-Map Status */
};

ec_sync_info_t el6900_syncs[] = {
    {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
    {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
    {2, EC_DIR_OUTPUT, 8, el6900_pdos + 0, EC_WD_DISABLE},
    {3, EC_DIR_INPUT, 8, el6900_pdos + 8, EC_WD_DISABLE},
    {0xff}
};

