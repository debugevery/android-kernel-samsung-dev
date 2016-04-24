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
	/*�ں�ͨ��machine_desc�ṹ��������ϵͳ��ϵ�ܹ���ز��ֵĳ�ʼ����
	������Ա�����ڲ�ͬʱ�ڱ����ã�============������Ҫ���� setup_arch() ���õ���
	 * Note! The first four elements are used
	 * by assembler code in head.S, head-common.S
	 */
	unsigned int		nr;		/* architecture number��������linux�еĻ�����	*/
	unsigned int		phys_io;	/* start of physical io����˿���ʼ��ַ 	*/
	unsigned int		io_pg_offst;	/* byte offset for io //ioҳ���ƫ��
						 * page tabe entry	*/

	const char		*name;		/* architecture name��������Ϣ	*/
	unsigned long		boot_params;	/* tagged list	bootloader���ݲ����������ַ	*/

	unsigned int		video_start;	/* start of video RAM  ��ƵRAM��ʼ��ַ	*/
	unsigned int		video_end;	/* end of video RAM	��ƵRAM������ַ*/

	unsigned int		reserve_lp0 :1;	/* never has lp0	*/
	unsigned int		reserve_lp1 :1;	/* never has lp1	*/
	unsigned int		reserve_lp2 :1;	/* never has lp2	*///���õ�3����ӡ�� 

	unsigned int		soft_reboot :1;	/* soft reboot	������ 	*/
	void			(*fixup)(struct machine_desc *,struct tag *, char **,struct meminfo *);
//map_io��Ա���ں��ṩ���û��Ĵ�������I/O��Դ���ں������ַ��̬ӳ���Ľӿں���
//   map_io��Ա��������ϵͳ��ʼ�������б�����,�������£�
//   Start_kernel -> setup_arch() --> paging_init() --> devicemaps_init()�б�����Machine_desc�ṹ��ͨ��MACHINE_START������ʼ����	
	void			(*map_io)(void);/* IO mapping functionI/O�˿��ڴ�ӳ�亯����*/
//_init_irq()�����ǳ�ʼ��IRQ�ж�,ͨ��start_kernel()���init_IRQ()��������init_arch_irq()ʵ
//�ֵġ���Ϊ��MACHINE_START�ṹ����  .init_irq = s3c24xx_init_irq������setup_arch()��
//����init_arch_irq = mdesc->init_irq�� ���Ե���init_arch_irq()���൱�ڵ�����s3c24xx_init_irq()��
	void			(*init_irq)(void);//�жϳ�ʼ������ ��start_kernel() --> init_IRQ() --> init_arch_irq() ������
	struct sys_timer	*timer;		/* ��ʱ��system tick timer	*/
//_machine_init()�����ĳ�ʼ������MACHINE_START�ṹ���У�����ָ�븳ֵ��.init_machine =
//smdk_machine_init����init_machine()������linux/arch/arm/kernel/setup.c�ļ���
//��customize_machine()�������ò���arch_initcall(Fn)�괦��arch_initcall(customize_machine)�
//� ��arch_initcall(Fn)�괦���������linux/init/main.c  do_initcalls()�������á�	
	void			(*init_machine)(void);//��ʼ�������� arch/arm/kernel/setup.c �б� customize_machine ���ã����� arch_initcall() �����棬���Զ���˳�򱻵��á�
};

/*
 * Set of macros to define architecture features.  This is built into
 * a table by the linker.
 */
// MACHINE_START��Ҫ�Ƕ�����"struct machine_desc"������
#define MACHINE_START(_type,_name)			\           //_type��_name�滻����ȥ��##
static const struct machine_desc __mach_desc_##_type	\
 __used							\
 __attribute__((__section__(".arch.info.init"))) = {	\
	.nr		= MACH_TYPE_##_type,		\
	.name		= _name,

#define MACHINE_END				\
};

#endif
//MACH_TYPE_S3C2440���Կ�����ϵͳƽ̨�ţ���������include/asm- arm/mach-types.hͷ�ļ��У�
//�������ͷ�ļ����������ں˻�����ں�ʱ�Զ����ɵģ����Բ��ܸ��ġ�������ϵͳƽ̨��
//�Ķ���λ����arch/arm/tools/mach-types�ļ��С�

//# machine_is_xxx        CONFIG_xxxx      MACH_TYPE_xxx       number

//s3c2440          ARCH_S3C2440           S3C2440          362

//arch/arm/tools/mach-types��ÿһ�ж���һ��ϵͳƽ̨�š� ��machine_is_xxx���������жϵ�ǰ��ƽ̨��
//�Ƿ���ȷ�ĺ����� ��CONFIG_xxxx�������ں�����ʱ���ɵģ� ��MACH_TYPE_xxx����ϵͳƽ̨�ŵĶ��壻 
//��number����ϵͳƽ̨��ֵ�� __mach_desc_S3C2440�ṹ���еĺ��������ں����������У����ϵͳƽ̨��
//��ʼ������.  ���ھ�����ͬ��������ϵͳƽ̨��������Ҫ��ÿһ��ƽ̨����дһ��BSP��������ǵ���Χ
//�ӿڵ�·������ͬ��Ҳ��ֻ���޸�һЩ���ݵĶ��壬�޸ļ��������Ĳ����Ϳ����ˡ�


