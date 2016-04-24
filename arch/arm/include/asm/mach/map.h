/*
 *  arch/arm/include/asm/map.h
 *
 *  Copyright (C) 1999-2000 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *  Page table mapping constructs and function prototypes
 */
//#include <asm/io.h>

//描述静态映射数据结构，在嵌入式中一般将SOC内的控制器和片外内存以及ROM和网络控制器先静态映射并为之建立页表以方便使用，在map_io函数中完成大部分静态映射。一般将片内控制器作为IO内存使用，利用静态映射来访问。
struct map_desc 
{ 
 unsigned long virtual; //虚拟地址
 unsigned long physical; //物理地址
 unsigned long length; //长度
 unsigned int type; //类型供8中MT_DEVICE MT_CACHECLEAN MT_MINICLEAN MT_LOW_VECTORS
 //MT_HIGH_VECTORS MT_MEMORY MT_ROM MT_IXP2000_DEVICE
}; 
//在分析平台设备驱动的过程中发现一个问题，在初始化过程中已将所用片内控制寄存器静态映射；但是在驱动程序中通过ioremap(res->start, size)又将物理地址动态映射了一遍，但两虚拟地址指向同一物理地址不会起冲突。

/* types 0-3 are defined in asm/io.h */
#define MT_UNCACHED		4
#define MT_CACHECLEAN		5
#define MT_MINICLEAN		6
#define MT_LOW_VECTORS		7
#define MT_HIGH_VECTORS		8
#define MT_MEMORY		9
#define MT_ROM			10
#define MT_MEMORY_NONCACHED	11

#ifdef CONFIG_MMU
extern void iotable_init(struct map_desc *, int);

struct mem_type;
extern const struct mem_type *get_mem_type(unsigned int type);
/*
 * external interface to remap single page with appropriate type
 */
extern int ioremap_page(unsigned long virt, unsigned long phys,
			const struct mem_type *mtype);
#else
#define iotable_init(map,num)	do { } while (0)
#endif
