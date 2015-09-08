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
	{ 0xb569d6ba, "ecrt_master_receive" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x130a49c5, "ecrt_master_create_domain" },
	{ 0x97e8031c, "ecrt_master_send" },
	{ 0xe59df8c6, "ecrt_domain_queue" },
	{ 0x8d086ce7, "ecrt_master_send_ext" },
	{ 0xfb0e29f, "init_timer_key" },
	{ 0xb26b5fae, "ecrt_domain_reg_pdo_entry_list" },
	{ 0x7d11c268, "jiffies" },
	{ 0xd174c23c, "ecrt_domain_process" },
	{ 0x5496305a, "ecrt_domain_state" },
	{ 0xd5f2172f, "del_timer_sync" },
	{ 0x1758da77, "ecrt_master_callbacks" },
	{ 0xdcd26469, "ecrt_master_state" },
	{ 0x60dd2a36, "ecrt_slave_config_state" },
	{ 0x50eedeb8, "printk" },
	{ 0x4d18589a, "ecrt_master_slave_config" },
	{ 0xdd1a2871, "down" },
	{ 0xbe2c0274, "add_timer" },
	{ 0xf551b5a1, "ecrt_slave_config_pdos" },
	{ 0x14da230, "ecrt_domain_external_memory" },
	{ 0xb96b5dc, "ecrt_domain_size" },
	{ 0x37a0cba, "kfree" },
	{ 0xd4102ca2, "ecrt_master_activate" },
	{ 0x139b6adb, "ecrt_release_master" },
	{ 0xc4554217, "up" },
	{ 0x39618d6d, "ecrt_request_master" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ec_master";

