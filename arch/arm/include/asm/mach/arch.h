/*
 *  arch/arm/include/asm/mach/arch.h
 *
 *  Copyright (C) 2000 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ASSEMBLY__

struct tag;
struct meminfo;
struct sys_timer;

struct machine_desc {
	/*内核通过machine_desc结构体来控制系统体系架构相关部分的初始化。
	各个成员函数在不同时期被调用：============其他主要都在 setup_arch() 中用到。
	 * Note! The first four elements are used
	 * by assembler code in head.S, head-common.S
	 */
	unsigned int		nr;		/* architecture number开发板在linux中的机器号	*/
	unsigned int		phys_io;	/* start of physical io物理端口起始地址 	*/
	unsigned int		io_pg_offst;	/* byte offset for io //io页表的偏移
						 * page tabe entry	*/

	const char		*name;		/* architecture name开发板信息	*/
	unsigned long		boot_params;	/* tagged list	bootloader传递参数首物理地址	*/

	unsigned int		video_start;	/* start of video RAM  视频RAM起始地址	*/
	unsigned int		video_end;	/* end of video RAM	视频RAM结束地址*/

	unsigned int		reserve_lp0 :1;	/* never has lp0	*/
	unsigned int		reserve_lp1 :1;	/* never has lp1	*/
	unsigned int		reserve_lp2 :1;	/* never has lp2	*///设置的3个打印口 

	unsigned int		soft_reboot :1;	/* soft reboot	软重启 	*/
	void			(*fixup)(struct machine_desc *,struct tag *, char **,struct meminfo *);
//map_io成员即内核提供给用户的创建外设I/O资源到内核虚拟地址静态映射表的接口函数
//   map_io成员函数会在系统初始化过程中被调用,流程如下：
//   Start_kernel -> setup_arch() --> paging_init() --> devicemaps_init()中被调用Machine_desc结构体通过MACHINE_START宏来初始化。	
	void			(*map_io)(void);/* IO mapping functionI/O端口内存映射函数，*/
//_init_irq()函数是初始化IRQ中断,通过start_kernel()里的init_IRQ()函数调用init_arch_irq()实
//现的。因为在MACHINE_START结构体中  .init_irq = s3c24xx_init_irq，而在setup_arch()函
//数中init_arch_irq = mdesc->init_irq， 所以调用init_arch_irq()就相当于调用了s3c24xx_init_irq()。
	void			(*init_irq)(void);//中断初始化函数 在start_kernel() --> init_IRQ() --> init_arch_irq() 被调用
	struct sys_timer	*timer;		/* 定时器system tick timer	*/
//_machine_init()函数的初始化。在MACHINE_START结构体中，函数指针赋值，.init_machine =
//smdk_machine_init。而init_machine()函数被linux/arch/arm/kernel/setup.c文件中
//的customize_machine()函数调用并被arch_initcall(Fn)宏处理，arch_initcall(customize_machine)�
//� 被arch_initcall(Fn)宏处理过函数将linux/init/main.c  do_initcalls()函数调用。	
	void			(*init_machine)(void);//初始化函数在 arch/arm/kernel/setup.c 中被 customize_machine 调用，放在 arch_initcall() 段里面，会自动按顺序被调用。
};

/*
 * Set of macros to define architecture features.  This is built into
 * a table by the linker.
 */
// MACHINE_START主要是定义了"struct machine_desc"的类型
#define MACHINE_START(_type,_name)			\           //_type，_name替换掉，去掉##
static const struct machine_desc __mach_desc_##_type	\
 __used							\
 __attribute__((__section__(".arch.info.init"))) = {	\
	.nr		= MACH_TYPE_##_type,		\
	.name		= _name,

#define MACHINE_END				\
};

#endif
//MACH_TYPE_S3C2440可以看作是系统平台号，它包含在include/asm- arm/mach-types.h头文件中，
//不过这个头文件是在配置内核或编译内核时自动生成的，所以不能更改。。真正系统平台号
//的定义位置在arch/arm/tools/mach-types文件中。

//# machine_is_xxx        CONFIG_xxxx      MACH_TYPE_xxx       number

//s3c2440          ARCH_S3C2440           S3C2440          362

//arch/arm/tools/mach-types中每一行定义一个系统平台号。 “machine_is_xxx”是用来判断当前的平台号
//是否正确的函数； “CONFIG_xxxx”是在内核配置时生成的； “MACH_TYPE_xxx”是系统平台号的定义； 
//“number”是系统平台的值。 __mach_desc_S3C2440结构体中的函数将在内核启动过程中，完成系统平台的
//初始化工作.  对于具有相同处理器的系统平台，并不需要对每一个平台都编写一个BSP，如果他们的外围
//接口电路基本相同，也许只需修改一些数据的定义，修改几个函数的参数就可以了。


