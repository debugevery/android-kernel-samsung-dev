#ifndef _LINUX_MISCDEVICE_H
#define _LINUX_MISCDEVICE_H
//#include <linux/module.h>
//#include <linux/major.h>

/*
 *	These allocations are managed by device@lanana.org. If you use an
 *	entry that is not in assigned your entry may well be moved and
 *	reassigned, or set dynamic if a fixed value is not justified.
 */

#define PSMOUSE_MINOR		1
#define MS_BUSMOUSE_MINOR	2
#define ATIXL_BUSMOUSE_MINOR	3
/*#define AMIGAMOUSE_MINOR	4	FIXME OBSOLETE */
#define ATARIMOUSE_MINOR	5
#define SUN_MOUSE_MINOR		6
#define APOLLO_MOUSE_MINOR	7
#define PC110PAD_MINOR		9
/*#define ADB_MOUSE_MINOR	10	FIXME OBSOLETE */
#define WATCHDOG_MINOR		130	/* Watchdog timer     */
#define TEMP_MINOR		131	/* Temperature Sensor */
#define RTC_MINOR		135
#define EFI_RTC_MINOR		136	/* EFI Time services */
#define SUN_OPENPROM_MINOR	139
#define DMAPI_MINOR		140	/* DMAPI */
#define NVRAM_MINOR		144
#define SGI_MMTIMER		153
#define STORE_QUEUE_MINOR	155
#define I2O_MINOR		166
#define MICROCODE_MINOR		184
#define TUN_MINOR		200
#define MWAVE_MINOR		219	/* ACP/Mwave Modem */
#define MPT_MINOR		220
#define MPT2SAS_MINOR		221
#define HPET_MINOR		228
#define FUSE_MINOR		229
#define KVM_MINOR		232
#define BTRFS_MINOR		234
#define AUTOFS_MINOR		235
#define MISC_DYNAMIC_MINOR	255

struct device;

//混杂设备
//Misc（或miscellaneous）驱动是一些拥有着共同特性的简单字符设备驱动。内核抽象出这些特性而形成一些API（在文件drivers/char/misc.c中实现），以简化这些设备驱动程序的初始化。所有的misc设备被分配同一个主设备号MISC_MAJOR(10)，但是每一个可以选择一个单独的次设备号。如果一个字符设备驱动要驱动多个设备，那么它就不应该用misc设备来实现。
//通常情况下，一个字符设备都不得不在初始化的过程中进行下面的步骤：
//通过alloc_chrdev_region()分配主/次设备号。
//使用cdev_init()和cdev_add()来以一个字符设备注册自己。
//而一个misc驱动，则可以只用一个调用misc_register()来完成这所有的步骤。
//所有的miscdevice设备形成一个链表，对设备访问时，内核根据次设备号查找对应的miscdevice设备，然后调用其file_operations中注册的文件操作方法进行操作。
//在Linux内核中，使用struct miscdevice来表示miscdevice。这个结构体的定义为：
struct miscdevice  //混杂结构体在内核中，设计时只需要调用它定义变量，如下：
{
	int minor;// //自动分配从设备号
	const char *name;
	const struct file_operations *fops;//文件操作
	struct list_head list;//链表头；各个设备形成一个链表
	struct device *parent;
	struct device *this_device;
	const char *nodename;
	mode_t mode;
};

//minor是这个混杂设备的次设备号，若由系统自动配置，则可以设置为MISC_DYNANIC_MINOR，name是设备名。
//每一个misc驱动会自动出现在/sys/class/misc下，而不需要驱动程序作者明确的去做。Linux watchdog timer驱动被实现为misc 驱动，他们被放在drivers/char/watchdog/目录下。Watchdog 驱动也导出了一个标准设备接口到用户空间。这样就可以使符合这个接口的应用程序的实现独立于Watchdog硬件。这个API在内核树中的Documentation/watchdog/watchdog-api.txt文件中有详细的说明。需要watchdog服务的程序可以操作/dev/watchdog,这个设备有一个misc次设备号130。
//WDT在内核中通常都实现为misc驱动。
// 

extern int misc_register(struct miscdevice * misc);
extern int misc_deregister(struct miscdevice *misc);

#define //MODULE_ALIAS_MISCDEV(minor)				\
	//MODULE_ALIAS("char-major-" __stringify(MISC_MAJOR)	\
	"-" __stringify(minor))
#endif
