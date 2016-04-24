/* linux/include/asm-arm/plat-s3c/map.h
 *
 * Copyright 2003, 2007 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C - Memory map definitions (virtual addresses)内存虚拟映射
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ASM_PLAT_MAP_H
#define __ASM_PLAT_MAP_H __FILE__

/* Fit all our registers in at 0xF4000000 upwards, trying to use as
 * little of the VA space as possible so vmalloc and friends have a
 * better chance of getting memory.
 *
 * we try to ensure stuff like the IRQ registers are available for
 * an single MOVS instruction (ie, only 8 bits of set data)
   Linux规定，系统4G的空间的前面3G都是给用户态使用的，内核空间都在后1G，也就是0xc0000000到0xFFFFFFFF的
地址空间。不管模块的物理地址在哪里，都可以通过MMU将其映射到期望的虚拟地址，楼主的0xF400_0000就是这
个虚拟地址了。其实不一定非得是0xF400_0000,只要不和系统的其它映射冲突就可以了。至于各个模块的Offset问
题，有了MMU，可以将其映射想映射的位置，因此Offset也是没有关系的。这些映射在start_kernel里面会通
过map_io进行映射，因此系统是知道的。
   当然映射也不是说可以乱映射的，ARM的最小映射单位是4K，因此两个模块的地址如果都在一个4K区域里面就
没法映射开了。
	其实这个虚拟地址是你自己指定的，只要这个地址没有被使用，并且页对齐就可以了
    其实就是说0x70000000这个地址是用户态用的，Linux要把它映射到0xc0000000后去，比如F4000000,MMU配置
正确后，在内核中访问虚拟地址F4000000就是访问物理的0x70000000。
 */ */

#define S3C_ADDR_BASE	(0xFD000000)

#ifndef __ASSEMBLY__
#define S3C_ADDR(x)	((void __iomem __force *)S3C_ADDR_BASE + (x))
#else
#define S3C_ADDR(x)	(S3C_ADDR_BASE + (x))//=((0xFD000000) + (x))
#endif

#define S3C_VA_IRQ	S3C_ADDR(0x00000000)	/* irq controller(s) */
#define S3C_VA_SYS	S3C_ADDR(0x00100000)	/* system control */
#define S3C_VA_MEM	S3C_ADDR(0x00200000)	/* memory control */
#define S3C_VA_TIMER	S3C_ADDR(0x00300000)	/* timer block */
#define S3C_VA_WATCHDOG	S3C_ADDR(0x00400000)	/* watchdog */
#define S3C_VA_OTG	S3C_ADDR(0x00E00000)	/* OTG */
#define S3C_VA_OTGSFR	S3C_ADDR(0x00F00000)	/* OTG PHY */
#define S3C_VA_UART	S3C_ADDR(0x01000000)	/* UART */

/* This is used for the CPU specific mappings that may be needed, so that
 * they do not need to directly used S3C_ADDR() and thus make it easier to
 * modify the space for mapping.
 */
#define S3C_ADDR_CPU(x)	S3C_ADDR(0x00500000 + (x))

#endif /* __ASM_PLAT_MAP_H */
