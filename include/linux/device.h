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



struct bus_attribute {//总线属性结构体
	struct attribute	attr;//属性结构体
	//show方法实现数据读取。当用户空间读取属性值时，核心调用该方法实现编码，结果存放在形参buf中
	ssize_t (*show)(struct bus_type *bus, char *buf);
	//store方法实现数据保存。当用户控件设置属性值时，核心调用该方法实现解码，使用buf传递的数据解码，count指示buf传递的数据长度
	ssize_t (*store)(struct bus_type *bus, const char *buf, size_t count);
};
//在内核中，sysfs 属性一般是由 __ATTR 系列的宏来声明的，如对设备的使用 DEVICE_ATTR ，
//对总线使用 BUS_ATTR ，对驱动使用DRIVER_ATTR ，对类别(class)使用 CLASS_ATTR,
//DEVICE_ATTR 宏声明有四个参数，分别是名称、权限位、读函数、写函数。其中读函数和写函数是读写功能函数的函数名。
#define BUS_ATTR(_name, _mode, _show, _store)	\
struct bus_attribute bus_attr_##_name = __ATTR(_name, _mode, _show, _store)

extern int __must_check bus_create_file(struct bus_type *,
					struct bus_attribute *);
extern void bus_remove_file(struct bus_type *, struct bus_attribute *);


/*====================================================================
Linux设备模型中三个很重要的概念就是总线,设备,驱动.即bus,device,driver,而实际上内核
中也定义了这么一些数据结构,他们是 struct bus_type,struct device,struct device_driver,
这三个重要的数据结构都来自一个地方,include/linux/device.h.我们知道总线有很多种,pci
总线,scsi总线,usb 总线,所以我们会看到 Linux 内核代码中出现
pci_bus_type,scsi_bus_type,usb_bus_type,他们都是struct bus_type类型的变量.而
struct bus_type结构中两个非常重要的成员就是 struct kset drivers 和 struct kset devices.
kset 和另一个叫做 kobject正是 Linux Kernel 2.6中设备模型的基本元素,但此处我
们却不愿多讲,因为暂时不用去认识他们.我们的生命中会遇见许许多多的人和事,但更多的人和
事与我们只是擦肩而过,只是我们生命中的过客而已.在我们人生的电影中,他们也许只有一个镜
头,甚至那一个镜头后来也被剪辑掉了.这里我们只需要知道,drivers 和 devices 的存在,让
struct bus_type与两个链表联系了起来,一个是 devices 的链表,一个是drivers 的链表,也就
是说,知道一条总线所对应的数据结构,就可以找到这条总线所关联的设备有哪些,又有哪些支持
这类设备的驱动程序. 

而要实现这些,就要求每次出现一个设备就要向总线汇报,或者说注册,每次出现一个驱动,也要向
总线汇报,或者说注册.比如系统初始化的时候,会扫描连接了哪些设备,并为每一个设备建立起一
个 struct device的变量,每一次有一个驱动程序,就要准备一个 struct device_driver结构的
变量.把这些变量统统加入相应的链表,device插入devices链表,driver插入drivers链表. 这
样通过总线就能找到每一个设备,每一个驱动.

,关于 bus,关于 device,关于 driver,他们是如何建立联系的呢?换言之,这三个
数据结构中的指针是如何被赋值的?具体到usb 系统,完成这个工作的就是
usb core.usb core的代码会进行整个 usb 系统的初始化,比如申请struct bus_type 
usb_bus_type,然后会扫描 usb 总线,看线上连接了哪些usb设备,或者说 root hub上连了哪
些usb设备,那么 drivers链表呢?这个就不用bus方面主动了,而该由每一个 driver 本身去 bus上面登记,
或者说挂牌.具体到usb系统,每一个usb设备的驱动程序都会有一个 struct usb_driver结构
体,其代码如下,来自 include/linux/usb.h 

====================================================================*/

struct bus_type {//设备和驱动之间是如何联系的？总线，这就是总线的作用！
	const char		*name;//总线名称，体现在sysfs文件系统的/sys/bus下，不能和别的总线名称有冲突。
	struct bus_attribute	*bus_attrs;//总线属性。表现为/sys/bus/<name>/文件夹下的文件。
	struct device_attribute	*dev_attrs;//该总线上所有设备的默认属性。
	struct driver_attribute	*drv_attrs;//该总线上所有驱动的默认属性。

	//每当有设备添加到总线时，驱动核心遍历总线上的驱动链表
	//（执行流程device_register->device_add->bus_probe_device->device_attach->bus_for_each_drv->match/probe）查找设备驱动；
	//每当有驱动添加到总线时，驱动核心遍历总线上的设备链表
	//（执行流程driver_register->bus_add_driver->driver_attach->bus_for_each_dev->match/probe）查找驱动可操控的设备。
	//当前，match一般只执行总线特定的匹配处理，而在probe中，通过回调设备驱动probe，完成设备特定的匹配、设备初始化等。
	//举例来说，对于PCI总线，match判断驱动支持的ID列表是否包含设备ID，如果包含则匹配，否则失配；
	//probe会再次执行ID匹配判断，并回调驱动提供的probe函数。
	//对于一次遍历匹配而言，如果match和probe均成功，则结束匹配过程；如果match成功而probe失配，继续遍历查找匹配；
	//如果遍历结束而没有找到成功的匹配，对于驱动而言表示没有可操控设备，对于设备而言表示没有适当的驱动。
	int (*match)(struct device *dev, struct device_driver *drv);//驱动匹配。判定设备和驱动是否匹配，是总线体系相关的。驱动核心通过match和probe两个函数来完成匹配

	//在发送热插拔事件消息到用户空间之前添加环境变量。在设备注册、移除，或者状态更改时，
	//内核负责发送通知事件到用户空间。通过man udev和man udevd可获取相关帮助。uevent在事件发
	//送到用户空间之前调用，用来给事件添加总线特定的环境变量。在Linux-2.6.13以后，采用udev机制动态创建设备文件
	int (*uevent)(struct device *dev, struct kobj_uevent_env *env);//添加环境变量。

	//如在match中所述，probe执行设备相关的匹配探测、设备初始化、资源分配等。需要注意，
	//在probe调用时，dev->driver已经被设置为match成功匹配的驱动指针了，因此不再需要struct device_driver指针.
	int (*probe)(struct device *dev);//探测函数

	//设备移除时，调用该方法，完成部分清理工作。如删除设备驱动中，设备链表下的该设备。
	int (*remove)(struct device *dev);//设备移除时调用。

	//系统关机时，调用该方法关闭设备。
	void (*shutdown)(struct device *dev);//关机时调用。

	//设备休眠（挂起）时调用该方法。一般在该方法中设置设备为低耗电状态。
	int (*suspend)(struct device *dev, pm_message_t state);//挂起（投入休眠）时调用。

	//设备从休眠中恢复时调用该方法
	int (*resume)(struct device *dev);//恢复时调用。

	//一些设备有电源状态转换。结构体内部提供很多方法实现这个过程。暂时忽略这个结构体。
	const struct dev_pm_ops *pm;//设备电源管理。

	//驱动核心设置并使用，总线驱动不必关心这个成员，并且一般不要去修改它
	struct bus_type_private *p;//私有数据。完全由驱动核心初始化并使用。
};

//设备和驱动是严格区分的，设备是设备，驱动是驱动，设备通过struct device来定义，
//当然用户也可以将该结构体封装到自己定义的device结构体中，例如，struct platform_device，
struct device {//设备结构体：用于描述设备相关的信息设备之间的层次关系，以及设备与总线、驱动的关系
	struct device		*parent;//父设备

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
	void		*platform_data;	/* 平台特殊数据Platform specific data, device
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


struct device_driver {//设备驱动结构体：设备是设备，驱动是驱动，设备通过struct device来定义，驱动用struct device_driver定义
	//设备驱动程序的名称。在调用driver_register()往设备驱动程序模型中插入一个新
	//的device_driver对象时，driver_register()函数会调用bus_add_driver()函数，
	//bus_add_driver()调用kobject_set_name()函数将name赋给drv>kobj.name或者drv->kobj.k_name。
	const char		*name;//设备驱动程序的名称。
	
	struct bus_type		*bus;//指向总线描述符的指针，总线连接所支持的设备。

	//表示实现设备驱动程序的模块。也就是在该驱动的实现中，如果使用了模块，那么该域就指向你所写的模块，并使用mod_name域指向模块名。如果没有使用模块，那该域就为空。还有该结构中的module_kobject类型的mkobj也是与owner有关的域。
	struct module		*owner;
	const char		*mod_name;	/* used for built-in modules */

	bool suppress_bind_attrs;	/* disables bind/unbind via sysfs */

	//这五个回调函数用于处理热插拔、即插即用和电源管理。
	//当总线设备驱动程序发现一个可能有它处理的设备时就会调用probe方法，相应的函数将会探测硬件，
	//从而对该设备进行更进一步的检查。如果该device_driver对象的pribe()方法的返回值是一个负数，
	//那就意味这该驱动不能邦定到此设备上，那么就要释放所有为该device_driver对象分配的资源。     
	//当移走一个可热插拔的设备时驱动程序会调用remove方法，而驱动程序本身被卸载时，
	//它所处理的每个设备也会调用remove方法。当内核必须更改设备的供电状态时，
	//设备驱动会调用shutdown、suspend和resume三个方法。其中shutdown方法会停止对设备供电。
	//suspend方法是将设备切换到低功耗状态，
	int (*probe) (struct device *dev);
	int (*remove) (struct device *dev);
	void (*shutdown) (struct device *dev);
	int (*suspend) (struct device *dev, pm_message_t state);
	int (*resume) (struct device *dev);
	
	const struct attribute_group **groups;

	const struct dev_pm_ops *pm;//设备电源管理。

	struct driver_private *p;//私有数据。完全由驱动核心初始化并使用。
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

struct driver_attribute {//驱动属性结构体：类似bus_attribute
	struct attribute attr;
	ssize_t (*show)(struct device_driver *driver, char *buf);
	ssize_t (*store)(struct device_driver *driver, const char *buf,
			 size_t count);
};
//在内核中，sysfs 属性一般是由 __ATTR 系列的宏来声明的，如对设备的使用 DEVICE_ATTR ，
//对总线使用 BUS_ATTR ，对驱动使用DRIVER_ATTR ，对类别(class)使用 CLASS_ATTR,
//宏声明有四个参数，分别是名称、权限位、读函数、写函数。其中读函数和写函数是读写功能函数的函数名。
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

//在内核中，sysfs 属性一般是由 __ATTR 系列的宏来声明的，如对设备的使用 DEVICE_ATTR ，
//对总线使用 BUS_ATTR ，对驱动使用DRIVER_ATTR ，对类别(class)使用 CLASS_ATTR,
//宏声明有四个参数，分别是名称、权限位、读函数、写函数。其中读函数和写函数是读写功能函数的函数名。
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
struct device_attribute {//设备属性结构体：类似bus_attribute
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
