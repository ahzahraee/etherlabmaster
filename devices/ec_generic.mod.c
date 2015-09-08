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
	{ 0xfa3051e9, "ecdev_open" },
	{ 0x5cc591a8, "ecdev_withdraw" },
	{ 0xaee16a85, "kernel_sendmsg" },
	{ 0x62c1ade7, "malloc_sizes" },
	{ 0xe00a2210, "sock_release" },
	{ 0xc01cf848, "_raw_read_lock" },
	{ 0xf32055e7, "dev_base_lock" },
	{ 0xe898c551, "sock_create_kern" },
	{ 0xfd3c68b2, "ecdev_offer" },
	{ 0x50eedeb8, "printk" },
	{ 0x90c768f7, "free_netdev" },
	{ 0xb6ed1e53, "strncpy" },
	{ 0xf3205c35, "init_net" },
	{ 0x1f482af3, "ecdev_receive" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x8854c242, "ecdev_set_link" },
	{ 0x9e7a1f46, "alloc_netdev_mqs" },
	{ 0xc4b06e24, "ether_setup" },
	{ 0x6fe340df, "kmem_cache_alloc_trace" },
	{ 0x72cd64e3, "kernel_recvmsg" },
	{ 0x37a0cba, "kfree" },
	{ 0xd45dc2c6, "kernel_bind" },
	{ 0x844a224f, "ecdev_close" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ec_master";


MODULE_INFO(srcversion, "288D84E19A89DAD394C0D57");
