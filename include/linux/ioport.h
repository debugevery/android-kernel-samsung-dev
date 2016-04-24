/*
 * ioport.h	Definitions of routines for detecting, reserving and
 *		allocating system resources.
 *
 * Authors:	Linus Torvalds
 */

#ifndef _LINUX_IOPORT_H
#define _LINUX_IOPORT_H

#ifndef __ASSEMBLY__
//#include <linux/compiler.h>
//#include <linux/types.h>
/*
 * Resources are tree-like, allowing
 * nesting etc..
 */
struct resource {//通常关心start、end和flags这3个字段，分别标明资源的开始值、结束值和类型
	resource_size_t start;
	resource_size_t end;
	const char *name;
	unsigned long flags;
	struct resource *parent, *sibling, *child;
};
//flags:资源标记，用于标识各种资源,可以为IORESOURCE_IO、 IORESOURCE_MEM、IORESOURCE_IRQ、IORESOURCE_DMA等。
//例如IORESOURCE_MEM表示内存资源，IORESOURCE_IRQ表示中断资源

//start、end的含义会随着flags而变更，如当 flags为IORESOURCE_MEM时，start、end分别表示该platform_device占据的内存的开始地址和结束地址；
//当 flags为IORESOURCE_IRQ时，start、end分别表示该platform_device使用的中断号的开始值和结束值，如果只使用了 
// 1个中断号，开始和结束值相同。对于同种类型的资源而言，可以有多份，譬如说某设备
//占据了2个内存区域，则可以定义2个IORESOURCE_MEM资 源。
struct resource_list {
	struct resource_list *next;
	struct resource *res;
	struct pci_dev *dev;
};

/*
 * IO resources have these defined flags.
 */
 //属性flags是个unsigned long类型的32位标志值，用以描述资源的属性。比如：资源的
 //类型、是否只读、是否可缓存，及是否已被占用等。下面是一部分常用属性标志位的
 //定义（ioport.h）：
#define IORESOURCE_BITS		0x000000ff	/* Bus-specific bits */

#define IORESOURCE_TYPE_BITS	0x00001f00	/* Resource type */
#define IORESOURCE_IO		0x00000100
#define IORESOURCE_MEM		0x00000200
#define IORESOURCE_IRQ		0x00000400
#define IORESOURCE_DMA		0x00000800
#define IORESOURCE_BUS		0x00001000

#define IORESOURCE_PREFETCH	0x00002000	/* No side effects */
#define IORESOURCE_READONLY	0x00004000
#define IORESOURCE_CACHEABLE	0x00008000
#define IORESOURCE_RANGELENGTH	0x00010000
#define IORESOURCE_SHADOWABLE	0x00020000

#define IORESOURCE_SIZEALIGN	0x00040000	/* size indicates alignment */
#define IORESOURCE_STARTALIGN	0x00080000	/* start field is alignment */

#define IORESOURCE_MEM_64	0x00100000
#define IORESOURCE_WINDOW	0x00200000	/* forwarded by bridge */
#define IORESOURCE_MUXED	0x00400000	/* Resource is software muxed */

#define IORESOURCE_EXCLUSIVE	0x08000000	/* Userland may not map this resource */
#define IORESOURCE_DISABLED	0x10000000
#define IORESOURCE_UNSET	0x20000000
#define IORESOURCE_AUTO		0x40000000
#define IORESOURCE_BUSY		0x80000000	/* Driver has marked this resource busy */

/* PnP IRQ specific bits (IORESOURCE_BITS) */
#define IORESOURCE_IRQ_HIGHEDGE		(1<<0)
#define IORESOURCE_IRQ_LOWEDGE		(1<<1)
#define IORESOURCE_IRQ_HIGHLEVEL	(1<<2)
#define IORESOURCE_IRQ_LOWLEVEL		(1<<3)
#define IORESOURCE_IRQ_SHAREABLE	(1<<4)
#define IORESOURCE_IRQ_OPTIONAL 	(1<<5)

/* PnP DMA specific bits (IORESOURCE_BITS) */
#define IORESOURCE_DMA_TYPE_MASK	(3<<0)
#define IORESOURCE_DMA_8BIT		(0<<0)
#define IORESOURCE_DMA_8AND16BIT	(1<<0)
#define IORESOURCE_DMA_16BIT		(2<<0)

#define IORESOURCE_DMA_MASTER		(1<<2)
#define IORESOURCE_DMA_BYTE		(1<<3)
#define IORESOURCE_DMA_WORD		(1<<4)

#define IORESOURCE_DMA_SPEED_MASK	(3<<6)
#define IORESOURCE_DMA_COMPATIBLE	(0<<6)
#define IORESOURCE_DMA_TYPEA		(1<<6)
#define IORESOURCE_DMA_TYPEB		(2<<6)
#define IORESOURCE_DMA_TYPEF		(3<<6)

/* PnP memory I/O specific bits (IORESOURCE_BITS) */
#define IORESOURCE_MEM_WRITEABLE	(1<<0)	/* dup: IORESOURCE_READONLY */
#define IORESOURCE_MEM_CACHEABLE	(1<<1)	/* dup: IORESOURCE_CACHEABLE */
#define IORESOURCE_MEM_RANGELENGTH	(1<<2)	/* dup: IORESOURCE_RANGELENGTH */
#define IORESOURCE_MEM_TYPE_MASK	(3<<3)
#define IORESOURCE_MEM_8BIT		(0<<3)
#define IORESOURCE_MEM_16BIT		(1<<3)
#define IORESOURCE_MEM_8AND16BIT	(2<<3)
#define IORESOURCE_MEM_32BIT		(3<<3)
#define IORESOURCE_MEM_SHADOWABLE	(1<<5)	/* dup: IORESOURCE_SHADOWABLE */
#define IORESOURCE_MEM_EXPANSIONROM	(1<<6)

/* PnP I/O specific bits (IORESOURCE_BITS) */
#define IORESOURCE_IO_16BIT_ADDR	(1<<0)
#define IORESOURCE_IO_FIXED		(1<<1)

/* PCI ROM control bits (IORESOURCE_BITS) */
#define IORESOURCE_ROM_ENABLE		(1<<0)	/* ROM is enabled, same as PCI_ROM_ADDRESS_ENABLE */
#define IORESOURCE_ROM_SHADOW		(1<<1)	/* ROM is copy at C000:0 */
#define IORESOURCE_ROM_COPY		(1<<2)	/* ROM is alloc'd copy, resource field overlaid */
#define IORESOURCE_ROM_BIOS_COPY	(1<<3)	/* ROM is BIOS copy, resource field overlaid */

/* PCI control bits.  Shares IORESOURCE_BITS with above PCI ROM.  */
#define IORESOURCE_PCI_FIXED		(1<<4)	/* Do not move resource */

/* PC/ISA/whatever - the normal PC address spaces: IO and memory */
extern struct resource ioport_resource;
extern struct resource iomem_resource;

extern struct resource *request_resource_conflict(struct resource *root, struct resource *new);
extern int request_resource(struct resource *root, struct resource *new);
extern int release_resource(struct resource *new);
void release_child_resources(struct resource *new);
extern void reserve_region_with_split(struct resource *root,
			     resource_size_t start, resource_size_t end,
			     const char *name);
extern struct resource *insert_resource_conflict(struct resource *parent, struct resource *new);
extern int insert_resource(struct resource *parent, struct resource *new);
extern void insert_resource_expand_to_fit(struct resource *root, struct resource *new);
extern int allocate_resource(struct resource *root, struct resource *new,
			     resource_size_t size, resource_size_t min,
			     resource_size_t max, resource_size_t align,
			     resource_size_t (*alignf)(void *,
						       const struct resource *,
						       resource_size_t,
						       resource_size_t),
			     void *alignf_data);
int adjust_resource(struct resource *res, resource_size_t start,
		    resource_size_t size);
resource_size_t resource_alignment(struct resource *res);
static inline resource_size_t resource_size(const struct resource *res)
{
	return res->end - res->start + 1;
}
static inline unsigned long resource_type(const struct resource *res)
{//根据标志位判断资源类型
	return res->flags & IORESOURCE_TYPE_BITS;
}

/* Convenience shorthand with allocation */
//把一个给定区间的IO端口分配给一个IO设备
#define request_region(start,n,name)		__request_region(&ioport_resource, (start), (n), (name), 0)
#define request_muxed_region(start,n,name)	__request_region(&ioport_resource, (start), (n), (name), IORESOURCE_MUXED)
#define __request_mem_region(start,n,name, excl) __request_region(&iomem_resource, (start), (n), (name), excl)
//请求分配指定的从物理地址start开始，大小为n的IO内存资源。
#define request_mem_region(start,n,name) __request_region(&iomem_resource, (start), (n), (name), 0)
#define request_mem_region_exclusive(start,n,name) \
	__request_region(&iomem_resource, (start), (n), (name), IORESOURCE_EXCLUSIVE)
#define rename_region(region, newname) do { (region)->name = (newname); } while (0)

extern struct resource * __request_region(struct resource *,
					resource_size_t start,
					resource_size_t n,
					const char *name, int flags);

/* Compatibility cruft */
//释放以前分配给一个IO设备的给定区间的IO端口。
#define release_region(start,n)	__release_region(&ioport_resource, (start), (n))
//检查指定的IO内存资源是否已被占用。
#define check_mem_region(start,n)	__check_region(&iomem_resource, (start), (n))
//释放指定的IO内存资源
#define release_mem_region(start,n)	__release_region(&iomem_resource, (start), (n))

extern int __check_region(struct resource *, resource_size_t, resource_size_t);
extern void __release_region(struct resource *, resource_size_t,
				resource_size_t);

//检查一个给定区间的IO端口是否空闲，或者其中一些是否已经分配给某个IO设备。
static inline int __deprecated check_region(resource_size_t s,
						resource_size_t n)
{
	return __check_region(&ioport_resource, s, n);
}

/* Wrappers for managed devices */
struct device;
#define devm_request_region(dev,start,n,name) \
	__devm_request_region(dev, &ioport_resource, (start), (n), (name))
#define devm_request_mem_region(dev,start,n,name) \
	__devm_request_region(dev, &iomem_resource, (start), (n), (name))

extern struct resource * __devm_request_region(struct device *dev,
				struct resource *parent, resource_size_t start,
				resource_size_t n, const char *name);

#define devm_release_region(dev, start, n) \
	__devm_release_region(dev, &ioport_resource, (start), (n))
#define devm_release_mem_region(dev, start, n) \
	__devm_release_region(dev, &iomem_resource, (start), (n))

extern void __devm_release_region(struct device *dev, struct resource *parent,
				  resource_size_t start, resource_size_t n);
extern int iomem_map_sanity_check(resource_size_t addr, unsigned long size);
extern int iomem_is_exclusive(u64 addr);

extern int
walk_system_ram_range(unsigned long start_pfn, unsigned long nr_pages,
		void *arg, int (*func)(unsigned long, unsigned long, void *));

#endif /* __ASSEMBLY__ */
#endif	/* _LINUX_IOPORT_H */
