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
	{ 0xf550b75d, "cdev_del" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xb9c78ada, "cdev_init" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0xd0d8621b, "strlen" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x62c1ade7, "malloc_sizes" },
	{ 0x20000329, "simple_strtoul" },
	{ 0x2addc0be, "down_interruptible" },
	{ 0x6729d3df, "__get_user_4" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x999e8297, "vfree" },
	{ 0x91715312, "sprintf" },
	{ 0x671c95aa, "kthread_create_on_node" },
	{ 0x7d11c268, "jiffies" },
	{ 0xe2d5255a, "strcmp" },
	{ 0xd7474566, "__copy_to_user_ll" },
	{ 0xcc87729d, "netif_rx" },
	{ 0x48eb0c0d, "__init_waitqueue_head" },
	{ 0x72aa82c6, "param_ops_charp" },
	{ 0xd126d593, "dev_alloc_skb" },
	{ 0x95435001, "current_task" },
	{ 0x50eedeb8, "printk" },
	{ 0x3d11617c, "kthread_stop" },
	{ 0x4141f80, "__tracepoint_module_get" },
	{ 0x90c768f7, "free_netdev" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xb6ed1e53, "strncpy" },
	{ 0x2da418b5, "copy_to_user" },
	{ 0x84ac939, "register_netdev" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x9e492980, "skb_push" },
	{ 0xdd1a2871, "down" },
	{ 0x71abefe1, "device_create" },
	{ 0x325c1c47, "__get_page_tail" },
	{ 0xf6ede60b, "cdev_add" },
	{ 0xebebf1d1, "module_put" },
	{ 0xb2fd5ceb, "__put_user_4" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x4292364c, "schedule" },
	{ 0xd62c833f, "schedule_timeout" },
	{ 0x9e7a1f46, "alloc_netdev_mqs" },
	{ 0xd8fd1969, "eth_type_trans" },
	{ 0xb762e2e5, "wake_up_process" },
	{ 0xc4b06e24, "ether_setup" },
	{ 0x6fe340df, "kmem_cache_alloc_trace" },
	{ 0xe42b03c1, "sched_setscheduler" },
	{ 0xe45f60d8, "__wake_up" },
	{ 0xd2965f6f, "kthread_should_stop" },
	{ 0x37a0cba, "kfree" },
	{ 0x622fa02a, "prepare_to_wait" },
	{ 0xf59f197, "param_array_ops" },
	{ 0x6128b5fc, "__printk_ratelimit" },
	{ 0xc4554217, "up" },
	{ 0xed75bfaf, "set_user_nice" },
	{ 0xd13b2b18, "class_destroy" },
	{ 0x5a4896a8, "__put_user_2" },
	{ 0x75bb675a, "finish_wait" },
	{ 0xad2688a8, "device_unregister" },
	{ 0x8f9c199c, "__get_user_2" },
	{ 0xa12f8b16, "unregister_netdev" },
	{ 0xb81960ca, "snprintf" },
	{ 0x1b77b03, "__netif_schedule" },
	{ 0xcee0f9ca, "consume_skb" },
	{ 0x86e01b68, "vmalloc_to_page" },
	{ 0xae309282, "skb_put" },
	{ 0x33d169c9, "_copy_from_user" },
	{ 0xc3fe87c8, "param_ops_uint" },
	{ 0x1df70be4, "__class_create" },
	{ 0x29537c9e, "alloc_chrdev_region" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "D0A4D15A235DB2521B2F7A5");
