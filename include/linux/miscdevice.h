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

//�����豸
//Misc����miscellaneous��������һЩӵ���Ź�ͬ���Եļ��ַ��豸�������ں˳������Щ���Զ��γ�һЩAPI�����ļ�drivers/char/misc.c��ʵ�֣����Լ���Щ�豸��������ĳ�ʼ�������е�misc�豸������ͬһ�����豸��MISC_MAJOR(10)������ÿһ������ѡ��һ�������Ĵ��豸�š����һ���ַ��豸����Ҫ��������豸����ô���Ͳ�Ӧ����misc�豸��ʵ�֡�
//ͨ������£�һ���ַ��豸�����ò��ڳ�ʼ���Ĺ����н�������Ĳ��裺
//ͨ��alloc_chrdev_region()������/���豸�š�
//ʹ��cdev_init()��cdev_add()����һ���ַ��豸ע���Լ���
//��һ��misc�����������ֻ��һ������misc_register()����������еĲ��衣
//���е�miscdevice�豸�γ�һ���������豸����ʱ���ں˸��ݴ��豸�Ų��Ҷ�Ӧ��miscdevice�豸��Ȼ�������file_operations��ע����ļ������������в�����
//��Linux�ں��У�ʹ��struct miscdevice����ʾmiscdevice������ṹ��Ķ���Ϊ��
struct miscdevice  //���ӽṹ�����ں��У����ʱֻ��Ҫ������������������£�
{
	int minor;// //�Զ�������豸��
	const char *name;
	const struct file_operations *fops;//�ļ�����
	struct list_head list;//����ͷ�������豸�γ�һ������
	struct device *parent;
	struct device *this_device;
	const char *nodename;
	mode_t mode;
};

//minor����������豸�Ĵ��豸�ţ�����ϵͳ�Զ����ã����������ΪMISC_DYNANIC_MINOR��name���豸����
//ÿһ��misc�������Զ�������/sys/class/misc�£�������Ҫ��������������ȷ��ȥ����Linux watchdog timer������ʵ��Ϊmisc ���������Ǳ�����drivers/char/watchdog/Ŀ¼�¡�Watchdog ����Ҳ������һ����׼�豸�ӿڵ��û��ռ䡣�����Ϳ���ʹ��������ӿڵ�Ӧ�ó����ʵ�ֶ�����WatchdogӲ�������API���ں����е�Documentation/watchdog/watchdog-api.txt�ļ�������ϸ��˵������Ҫwatchdog����ĳ�����Բ���/dev/watchdog,����豸��һ��misc���豸��130��
//WDT���ں���ͨ����ʵ��Ϊmisc������
// 

extern int misc_register(struct miscdevice * misc);
extern int misc_deregister(struct miscdevice *misc);

#define //MODULE_ALIAS_MISCDEV(minor)				\
	//MODULE_ALIAS("char-major-" __stringify(MISC_MAJOR)	\
	"-" __stringify(minor))
#endif
