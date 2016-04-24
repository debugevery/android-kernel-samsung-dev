/*
 * device.h - generic, centralized driver model
 *
 * Copyright (c) 2001-2003 Patrick Mochel <mochel@osdl.org>
 * Copyright (c) 2004-2009 Greg Kroah-Hartman <gregkh@suse.de>
 * Copyright (c) 2008-2009 Novell Inc.
 *
 * This file is released under the GPLv2
 *
 * See Documentation/driver-model/ for more information.
 */

#ifndef _DEVICE_H_
#define _DEVICE_H_

//#include <linux/ioport.h>
//#include <linux/kobject.h>
//#include <linux/klist.h>
//#include <linux/list.h>
//#include <linux/lockdep.h>
//#include <linux/compiler.h>
//#include <linux/types.h>
//#include <linux/module.h>
//#include <linux/pm.h>
//#include <asm/atomic.h>
//#include <asm/device.h>


struct device;
struct device_private;
struct device_driver;
struct driver_private;
struct class;
struct class_private;
struct bus_type;
struct bus_type_private;



struct bus_attribute {//�������Խṹ��
	struct attribute	attr;//���Խṹ��
	//show����ʵ�����ݶ�ȡ�����û��ռ��ȡ����ֵʱ�����ĵ��ø÷���ʵ�ֱ��룬���������β�buf��
	ssize_t (*show)(struct bus_type *bus, char *buf);
	//store����ʵ�����ݱ��档���û��ؼ���������ֵʱ�����ĵ��ø÷���ʵ�ֽ��룬ʹ��buf���ݵ����ݽ��룬countָʾbuf���ݵ����ݳ���
	ssize_t (*store)(struct bus_type *bus, const char *buf, size_t count);
};
//���ں��У�sysfs ����һ������ __ATTR ϵ�еĺ��������ģ�����豸��ʹ�� DEVICE_ATTR ��
//������ʹ�� BUS_ATTR ��������ʹ��DRIVER_ATTR �������(class)ʹ�� CLASS_ATTR,
//DEVICE_ATTR ���������ĸ��������ֱ������ơ�Ȩ��λ����������д���������ж�������д�����Ƕ�д���ܺ����ĺ�������
#define BUS_ATTR(_name, _mode, _show, _store)	\
struct bus_attribute bus_attr_##_name = __ATTR(_name, _mode, _show, _store)

extern int __must_check bus_create_file(struct bus_type *,
					struct bus_attribute *);
extern void bus_remove_file(struct bus_type *, struct bus_attribute *);


/*====================================================================
Linux�豸ģ������������Ҫ�ĸ����������,�豸,����.��bus,device,driver,��ʵ�����ں�
��Ҳ��������ôһЩ���ݽṹ,������ struct bus_type,struct device,struct device_driver,
��������Ҫ�����ݽṹ������һ���ط�,include/linux/device.h.����֪�������кܶ���,pci
����,scsi����,usb ����,�������ǻῴ�� Linux �ں˴����г���
pci_bus_type,scsi_bus_type,usb_bus_type,���Ƕ���struct bus_type���͵ı���.��
struct bus_type�ṹ�������ǳ���Ҫ�ĳ�Ա���� struct kset drivers �� struct kset devices.
kset ����һ������ kobject���� Linux Kernel 2.6���豸ģ�͵Ļ���Ԫ��,���˴���
��ȴ��Ը�ི,��Ϊ��ʱ����ȥ��ʶ����.���ǵ������л�������������˺���,��������˺�
��������ֻ�ǲ������,ֻ�����������еĹ��Ͷ���.�����������ĵ�Ӱ��,����Ҳ��ֻ��һ����
ͷ,������һ����ͷ����Ҳ����������.��������ֻ��Ҫ֪��,drivers �� devices �Ĵ���,��
struct bus_type������������ϵ������,һ���� devices ������,һ����drivers ������,Ҳ��
��˵,֪��һ����������Ӧ�����ݽṹ,�Ϳ����ҵ������������������豸����Щ,������Щ֧��
�����豸����������. 

��Ҫʵ����Щ,��Ҫ��ÿ�γ���һ���豸��Ҫ�����߻㱨,����˵ע��,ÿ�γ���һ������,ҲҪ��
���߻㱨,����˵ע��.����ϵͳ��ʼ����ʱ��,��ɨ����������Щ�豸,��Ϊÿһ���豸������һ
�� struct device�ı���,ÿһ����һ����������,��Ҫ׼��һ�� struct device_driver�ṹ��
����.����Щ����ͳͳ������Ӧ������,device����devices����,driver����drivers����. ��
��ͨ�����߾����ҵ�ÿһ���豸,ÿһ������.

,���� bus,���� device,���� driver,��������ν�����ϵ����?����֮,������
���ݽṹ�е�ָ������α���ֵ��?���嵽usb ϵͳ,�����������ľ���
usb core.usb core�Ĵ����������� usb ϵͳ�ĳ�ʼ��,��������struct bus_type 
usb_bus_type,Ȼ���ɨ�� usb ����,��������������Щusb�豸,����˵ root hub��������
Щusb�豸,��ô drivers������?����Ͳ���bus����������,������ÿһ�� driver ����ȥ bus����Ǽ�,
����˵����.���嵽usbϵͳ,ÿһ��usb�豸���������򶼻���һ�� struct usb_driver�ṹ
��,���������,���� include/linux/usb.h 

====================================================================*/

struct bus_type {//�豸������֮���������ϵ�ģ����ߣ���������ߵ����ã�
	const char		*name;//�������ƣ�������sysfs�ļ�ϵͳ��/sys/bus�£����ܺͱ�����������г�ͻ��
	struct bus_attribute	*bus_attrs;//�������ԡ�����Ϊ/sys/bus/<name>/�ļ����µ��ļ���
	struct device_attribute	*dev_attrs;//�������������豸��Ĭ�����ԡ�
	struct driver_attribute	*drv_attrs;//������������������Ĭ�����ԡ�

	//ÿ�����豸��ӵ�����ʱ���������ı��������ϵ���������
	//��ִ������device_register->device_add->bus_probe_device->device_attach->bus_for_each_drv->match/probe�������豸������
	//ÿ����������ӵ�����ʱ���������ı��������ϵ��豸����
	//��ִ������driver_register->bus_add_driver->driver_attach->bus_for_each_dev->match/probe�����������ɲٿص��豸��
	//��ǰ��matchһ��ִֻ�������ض���ƥ�䴦������probe�У�ͨ���ص��豸����probe������豸�ض���ƥ�䡢�豸��ʼ���ȡ�
	//������˵������PCI���ߣ�match�ж�����֧�ֵ�ID�б��Ƿ�����豸ID�����������ƥ�䣬����ʧ�䣻
	//probe���ٴ�ִ��IDƥ���жϣ����ص������ṩ��probe������
	//����һ�α���ƥ����ԣ����match��probe���ɹ��������ƥ����̣����match�ɹ���probeʧ�䣬������������ƥ�䣻
	//�������������û���ҵ��ɹ���ƥ�䣬�����������Ա�ʾû�пɲٿ��豸�������豸���Ա�ʾû���ʵ���������
	int (*match)(struct device *dev, struct device_driver *drv);//����ƥ�䡣�ж��豸�������Ƿ�ƥ�䣬��������ϵ��صġ���������ͨ��match��probe�������������ƥ��

	//�ڷ����Ȳ���¼���Ϣ���û��ռ�֮ǰ��ӻ������������豸ע�ᡢ�Ƴ�������״̬����ʱ��
	//�ں˸�����֪ͨ�¼����û��ռ䡣ͨ��man udev��man udevd�ɻ�ȡ��ذ�����uevent���¼���
	//�͵��û��ռ�֮ǰ���ã��������¼���������ض��Ļ�����������Linux-2.6.13�Ժ󣬲���udev���ƶ�̬�����豸�ļ�
	int (*uevent)(struct device *dev, struct kobj_uevent_env *env);//��ӻ���������

	//����match��������probeִ���豸��ص�ƥ��̽�⡢�豸��ʼ������Դ����ȡ���Ҫע�⣬
	//��probe����ʱ��dev->driver�Ѿ�������Ϊmatch�ɹ�ƥ�������ָ���ˣ���˲�����Ҫstruct device_driverָ��.
	int (*probe)(struct device *dev);//̽�⺯��

	//�豸�Ƴ�ʱ�����ø÷�������ɲ�������������ɾ���豸�����У��豸�����µĸ��豸��
	int (*remove)(struct device *dev);//�豸�Ƴ�ʱ���á�

	//ϵͳ�ػ�ʱ�����ø÷����ر��豸��
	void (*shutdown)(struct device *dev);//�ػ�ʱ���á�

	//�豸���ߣ�����ʱ���ø÷�����һ���ڸ÷����������豸Ϊ�ͺĵ�״̬��
	int (*suspend)(struct device *dev, pm_message_t state);//����Ͷ�����ߣ�ʱ���á�

	//�豸�������лָ�ʱ���ø÷���
	int (*resume)(struct device *dev);//�ָ�ʱ���á�

	//һЩ�豸�е�Դ״̬ת�����ṹ���ڲ��ṩ�ܶ෽��ʵ��������̡���ʱ��������ṹ�塣
	const struct dev_pm_ops *pm;//�豸��Դ����

	//�����������ò�ʹ�ã������������ع��������Ա������һ�㲻Ҫȥ�޸���
	struct bus_type_private *p;//˽�����ݡ���ȫ���������ĳ�ʼ����ʹ�á�
};

//�豸���������ϸ����ֵģ��豸���豸���������������豸ͨ��struct device�����壬
//��Ȼ�û�Ҳ���Խ��ýṹ���װ���Լ������device�ṹ���У����磬struct platform_device��
struct device {//�豸�ṹ�壺���������豸��ص���Ϣ�豸֮��Ĳ�ι�ϵ���Լ��豸�����ߡ������Ĺ�ϵ
	struct device		*parent;//���豸

	struct device_private	*p;

	struct kobject kobj;
	const char		*init_name; /* initial name of the device */
	struct device_type	*type;

	struct mutex		mutex;	/* mutex to synchronize calls to
					 * its driver.
					 */

	struct bus_type	*bus;		/* type of bus device is on */
	struct device_driver *driver;	/* which driver has allocated this
					   device */
	void		*platform_data;	/* ƽ̨��������Platform specific data, device
					   core doesn't touch it */
	struct dev_pm_info	power;

#ifdef CONFIG_NUMA
	int		numa_node;	/* NUMA node this device is close to */
#endif
	u64		*dma_mask;	/* dma mask (if dma'able device) */
	u64		coherent_dma_mask;/* Like dma_mask, but for
					     alloc_coherent mappings as
					     not all hardware supports
					     64 bit addresses for consistent
					     allocations such descriptors. */

	struct device_dma_parameters *dma_parms;

	struct list_head	dma_pools;	/* dma pools (if dma'ble) */

	struct dma_coherent_mem	*dma_mem; /* internal for coherent mem
					     override */
	/* arch specific additions */
	struct dev_archdata	archdata;
#ifdef CONFIG_OF
	struct device_node	*of_node;
#endif

	dev_t			devt;	/* dev_t, creates the sysfs "dev" */

	spinlock_t		devres_lock;
	struct list_head	devres_head;

	struct klist_node	knode_class;
	struct class		*class;
	const struct attribute_group **groups;	/* optional groups */

	void	(*release)(struct device *dev);
};


struct device_driver {//�豸�����ṹ�壺�豸���豸���������������豸ͨ��struct device�����壬������struct device_driver����
	//�豸������������ơ��ڵ���driver_register()���豸��������ģ���в���һ����
	//��device_driver����ʱ��driver_register()���������bus_add_driver()������
	//bus_add_driver()����kobject_set_name()������name����drv>kobj.name����drv->kobj.k_name��
	const char		*name;//�豸������������ơ�
	
	struct bus_type		*bus;//ָ��������������ָ�룬����������֧�ֵ��豸��

	//��ʾʵ���豸���������ģ�顣Ҳ�����ڸ�������ʵ���У����ʹ����ģ�飬��ô�����ָ������д��ģ�飬��ʹ��mod_name��ָ��ģ���������û��ʹ��ģ�飬�Ǹ����Ϊ�ա����иýṹ�е�module_kobject���͵�mkobjҲ����owner�йص���
	struct module		*owner;
	const char		*mod_name;	/* used for built-in modules */

	bool suppress_bind_attrs;	/* disables bind/unbind via sysfs */

	//������ص��������ڴ����Ȳ�Ρ����弴�ú͵�Դ����
	//�������豸����������һ����������������豸ʱ�ͻ����probe��������Ӧ�ĺ�������̽��Ӳ����
	//�Ӷ��Ը��豸���и���һ���ļ�顣�����device_driver�����pribe()�����ķ���ֵ��һ��������
	//�Ǿ���ζ����������ܰ�����豸�ϣ���ô��Ҫ�ͷ�����Ϊ��device_driver����������Դ��     
	//������һ�����Ȳ�ε��豸ʱ������������remove������������������ж��ʱ��
	//���������ÿ���豸Ҳ�����remove���������ں˱�������豸�Ĺ���״̬ʱ��
	//�豸���������shutdown��suspend��resume��������������shutdown������ֹͣ���豸���硣
	//suspend�����ǽ��豸�л����͹���״̬��
	int (*probe) (struct device *dev);
	int (*remove) (struct device *dev);
	void (*shutdown) (struct device *dev);
	int (*suspend) (struct device *dev, pm_message_t state);
	int (*resume) (struct device *dev);
	
	const struct attribute_group **groups;

	const struct dev_pm_ops *pm;//�豸��Դ����

	struct driver_private *p;//˽�����ݡ���ȫ���������ĳ�ʼ����ʹ�á�
};

/*
 * device classes
 */
struct class {
	const char		*name;
	struct module		*owner;

	struct class_attribute		*class_attrs;
	struct device_attribute		*dev_attrs;
	struct kobject			*dev_kobj;

	int (*dev_uevent)(struct device *dev, struct kobj_uevent_env *env);
	char *(*devnode)(struct device *dev, mode_t *mode);

	void (*class_release)(struct class *class);
	void (*dev_release)(struct device *dev);

	int (*suspend)(struct device *dev, pm_message_t state);
	int (*resume)(struct device *dev);

	const struct kobj_ns_type_operations *ns_type;
	const void *(*namespace)(struct device *dev);

	const struct dev_pm_ops *pm;

	struct class_private *p;
};


extern int __must_check bus_register(struct bus_type *bus);
extern void bus_unregister(struct bus_type *bus);

extern int __must_check bus_rescan_devices(struct bus_type *bus);

/* iterator helpers for buses */

int bus_for_each_dev(struct bus_type *bus, struct device *start, void *data,
		     int (*fn)(struct device *dev, void *data));
struct device *bus_find_device(struct bus_type *bus, struct device *start,
			       void *data,
			       int (*match)(struct device *dev, void *data));
struct device *bus_find_device_by_name(struct bus_type *bus,
				       struct device *start,
				       const char *name);

int __must_check bus_for_each_drv(struct bus_type *bus,
				  struct device_driver *start, void *data,
				  int (*fn)(struct device_driver *, void *));

void bus_sort_breadthfirst(struct bus_type *bus,
			   int (*compare)(const struct device *a,
					  const struct device *b));
/*
 * Bus notifiers: Get notified of addition/removal of devices
 * and binding/unbinding of drivers to devices.
 * In the long run, it should be a replacement for the platform
 * notify hooks.
 */
struct notifier_block;

extern int bus_register_notifier(struct bus_type *bus,
				 struct notifier_block *nb);
extern int bus_unregister_notifier(struct bus_type *bus,
				   struct notifier_block *nb);

/* All 4 notifers below get called with the target struct device *
 * as an argument. Note that those functions are likely to be called
 * with the device lock held in the core, so be careful.
 */
#define BUS_NOTIFY_ADD_DEVICE		0x00000001 /* device added */
#define BUS_NOTIFY_DEL_DEVICE		0x00000002 /* device removed */
#define BUS_NOTIFY_BOUND_DRIVER		0x00000003 /* driver bound to device */
#define BUS_NOTIFY_UNBIND_DRIVER	0x00000004 /* driver about to be
						      unbound */
#define BUS_NOTIFY_UNBOUND_DRIVER	0x00000005 /* driver is unbound
						      from the device */

extern struct kset *bus_get_kset(struct bus_type *bus);
extern struct klist *bus_get_device_klist(struct bus_type *bus);




extern int __must_check driver_register(struct device_driver *drv);
extern void driver_unregister(struct device_driver *drv);

extern struct device_driver *get_driver(struct device_driver *drv);
extern void put_driver(struct device_driver *drv);
extern struct device_driver *driver_find(const char *name,
					 struct bus_type *bus);
extern int driver_probe_done(void);
extern void wait_for_device_probe(void);


/* sysfs interface for exporting driver attributes */

struct driver_attribute {//�������Խṹ�壺����bus_attribute
	struct attribute attr;
	ssize_t (*show)(struct device_driver *driver, char *buf);
	ssize_t (*store)(struct device_driver *driver, const char *buf,
			 size_t count);
};
//���ں��У�sysfs ����һ������ __ATTR ϵ�еĺ��������ģ�����豸��ʹ�� DEVICE_ATTR ��
//������ʹ�� BUS_ATTR ��������ʹ��DRIVER_ATTR �������(class)ʹ�� CLASS_ATTR,
//���������ĸ��������ֱ������ơ�Ȩ��λ����������д���������ж�������д�����Ƕ�д���ܺ����ĺ�������
#define DRIVER_ATTR(_name, _mode, _show, _store)	\
struct driver_attribute driver_attr_##_name =		\
	__ATTR(_name, _mode, _show, _store)

extern int __must_check driver_create_file(struct device_driver *driver,
					const struct driver_attribute *attr);
extern void driver_remove_file(struct device_driver *driver,
			       const struct driver_attribute *attr);

extern int __must_check driver_add_kobj(struct device_driver *drv,
					struct kobject *kobj,
					const char *fmt, ...);

extern int __must_check driver_for_each_device(struct device_driver *drv,
					       struct device *start,
					       void *data,
					       int (*fn)(struct device *dev,
							 void *));
struct device *driver_find_device(struct device_driver *drv,
				  struct device *start, void *data,
				  int (*match)(struct device *dev, void *data));



struct class_dev_iter {
	struct klist_iter		ki;
	const struct device_type	*type;
};

extern struct kobject *sysfs_dev_block_kobj;
extern struct kobject *sysfs_dev_char_kobj;
extern int __must_check __class_register(struct class *class,
					 struct lock_class_key *key);
extern void class_unregister(struct class *class);

/* This is a #define to keep the compiler from merging different
 * instances of the __key variable */
#define class_register(class)			\
({						\
	static struct lock_class_key __key;	\
	__class_register(class, &__key);	\
})

struct class_compat;
struct class_compat *class_compat_register(const char *name);
void class_compat_unregister(struct class_compat *cls);
int class_compat_create_link(struct class_compat *cls, struct device *dev,
			     struct device *device_link);
void class_compat_remove_link(struct class_compat *cls, struct device *dev,
			      struct device *device_link);

extern void class_dev_iter_init(struct class_dev_iter *iter,
				struct class *class,
				struct device *start,
				const struct device_type *type);
extern struct device *class_dev_iter_next(struct class_dev_iter *iter);
extern void class_dev_iter_exit(struct class_dev_iter *iter);

extern int class_for_each_device(struct class *class, struct device *start,
				 void *data,
				 int (*fn)(struct device *dev, void *data));
extern struct device *class_find_device(struct class *class,
					struct device *start, void *data,
					int (*match)(struct device *, void *));

struct class_attribute {
	struct attribute attr;
	ssize_t (*show)(struct class *class, struct class_attribute *attr,
			char *buf);
	ssize_t (*store)(struct class *class, struct class_attribute *attr,
			const char *buf, size_t count);
};

//���ں��У�sysfs ����һ������ __ATTR ϵ�еĺ��������ģ�����豸��ʹ�� DEVICE_ATTR ��
//������ʹ�� BUS_ATTR ��������ʹ��DRIVER_ATTR �������(class)ʹ�� CLASS_ATTR,
//���������ĸ��������ֱ������ơ�Ȩ��λ����������д���������ж�������д�����Ƕ�д���ܺ����ĺ�������
#define CLASS_ATTR(_name, _mode, _show, _store)			\
struct class_attribute class_attr_##_name = __ATTR(_name, _mode, _show, _store)

extern int __must_check class_create_file(struct class *class,
					  const struct class_attribute *attr);
extern void class_remove_file(struct class *class,
			      const struct class_attribute *attr);

/* Simple class attribute that is just a static string */

struct class_attribute_string {
	struct class_attribute attr;
	char *str;
};

/* Currently read-only only */
#define _CLASS_ATTR_STRING(_name, _mode, _str) \
	{ __ATTR(_name, _mode, show_class_attr_string, NULL), _str }
#define CLASS_ATTR_STRING(_name, _mode, _str) \
	struct class_attribute_string class_attr_##_name = \
		_CLASS_ATTR_STRING(_name, _mode, _str)

extern ssize_t show_class_attr_string(struct class *class, struct class_attribute *attr,
                        char *buf);

struct class_interface {
	struct list_head	node;
	struct class		*class;

	int (*add_dev)		(struct device *, struct class_interface *);
	void (*remove_dev)	(struct device *, struct class_interface *);
};

extern int __must_check class_interface_register(struct class_interface *);
extern void class_interface_unregister(struct class_interface *);

extern struct class * __must_check __class_create(struct module *owner,
						  const char *name,
						  struct lock_class_key *key);
extern void class_destroy(struct class *cls);

/* This is a #define to keep the compiler from merging different
 * instances of the __key variable */
#define class_create(owner, name)		\
({						\
	static struct lock_class_key __key;	\
	__class_create(owner, name, &__key);	\
})

/*
 * The type of device, "struct device" is embedded in. A class
 * or bus can contain devices of different types
 * like "partitions" and "disks", "mouse" and "event".
 * This identifies the device type and carries type-specific
 * information, equivalent to the kobj_type of a kobject.
 * If "name" is specified, the uevent will contain it in
 * the DEVTYPE variable.
 */
struct device_type {
	const char *name;
	const struct attribute_group **groups;
	int (*uevent)(struct device *dev, struct kobj_uevent_env *env);
	char *(*devnode)(struct device *dev, mode_t *mode);
	void (*release)(struct device *dev);

	const struct dev_pm_ops *pm;
};

/* interface for exporting device attributes */
struct device_attribute {//�豸���Խṹ�壺����bus_attribute
	struct attribute	attr;
	ssize_t (*show)(struct device *dev, struct device_attribute *attr,
			char *buf);
	ssize_t (*store)(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);
};

#define DEVICE_ATTR(_name, _mode, _show, _store) \
struct device_attribute dev_attr_##_name = __ATTR(_name, _mode, _show, _store)

extern int __must_check device_create_file(struct device *device,
					const struct device_attribute *entry);
extern void device_remove_file(struct device *dev,
			       const struct device_attribute *attr);
extern int __must_check device_create_bin_file(struct device *dev,
					const struct bin_attribute *attr);
extern void device_remove_bin_file(struct device *dev,
				   const struct bin_attribute *attr);
extern int device_schedule_callback_owner(struct device *dev,
		void (*func)(struct device *dev), struct module *owner);

/* This is a macro to avoid include problems with THIS_MODULE */
#define device_schedule_callback(dev, func)			\
	device_schedule_callback_owner(dev, func, THIS_MODULE)

/* device resource management */
typedef void (*dr_release_t)(struct device *dev, void *res);
typedef int (*dr_match_t)(struct device *dev, void *res, void *match_data);

#ifdef CONFIG_DEBUG_DEVRES
extern void *__devres_alloc(dr_release_t release, size_t size, gfp_t gfp,
			     const char *name);
#define devres_alloc(release, size, gfp) \
	__devres_alloc(release, size, gfp, #release)
#else
extern void *devres_alloc(dr_release_t release, size_t size, gfp_t gfp);
#endif
extern void devres_free(void *res);
extern void devres_add(struct device *dev, void *res);
extern void *devres_find(struct device *dev, dr_release_t release,
			 dr_match_t match, void *match_data);
extern void *devres_get(struct device *dev, void *new_res,
			dr_match_t match, void *match_data);
extern void *devres_remove(struct device *dev, dr_release_t release,
			   dr_match_t match, void *match_data);
extern int devres_destroy(struct device *dev, dr_release_t release,
			  dr_match_t match, void *match_data);

/* devres group */
extern void * __must_check devres_open_group(struct device *dev, void *id,
					     gfp_t gfp);
extern void devres_close_group(struct device *dev, void *id);
extern void devres_remove_group(struct device *dev, void *id);
extern int devres_release_group(struct device *dev, void *id);

/* managed kzalloc/kfree for device drivers, no kmalloc, always use kzalloc */
extern void *devm_kzalloc(struct device *dev, size_t size, gfp_t gfp);
extern void devm_kfree(struct device *dev, void *p);

struct device_dma_parameters {
	/*
	 * a low level driver may set these to teach IOMMU code about
	 * sg limitations.
	 */
	unsigned int max_segment_size;
	unsigned long segment_boundary_mask;
};


/* Get the wakeup routines, which depend on struct device */
//#include <linux/pm_wakeup.h>

static inline const char *dev_name(const struct device *dev)
{
	/* Use the init name until the kobject becomes available */
	if (dev->init_name)
		return dev->init_name;

	return kobject_name(&dev->kobj);
}

extern int dev_set_name(struct device *dev, const char *name, ...)
			__attribute__((format(printf, 2, 3)));

#ifdef CONFIG_NUMA
static inline int dev_to_node(struct device *dev)
{
	return dev->numa_node;
}
static inline void set_dev_node(struct device *dev, int node)
{
	dev->numa_node = node;
}
#else
static inline int dev_to_node(struct device *dev)
{
	return -1;
}
static inline void set_dev_node(struct device *dev, int node)
{
}
#endif

static inline unsigned int dev_get_uevent_suppress(const struct device *dev)
{
	return dev->kobj.uevent_suppress;
}

static inline void dev_set_uevent_suppress(struct device *dev, int val)
{
	dev->kobj.uevent_suppress = val;
}

static inline int device_is_registered(struct device *dev)
{
	return dev->kobj.state_in_sysfs;
}

static inline void device_enable_async_suspend(struct device *dev)
{
	if (dev->power.status == DPM_ON)
		dev->power.async_suspend = true;
}

static inline void device_disable_async_suspend(struct device *dev)
{
	if (dev->power.status == DPM_ON)
		dev->power.async_suspend = false;
}

static inline bool device_async_suspend_enabled(struct device *dev)
{
	return !!dev->power.async_suspend;
}

static inline void device_lock(struct device *dev)
{
	mutex_lock(&dev->mutex);
}

static inline int device_trylock(struct device *dev)
{
	return mutex_trylock(&dev->mutex);
}

static inline void device_unlock(struct device *dev)
{
	mutex_unlock(&dev->mutex);
}

void driver_init(void);

/*
 * High level routines for use by the bus drivers
 */
extern int __must_check device_register(struct device *dev);
extern void device_unregister(struct device *dev);
extern void device_initialize(struct device *dev);
extern int __must_check device_add(struct device *dev);
extern void device_del(struct device *dev);
extern int device_for_each_child(struct device *dev, void *data,
		     int (*fn)(struct device *dev, void *data));
extern struct device *device_find_child(struct device *dev, void *data,
				int (*match)(struct device *dev, void *data));
extern int device_rename(struct device *dev, char *new_name);
extern int device_move(struct device *dev, struct device *new_parent,
		       enum dpm_order dpm_order);
extern const char *device_get_devnode(struct device *dev,
				      mode_t *mode, const char **tmp);
extern void *dev_get_drvdata(const struct device *dev);
extern void dev_set_drvdata(struct device *dev, void *data);

/*
 * Root device objects for grouping under /sys/devices
 */
extern struct device *__root_device_register(const char *name,
					     struct module *owner);
static inline struct device *root_device_register(const char *name)
{
	return __root_device_register(name, THIS_MODULE);
}
extern void root_device_unregister(struct device *root);

static inline void *dev_get_platdata(const struct device *dev)
{
	return dev->platform_data;
}

/*
 * Manual binding of a device to driver. See drivers/base/bus.c
 * for information on use.
 */
extern int __must_check device_bind_driver(struct device *dev);
extern void device_release_driver(struct device *dev);
extern int  __must_check device_attach(struct device *dev);
extern int __must_check driver_attach(struct device_driver *drv);
extern int __must_check device_reprobe(struct device *dev);

/*
 * Easy functions for dynamically creating devices on the fly
 */
extern struct device *device_create_vargs(struct class *cls,
					  struct device *parent,
					  dev_t devt,
					  void *drvdata,
					  const char *fmt,
					  va_list vargs);
extern struct device *device_create(struct class *cls, struct device *parent,
				    dev_t devt, void *drvdata,
				    const char *fmt, ...)
				    __attribute__((format(printf, 5, 6)));
extern void device_destroy(struct class *cls, dev_t devt);

/*
 * Platform "fixup" functions - allow the platform to have their say
 * about devices and actions that the general device layer doesn't
 * know about.
 */
/* Notify platform of device discovery */
extern int (*platform_notify)(struct device *dev);

extern int (*platform_notify_remove)(struct device *dev);


/**
 * get_device - atomically increment the reference count for the device.
 *
 */
extern struct device *get_device(struct device *dev);
extern void put_device(struct device *dev);

extern void wait_for_device_probe(void);

#ifdef CONFIG_DEVTMPFS
extern int devtmpfs_create_node(struct device *dev);
extern int devtmpfs_delete_node(struct device *dev);
extern int devtmpfs_mount(const char *mntdir);
#else
static inline int devtmpfs_create_node(struct device *dev) { return 0; }
static inline int devtmpfs_delete_node(struct device *dev) { return 0; }
static inline int devtmpfs_mount(const char *mountpoint) { return 0; }
#endif

/* drivers/base/power/shutdown.c */
extern void device_shutdown(void);

/* drivers/base/sys.c */
extern void sysdev_shutdown(void);

/* debugging and troubleshooting/diagnostic helpers. */
extern const char *dev_driver_string(const struct device *dev);
#define dev_printk(level, dev, format, arg...)	\
	printk(level "%s %s: " format , dev_driver_string(dev) , \
	       dev_name(dev) , ## arg)

#define dev_emerg(dev, format, arg...)		\
	dev_printk(KERN_EMERG , dev , format , ## arg)
#define dev_alert(dev, format, arg...)		\
	dev_printk(KERN_ALERT , dev , format , ## arg)
#define dev_crit(dev, format, arg...)		\
	dev_printk(KERN_CRIT , dev , format , ## arg)
#define dev_err(dev, format, arg...)		\
	dev_printk(KERN_ERR , dev , format , ## arg)
#define dev_warn(dev, format, arg...)		\
	dev_printk(KERN_WARNING , dev , format , ## arg)
#define dev_notice(dev, format, arg...)		\
	dev_printk(KERN_NOTICE , dev , format , ## arg)
#define dev_info(dev, format, arg...)		\
	dev_printk(KERN_INFO , dev , format , ## arg)

#if defined(DEBUG)
#define dev_dbg(dev, format, arg...)		\
	dev_printk(KERN_DEBUG , dev , format , ## arg)
#elif defined(CONFIG_DYNAMIC_DEBUG)
#define dev_dbg(dev, format, ...) do { \
	dynamic_dev_dbg(dev, format, ##__VA_ARGS__); \
	} while (0)
#else
#define dev_dbg(dev, format, arg...)		\
	({ if (0) dev_printk(KERN_DEBUG, dev, format, ##arg); 0; })
#endif

#ifdef VERBOSE_DEBUG
#define dev_vdbg	dev_dbg
#else

#define dev_vdbg(dev, format, arg...)		\
	({ if (0) dev_printk(KERN_DEBUG, dev, format, ##arg); 0; })
#endif

/*
 * dev_WARN() acts like dev_printk(), but with the key difference
 * of using a WARN/WARN_ON to get the message out, including the
 * file/line information and a backtrace.
 */
#define dev_WARN(dev, format, arg...) \
	WARN(1, "Device: %s\n" format, dev_driver_string(dev), ## arg);

/* Create alias, so I can be autoloaded. */
#define //MODULE_ALIAS_CHARDEV(major,minor) \
	//MODULE_ALIAS("char-major-" __stringify(major) "-" __stringify(minor))
#define //MODULE_ALIAS_CHARDEV_MAJOR(major) \
	//MODULE_ALIAS("char-major-" __stringify(major) "-*")
#endif /* _DEVICE_H_ */
