#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xd4733cff, "module_layout" },
	{ 0x397ea5e3, "netdev_info" },
	{ 0xf7189473, "mii_ethtool_gset" },
	{ 0xfa3051e9, "ecdev_open" },
	{ 0xf9a482f9, "msleep" },
	{ 0x5cc591a8, "ecdev_withdraw" },
	{ 0x3ec8886f, "param_ops_int" },
	{ 0xf84b4615, "__napi_complete" },
	{ 0xb2ba53eb, "dev_set_drvdata" },
	{ 0x27bbf221, "disable_irq_nosync" },
	{ 0xea5578d5, "pci_disable_device" },
	{ 0xc7a4fbed, "rtnl_lock" },
	{ 0xe5a53698, "eth_change_mtu" },
	{ 0xed81fb74, "skb_copy_and_csum_dev" },
	{ 0xa4eb4eff, "_raw_spin_lock_bh" },
	{ 0x143f0cff, "generic_mii_ioctl" },
	{ 0xc821c4ce, "x86_dma_fallback_dev" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x2ca1d717, "pci_release_regions" },
	{ 0xfb0e29f, "init_timer_key" },
	{ 0x6baae653, "cancel_delayed_work_sync" },
	{ 0x7e1e97fb, "pci_bus_write_config_word" },
	{ 0xfd3c68b2, "ecdev_offer" },
	{ 0x7d11c268, "jiffies" },
	{ 0xb444bbeb, "__netdev_alloc_skb" },
	{ 0xc97261a2, "pci_set_master" },
	{ 0xf10de535, "ioread8" },
	{ 0xb69b1d94, "mii_nway_restart" },
	{ 0x6e877360, "pci_restore_state" },
	{ 0xab80f0ef, "pci_iounmap" },
	{ 0x510f6ed7, "dev_err" },
	{ 0xf97456ea, "_raw_spin_unlock_irqrestore" },
	{ 0x50eedeb8, "printk" },
	{ 0x90c768f7, "free_netdev" },
	{ 0x84ac939, "register_netdev" },
	{ 0x224d14a8, "netif_receive_skb" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0xa34f1ef5, "crc32_le" },
	{ 0x68e0f9a0, "netif_napi_add" },
	{ 0x656ad20e, "dma_release_from_coherent" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0x6a4417b9, "dma_alloc_from_coherent" },
	{ 0xe4d6e43a, "netif_device_attach" },
	{ 0x7e5d5a9e, "_dev_info" },
	{ 0x8ff4079b, "pv_irq_ops" },
	{ 0x7b800764, "netif_device_detach" },
	{ 0x823ab0bb, "pci_bus_read_config_word" },
	{ 0x1f482af3, "ecdev_receive" },
	{ 0xb03e0b5, "__napi_schedule" },
	{ 0x8bf826c, "_raw_spin_unlock_bh" },
	{ 0x77edf722, "schedule_delayed_work" },
	{ 0x8854c242, "ecdev_set_link" },
	{ 0x727c4f3, "iowrite8" },
	{ 0xf1faac3a, "_raw_spin_lock_irq" },
	{ 0xcebc12e1, "mii_check_media" },
	{ 0xd8fd1969, "eth_type_trans" },
	{ 0xfc8cc9a9, "pci_unregister_driver" },
	{ 0x67f7403e, "_raw_spin_lock" },
	{ 0x21fb443e, "_raw_spin_lock_irqsave" },
	{ 0xfaf98462, "bitrev32" },
	{ 0xf6ebc03b, "net_ratelimit" },
	{ 0x2ad8535d, "pci_set_power_state" },
	{ 0x8496ff85, "eth_validate_addr" },
	{ 0x8c183cbe, "iowrite16" },
	{ 0xfcec0987, "enable_irq" },
	{ 0x2f24ef05, "pci_request_regions" },
	{ 0xf59f197, "param_array_ops" },
	{ 0x7e79192d, "__pci_register_driver" },
	{ 0xc5534d64, "ioread16" },
	{ 0xa12f8b16, "unregister_netdev" },
	{ 0xe7e1eb6e, "mii_link_ok" },
	{ 0x1b77b03, "__netif_schedule" },
	{ 0x48ccb2c4, "pci_iomap" },
	{ 0xcee0f9ca, "consume_skb" },
	{ 0x436c2179, "iowrite32" },
	{ 0xae309282, "skb_put" },
	{ 0xdb49d31, "pci_enable_device" },
	{ 0x844a224f, "ecdev_close" },
	{ 0x74f13e03, "dev_get_drvdata" },
	{ 0xc4d1c67d, "mii_ethtool_sset" },
	{ 0x6e720ff2, "rtnl_unlock" },
	{ 0x3ae4ab7, "dma_ops" },
	{ 0xe484e35f, "ioread32" },
	{ 0xf20dabd8, "free_irq" },
	{ 0xeb9f7e74, "pci_save_state" },
	{ 0xe914e41e, "strcpy" },
	{ 0x5748fb87, "alloc_etherdev_mqs" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=mii,ec_master";


MODULE_INFO(srcversion, "FA67A769F7EAA9395257ABA");
