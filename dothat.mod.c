#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
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
	{ 0xeb0ce2ec, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xb3dcdb60, __VMLINUX_SYMBOL_STR(i2c_smbus_read_byte_data) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xfef492cb, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0xcb093fb8, __VMLINUX_SYMBOL_STR(i2c_smbus_read_i2c_block_data) },
	{ 0x6f9504c8, __VMLINUX_SYMBOL_STR(i2c_smbus_write_byte_data) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0x78845154, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x22270ba5, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x4dbeb668, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xd5f2172f, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x80c3a99, __VMLINUX_SYMBOL_STR(spi_busnum_to_master) },
	{ 0x9fd2f487, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0xf2318181, __VMLINUX_SYMBOL_STR(class_unregister) },
	{ 0xaf90711f, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0xe131215c, __VMLINUX_SYMBOL_STR(spi_new_device) },
	{ 0x4409d2f1, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x1b38df4a, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x8834396c, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x71a14398, __VMLINUX_SYMBOL_STR(i2c_unregister_device) },
	{ 0x24e3e324, __VMLINUX_SYMBOL_STR(spi_sync) },
	{ 0x70a791ac, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0x3e53d89c, __VMLINUX_SYMBOL_STR(device_create_file) },
	{ 0x60f0564c, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0xc7710d52, __VMLINUX_SYMBOL_STR(input_register_device) },
	{ 0xc2165d85, __VMLINUX_SYMBOL_STR(__arm_iounmap) },
	{ 0xdf054e89, __VMLINUX_SYMBOL_STR(spi_write_then_read) },
	{ 0xbe08ccab, __VMLINUX_SYMBOL_STR(devm_input_allocate_device) },
	{ 0xf9e73082, __VMLINUX_SYMBOL_STR(scnprintf) },
	{ 0x577c3acc, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0xfb961d14, __VMLINUX_SYMBOL_STR(__arm_ioremap) },
	{ 0x6d354ce0, __VMLINUX_SYMBOL_STR(i2c_smbus_write_i2c_block_data) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x1c6d9962, __VMLINUX_SYMBOL_STR(spi_register_driver) },
	{ 0x7eca383a, __VMLINUX_SYMBOL_STR(i2c_get_adapter) },
	{ 0x62d6b7f1, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0x6e904dc6, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x42e8c44a, __VMLINUX_SYMBOL_STR(i2c_new_device) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("i2c:sn3218");
MODULE_ALIAS("i2c:cap1166");

MODULE_INFO(srcversion, "7D45582C8BB38AC78148CD9");
