/*
 * kobject.h - generic kernel object infrastructure.
 * 设备模型kobject的相关操作=======================zjz
 * Copyright (c) 2002-2003 Patrick Mochel
 * Copyright (c) 2002-2003 Open Source Development Labs
 * Copyright (c) 2006-2008 Greg Kroah-Hartman <greg@kroah.com>
 * Copyright (c) 2006-2008 Novell Inc.
 *
 * This file is released under the GPLv2.
 *
 * Please read Documentation/kobject.txt before using the kobject
 * interface, ESPECIALLY the parts about reference counts and object
 * destructors.
 */

#ifndef _KOBJECT_H_
#define _KOBJECT_H_

//#include <linux/types.h>
//#include <linux/list.h>
//#include <linux/sysfs.h>
//#include <linux/compiler.h>
//#include <linux/spinlock.h>
//#include <linux/kref.h>
//#include <linux/kernel.h>
//#include <linux/wait.h>
//#include <asm/atomic.h>

#define UEVENT_HELPER_PATH_LEN		256
#define UEVENT_NUM_ENVP			32	/* number of env pointers */
#define UEVENT_BUFFER_SIZE		2048	/* buffer for the variables */

/* path to the userspace helper executed on an event */
extern char uevent_helper[];

/* counter to tag the uevent, read only except for the kobject core */
extern u64 uevent_seqnum;

/*
 * The actions here must match the index to the string array
 * in lib/kobject_uevent.c
 *
 * Do not add new actions here without checking with the driver-core
 * maintainers. Action strings are not meant to express subsystem
 * or device specific properties. In most cases you want to send a
 * kobject_uevent_env(kobj, KOBJ_CHANGE, env) with additional event
 * specific variables added to the event environment.
 */
enum kobject_action {
	KOBJ_ADD,
	KOBJ_REMOVE,
	KOBJ_CHANGE,
	KOBJ_MOVE,
	KOBJ_ONLINE,
	KOBJ_OFFLINE,
	KOBJ_MAX
};


/**
 * struct kset - a set of kobjects of a specific type, belonging to a specific subsystem.
 *
 * A kset defines a group of kobjects.  They can be individually
 * different "types" but overall these kobjects all want to be grouped
 * together and operated on in the same manner.  ksets are used to
 * define the attribute callbacks and other common events that happen to
 * a kobject.
 *
 * @list: the list of all kobjects for this kset
 * @list_lock: a lock for iterating over the kobjects
 * @kobj: the embedded kobject for this kset (recursion, isn't it fun...)
 * @uevent_ops: the set of uevent operations for this kset.  These are
 * called whenever a kobject has something happen to it so that the kset
 * can add new environment variables, or filter out the uevents if so
 * desired.
kset 和另一个叫做 kobject正是 Linux Kernel 2.6中设备模型的基本元素,但此处我
们却不愿多讲,因为暂时不用去认识他们.我们的生命中会遇见许许多多的人和事,但更多的人和
事与我们只是擦肩而过,只是我们生命中的过客而已.在我们人生的电影中,他们也许只有一个镜
头,甚至那一个镜头后来也被剪辑掉了.这里我们只需要知道,drivers 和 devices 的存在,让
struct bus_type与两个链表联系了起来,一个是 devices 的链表,一个是drivers 的链表,也就
是说,知道一条总线所对应的数据结构,就可以找到这条总线所关联的设备有哪些,又有哪些支持
这类设备的驱动程序. */
struct kset {//Kobject通常通过kset组织成层次化的结构，kset是具有相同类型的kobject的集合，在内核中用kset数据结构表示
	struct list_head list;//用于连接该kset中所有kobject的链表头
	spinlock_t list_lock;
	struct kobject kobj;//嵌入的kobject
	const struct kset_uevent_ops *uevent_ops;
};

//Kobject 是Linux 2.6引入的新的设备管理机制，在内核中由struct kobject表示。
//通过这个数据结构使所有设备在底层都具有统一的接口，kobject提供基本的对象管理，
//是构成Linux 2.6设备模型的核心结构，它与sysfs文件系统紧密关联，每个在内核中注册
//的kobject对象都对应于sysfs文件系统中的一个目录。
struct kobject {//内核对象
	const char		*name;//指向设备名称的指针
	struct list_head	entry;//挂接到所在kset中去的单元
	struct kobject		*parent;//指向父对象的指针
	struct kset		*kset;//所属kset的指针
	struct kobj_type	*ktype;//指向其对象类型描述符的指针
	struct sysfs_dirent	*sd;//
	struct kref		kref;//对象引用计数
	unsigned int state_initialized:1;//
	unsigned int state_in_sysfs:1;//
	unsigned int state_add_uevent_sent:1;//
	unsigned int state_remove_uevent_sent:1;//
	unsigned int uevent_suppress:1;//
};

extern int kobject_set_name(struct kobject *kobj, const char *name, ...)
			    __attribute__((format(printf, 2, 3)));
extern int kobject_set_name_vargs(struct kobject *kobj, const char *fmt,
				  va_list vargs);

static inline const char *kobject_name(const struct kobject *kobj)
{
	return kobj->name;
}

extern void kobject_init(struct kobject *kobj, struct kobj_type *ktype);
extern int __must_check kobject_add(struct kobject *kobj,
				    struct kobject *parent,
				    const char *fmt, ...);
extern int __must_check kobject_init_and_add(struct kobject *kobj,
					     struct kobj_type *ktype,
					     struct kobject *parent,
					     const char *fmt, ...);

extern void kobject_del(struct kobject *kobj);

extern struct kobject * __must_check kobject_create(void);
extern struct kobject * __must_check kobject_create_and_add(const char *name,
						struct kobject *parent);

extern int __must_check kobject_rename(struct kobject *, const char *new_name);
extern int __must_check kobject_move(struct kobject *, struct kobject *);

extern struct kobject *kobject_get(struct kobject *kobj);
extern void kobject_put(struct kobject *kobj);
//kobject_get()、kobject_put()分别用于增加和减少引用计数，
//当引用计数为 0 时，所有该对象使用的资源将被释放。 
extern char *kobject_get_path(struct kobject *kobj, gfp_t flag);

struct kobj_type {
	void (*release)(struct kobject *kobj);//：用于释放 kobject 占用的资源
	const struct sysfs_ops *sysfs_ops;//、指向sysfs操作的 sysfs_ops指针
	struct attribute **default_attrs;//sysfs文件系统默认属性列表。
	const struct kobj_ns_type_operations *(*child_ns_type)(struct kobject *kobj);
	const void *(*namespace)(struct kobject *kobj);
};

struct kobj_uevent_env {
	char *envp[UEVENT_NUM_ENVP];
	int envp_idx;
	char buf[UEVENT_BUFFER_SIZE];
	int buflen;
};

struct kset_uevent_ops {
	int (* const filter)(struct kset *kset, struct kobject *kobj);
	const char *(* const name)(struct kset *kset, struct kobject *kobj);
	int (* const uevent)(struct kset *kset, struct kobject *kobj,
		      struct kobj_uevent_env *env);
};

struct kobj_attribute {
	struct attribute attr;
	ssize_t (*show)(struct kobject *kobj, struct kobj_attribute *attr,
			char *buf);
	ssize_t (*store)(struct kobject *kobj, struct kobj_attribute *attr,
			 const char *buf, size_t count);
};

extern const struct sysfs_ops kobj_sysfs_ops;

/*
 * Namespace types which are used to tag kobjects and sysfs entries.
 * Network namespace will likely be the first.
 */
enum kobj_ns_type {
	KOBJ_NS_TYPE_NONE = 0,
	KOBJ_NS_TYPE_NET,
	KOBJ_NS_TYPES
};

struct sock;

/*
 * Callbacks so sysfs can determine namespaces
 *   @current_ns: return calling task's namespace
 *   @netlink_ns: return namespace to which a sock belongs (right?)
 *   @initial_ns: return the initial namespace (i.e. init_net_ns)
 */
struct kobj_ns_type_operations {
	enum kobj_ns_type type;
	const void *(*current_ns)(void);
	const void *(*netlink_ns)(struct sock *sk);
	const void *(*initial_ns)(void);
};

int kobj_ns_type_register(const struct kobj_ns_type_operations *ops);
int kobj_ns_type_registered(enum kobj_ns_type type);
const struct kobj_ns_type_operations *kobj_child_ns_ops(struct kobject *parent);
const struct kobj_ns_type_operations *kobj_ns_ops(struct kobject *kobj);

const void *kobj_ns_current(enum kobj_ns_type type);
const void *kobj_ns_netlink(enum kobj_ns_type type, struct sock *sk);
const void *kobj_ns_initial(enum kobj_ns_type type);
void kobj_ns_exit(enum kobj_ns_type type, const void *ns);




extern void kset_init(struct kset *kset);
extern int __must_check kset_register(struct kset *kset);
extern void kset_unregister(struct kset *kset);
extern struct kset * __must_check kset_create_and_add(const char *name,
						const struct kset_uevent_ops *u,
						struct kobject *parent_kobj);

static inline struct kset *to_kset(struct kobject *kobj)
{
	return kobj ? container_of(kobj, struct kset, kobj) : NULL;
}

static inline struct kset *kset_get(struct kset *k)
{
	return k ? to_kset(kobject_get(&k->kobj)) : NULL;
}

static inline void kset_put(struct kset *k)
{
	kobject_put(&k->kobj);
}

static inline struct kobj_type *get_ktype(struct kobject *kobj)
{
	return kobj->ktype;
}

extern struct kobject *kset_find_obj(struct kset *, const char *);

/* The global /sys/kernel/ kobject for people to chain off of */
extern struct kobject *kernel_kobj;
/* The global /sys/kernel/mm/ kobject for people to chain off of */
extern struct kobject *mm_kobj;
/* The global /sys/hypervisor/ kobject for people to chain off of */
extern struct kobject *hypervisor_kobj;
/* The global /sys/power/ kobject for people to chain off of */
extern struct kobject *power_kobj;
/* The global /sys/firmware/ kobject for people to chain off of */
extern struct kobject *firmware_kobj;

#if defined(CONFIG_HOTPLUG)
int kobject_uevent(struct kobject *kobj, enum kobject_action action);
int kobject_uevent_env(struct kobject *kobj, enum kobject_action action,
			char *envp[]);

int add_uevent_var(struct kobj_uevent_env *env, const char *format, ...)
	__attribute__((format (printf, 2, 3)));

int kobject_action_type(const char *buf, size_t count,
			enum kobject_action *type);
#else
static inline int kobject_uevent(struct kobject *kobj,
				 enum kobject_action action)
{ return 0; }
static inline int kobject_uevent_env(struct kobject *kobj,
				      enum kobject_action action,
				      char *envp[])
{ return 0; }

static inline int add_uevent_var(struct kobj_uevent_env *env,
				 const char *format, ...)
{ return 0; }

static inline int kobject_action_type(const char *buf, size_t count,
				      enum kobject_action *type)
{ return -EINVAL; }
#endif

#endif /* _KOBJECT_H_ */
