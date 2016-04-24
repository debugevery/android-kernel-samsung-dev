/* Generic I/O port emulation, based on MN10300 code
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version
 * 2 of the Licence, or (at your option) any later version.
 */
#ifndef __ASM_GENERIC_IO_H
#define __ASM_GENERIC_IO_H

//#include <asm/page.h> /* I/O is all done through memory accesses */
//#include <asm/cacheflush.h>
//#include <linux/types.h>

#ifdef CONFIG_GENERIC_IOMAP
//#include <asm-generic/iomap.h>
#endif

#define mmiowb() do {} while (0)

/*****************************************************************************/
/*
 * readX/writeX() are used to access memory mapped devices. On some
 * architectures the memory mapped IO stuff needs to be accessed
 * differently. On the simple architectures, we just read/write the
 * memory location directly.
 //读GPIO端口寄存器的值===============================*/
#define readb __raw_readb
#define readw(addr) __le16_to_cpu(__raw_readw(addr))
#define readl(addr) __le32_to_cpu(__raw_readl(addr))
static inline u8 __raw_readb(const volatile void __iomem *addr)
{
	return *(const volatile u8 __force *) addr;
}

static inline u16 __raw_readw(const volatile void __iomem *addr)
{
	return *(const volatile u16 __force *) addr;
}

static inline u32 __raw_readl(const volatile void __iomem *addr)
{
	return *(const volatile u32 __force *) addr;
}



//写值到GPIO端口寄存器=======================================
#define writeb __raw_writeb
#define writew(b,addr) __raw_writew(__cpu_to_le16(b),addr)
#define writel(b,addr) __raw_writel(__cpu_to_le32(b),addr)
static inline void __raw_writeb(u8 b, volatile void __iomem *addr)
{
	*(volatile u8 __force *) addr = b;
}

static inline void __raw_writew(u16 b, volatile void __iomem *addr)
{
	*(volatile u16 __force *) addr = b;
}

static inline void __raw_writel(u32 b, volatile void __iomem *addr)
{
	*(volatile u32 __force *) addr = b;
}



#ifdef CONFIG_64BIT
static inline u64 __raw_readq(const volatile void __iomem *addr)
{
	return *(const volatile u64 __force *) addr;
}
#define readq(addr) __le64_to_cpu(__raw_readq(addr))

static inline void __raw_writeq(u64 b, volatile void __iomem *addr)
{
	*(volatile u64 __force *) addr = b;
}
#define writeq(b,addr) __raw_writeq(__cpu_to_le64(b),addr)
#endif

/*****************************************************************************/
/*
 * traditional input/output functions
 */

static inline u8 inb(unsigned long addr)
{
	return readb((volatile void __iomem *) addr);
}

static inline u16 inw(unsigned long addr)
{
	return readw((volatile void __iomem *) addr);
}

static inline u32 inl(unsigned long addr)
{
	return readl((volatile void __iomem *) addr);
}

static inline void outb(u8 b, unsigned long addr)
{
	writeb(b, (volatile void __iomem *) addr);
}

static inline void outw(u16 b, unsigned long addr)
{
	writew(b, (volatile void __iomem *) addr);
}

static inline void outl(u32 b, unsigned long addr)
{
	writel(b, (volatile void __iomem *) addr);
}

#define inb_p(addr)	inb(addr)
#define inw_p(addr)	inw(addr)
#define inl_p(addr)	inl(addr)
#define outb_p(x, addr)	outb((x), (addr))
#define outw_p(x, addr)	outw((x), (addr))
#define outl_p(x, addr)	outl((x), (addr))

static inline void insb(unsigned long addr, void *buffer, int count)
{
	if (count) {
		u8 *buf = buffer;
		do {
			u8 x = inb(addr);
			*buf++ = x;
		} while (--count);
	}
}

static inline void insw(unsigned long addr, void *buffer, int count)
{
	if (count) {
		u16 *buf = buffer;
		do {
			u16 x = inw(addr);
			*buf++ = x;
		} while (--count);
	}
}

static inline void insl(unsigned long addr, void *buffer, int count)
{
	if (count) {
		u32 *buf = buffer;
		do {
			u32 x = inl(addr);
			*buf++ = x;
		} while (--count);
	}
}

static inline void outsb(unsigned long addr, const void *buffer, int count)
{
	if (count) {
		const u8 *buf = buffer;
		do {
			outb(*buf++, addr);
		} while (--count);
	}
}

static inline void outsw(unsigned long addr, const void *buffer, int count)
{
	if (count) {
		const u16 *buf = buffer;
		do {
			outw(*buf++, addr);
		} while (--count);
	}
}

static inline void outsl(unsigned long addr, const void *buffer, int count)
{
	if (count) {
		const u32 *buf = buffer;
		do {
			outl(*buf++, addr);
		} while (--count);
	}
}

#ifndef CONFIG_GENERIC_IOMAP
#define ioread8(addr)		readb(addr)
#define ioread16(addr)		readw(addr)
#define ioread32(addr)		readl(addr)

#define iowrite8(v, addr)	writeb((v), (addr))
#define iowrite16(v, addr)	writew((v), (addr))
#define iowrite32(v, addr)	writel((v), (addr))

#define ioread8_rep(p, dst, count) \
	insb((unsigned long) (p), (dst), (count))
#define ioread16_rep(p, dst, count) \
	insw((unsigned long) (p), (dst), (count))
#define ioread32_rep(p, dst, count) \
	insl((unsigned long) (p), (dst), (count))

#define iowrite8_rep(p, src, count) \
	outsb((unsigned long) (p), (src), (count))
#define iowrite16_rep(p, src, count) \
	outsw((unsigned long) (p), (src), (count))
#define iowrite32_rep(p, src, count) \
	outsl((unsigned long) (p), (src), (count))
#endif /* CONFIG_GENERIC_IOMAP */


#define IO_SPACE_LIMIT 0xffffffff

#ifdef __KERNEL__

//#include <linux/vmalloc.h>
#define __io_virt(x) ((void __force *) (x))

#ifndef CONFIG_GENERIC_IOMAP
/* Create a virtual mapping cookie for a PCI BAR (memory or IO) */
struct pci_dev;
extern void __iomem *pci_iomap(struct pci_dev *dev, int bar, unsigned long max);
static inline void pci_iounmap(struct pci_dev *dev, void __iomem *p)
{
}
#endif /* CONFIG_GENERIC_IOMAP */

/*
 * Change virtual addresses to physical addresses and vv.
 * These are pretty trivial
 */
static inline unsigned long virt_to_phys(volatile void *address)
{//转换过程是将虚拟地址减去3G（PAGE_OFFSET=0XC000000）。
	return __pa((unsigned long)address);
}
static inline void *phys_to_virt(unsigned long address)
{
	return __va(address);
}

/*
 * Change "struct page" to physical address.
 
内存映射
    对于提供了MMU（存储管理器，辅助操作系统进行内存管理，提供虚实地址转换等硬件支持）的处理器而言，Linux提供了复杂的存储管理系统，使得进程所能访问的内存达到4GB。
　　进程的4GB内存空间被人为的分为两个部分--用户空间与内核空间。用户空间地址分布从0到3GB(PAGE_OFFSET，在0x86中它等于0xC0000000)，3GB到4GB为内核空间，如下图：

　　内核空间中，从3G到vmalloc_start这段地址是物理内存映射区域（该区域中包含了内核镜像、物理页框表mem_map等等），比如我们使用的VMware虚拟系统内存是160M，那么3G～3G+160M这片内存就应该映射物理内存。在物理内存映射区之后，就是vmalloc区域。对于 160M的系统而言，vmalloc_start位置应在3G+160M附近（在物理内存映射区与vmalloc_start期间还存在一个8M的gap 来防止跃界），vmalloc_end的位置接近4G(最后位置系统会保留一片128k大小的区域用于专用页面映射)，如下图：

　　kmalloc和get_free_page申请的内存位于物理内存映射区域，而且在物理上也是连续的，它们与真实的物理地址只有一个固定的偏移，因此存在较简单的转换关系，virt_to_phys()可以实现内核虚拟地址转化为物理地址：

 我们讨论Linux设备驱动究竟怎样访问外设的I/O端口（寄存器）===============================================。
 
　　几乎每一种外设都是通过读写设备上的寄存器来进行的，通常包括控制寄存器、状态寄存器和数据寄存器三大类，外设的寄存器通常被连续地编址。
根据CPU体系结构的不同，CPU对IO端口的编址方式有两种：
　　（1）I/O映射方式（I/O-mapped）
　　典型地，如X86处理器为外设专门实现了一个单独的地址空间，称为"I/O地址空间"或者"I/O端口空间"，CPU通过专门
的I/O指令（如X86的IN和OUT指令）来访问这一空间中的地址单元。

    （2）内存映射方式（Memory-mapped）
　　RISC指令系统的CPU（如ARM、PowerPC等）通常只实现一个物理地址空间，外设I/O端口成为内存的一部分。此时，CPU可以象访问
一个内存单元那样访问外设I/O端口，而不需要设立专门的外设I/O指令。
　　但是，这两者在硬件实现上的差异对于软件来说是完全透明的，驱动程序开发人员可以将内存映射方式的I/O端口和外设内存统一
看作是"I/O内存"资源。
　　一般来说，在系统运行时，外设的I/O内存资源的物理地址是已知的，由硬件的设计决定。但是CPU通常并没有为这些已知的外设
I/O内存资源的物理地址预定义虚拟地址范围，驱动程序并不能直接通过物理地址访问I/O内存资源，而必须将它们映射到核心虚地址
空间内（通过页表），然后才能根据映射所得到的核心虚地址范围，通过访内指令访问这些I/O内存资源。Linux在io.h头文件中声明
了函数ioremap（），用来将I/O内存资源的物理地址映射到核心虚地址空间（3GB－4GB）中

	在将I/O内存资源的物理地址映射成核心虚地址后，理论上讲我们就可以象读写RAM那样直接读写I/O内存资源了。为了保证驱动程序
的跨平台的可移植性，我们应该使用Linux中特定的函数来访问I/O内存资源，而不应该通过指向核心虚地址的指针来访问。

	最后，我们要特别强调驱动程序中mmap函数的实现方法。用mmap映射一个设备，意味着使用户空间的一段地址关联到设备内存上，
这使得只要程序在分配的地址范围内进行读取或者写入，实际上就是对设备的访问。
*/
static inline void __iomem *ioremap(phys_addr_t offset, unsigned long size)
{//将一个IO物理地址空间映射到内核的虚拟地址空间（3GB－4GB）中上去，用于配置寄存器。
//因为linux用的是页面映射机制,CPU不能按物理地址来访问存储空间,,而必须使用虚拟地址,除非在用户空间用mmap直接访问物理地址
	return (void __iomem*) (unsigned long)offset;
}

#define __ioremap(offset, size, flags)	ioremap(offset, size)

#ifndef ioremap_nocache
#define ioremap_nocache ioremap
#endif

#ifndef ioremap_wc
#define ioremap_wc ioremap_nocache
#endif

static inline void iounmap(void *addr)
{
}

#ifndef CONFIG_GENERIC_IOMAP
static inline void __iomem *ioport_map(unsigned long port, unsigned int nr)
{
	return (void __iomem *) port;
}

static inline void ioport_unmap(void __iomem *p)
{
}
#else /* CONFIG_GENERIC_IOMAP */
extern void __iomem *ioport_map(unsigned long port, unsigned int nr);
extern void ioport_unmap(void __iomem *p);
#endif /* CONFIG_GENERIC_IOMAP */

#define xlate_dev_kmem_ptr(p)	p
#define xlate_dev_mem_ptr(p)	((void *) (p))

#ifndef virt_to_bus
static inline unsigned long virt_to_bus(volatile void *address)
{
	return ((unsigned long) address);
}

static inline void *bus_to_virt(unsigned long address)
{
	return (void *) address;
}
#endif

#define memset_io(a, b, c)	memset(__io_virt(a), (b), (c))
#define memcpy_fromio(a, b, c)	memcpy((a), __io_virt(b), (c))
#define memcpy_toio(a, b, c)	memcpy(__io_virt(a), (b), (c))

#endif /* __KERNEL__ */

#endif /* __ASM_GENERIC_IO_H */
