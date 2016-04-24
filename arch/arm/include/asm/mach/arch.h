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
	/*ÄÚºËÍ¨¹ımachine_desc½á¹¹ÌåÀ´¿ØÖÆÏµÍ³ÌåÏµ¼Ü¹¹Ïà¹Ø²¿·ÖµÄ³õÊ¼»¯¡£
	¸÷¸ö³ÉÔ±º¯ÊıÔÚ²»Í¬Ê±ÆÚ±»µ÷ÓÃ£º============ÆäËûÖ÷Òª¶¼ÔÚ setup_arch() ÖĞÓÃµ½¡£
	 * Note! The first four elements are used
	 * by assembler code in head.S, head-common.S
	 */
	unsigned int		nr;		/* architecture number¿ª·¢°åÔÚlinuxÖĞµÄ»úÆ÷ºÅ	*/
	unsigned int		phys_io;	/* start of physical ioÎïÀí¶Ë¿ÚÆğÊ¼µØÖ· 	*/
	unsigned int		io_pg_offst;	/* byte offset for io //ioÒ³±íµÄÆ«ÒÆ
						 * page tabe entry	*/

	const char		*name;		/* architecture name¿ª·¢°åĞÅÏ¢	*/
	unsigned long		boot_params;	/* tagged list	bootloader´«µİ²ÎÊıÊ×ÎïÀíµØÖ·	*/

	unsigned int		video_start;	/* start of video RAM  ÊÓÆµRAMÆğÊ¼µØÖ·	*/
	unsigned int		video_end;	/* end of video RAM	ÊÓÆµRAM½áÊøµØÖ·*/

	unsigned int		reserve_lp0 :1;	/* never has lp0	*/
	unsigned int		reserve_lp1 :1;	/* never has lp1	*/
	unsigned int		reserve_lp2 :1;	/* never has lp2	*///ÉèÖÃµÄ3¸ö´òÓ¡¿Ú 

	unsigned int		soft_reboot :1;	/* soft reboot	ÈíÖØÆô 	*/
	void			(*fixup)(struct machine_desc *,struct tag *, char **,struct meminfo *);
//map_io³ÉÔ±¼´ÄÚºËÌá¹©¸øÓÃ»§µÄ´´½¨ÍâÉèI/O×ÊÔ´µ½ÄÚºËĞéÄâµØÖ·¾²Ì¬Ó³Éä±íµÄ½Ó¿Úº¯Êı
//   map_io³ÉÔ±º¯Êı»áÔÚÏµÍ³³õÊ¼»¯¹ı³ÌÖĞ±»µ÷ÓÃ,Á÷³ÌÈçÏÂ£º
//   Start_kernel -> setup_arch() --> paging_init() --> devicemaps_init()ÖĞ±»µ÷ÓÃMachine_desc½á¹¹ÌåÍ¨¹ıMACHINE_STARTºêÀ´³õÊ¼»¯¡£	
	void			(*map_io)(void);/* IO mapping functionI/O¶Ë¿ÚÄÚ´æÓ³Éäº¯Êı£¬*/
//_init_irq()º¯ÊıÊÇ³õÊ¼»¯IRQÖĞ¶Ï,Í¨¹ıstart_kernel()ÀïµÄinit_IRQ()º¯Êıµ÷ÓÃinit_arch_irq()Êµ
//ÏÖµÄ¡£ÒòÎªÔÚMACHINE_START½á¹¹ÌåÖĞ  .init_irq = s3c24xx_init_irq£¬¶øÔÚsetup_arch()º¯
//ÊıÖĞinit_arch_irq = mdesc->init_irq£¬ ËùÒÔµ÷ÓÃinit_arch_irq()¾ÍÏàµ±ÓÚµ÷ÓÃÁËs3c24xx_init_irq()¡£
	void			(*init_irq)(void);//ÖĞ¶Ï³õÊ¼»¯º¯Êı ÔÚstart_kernel() --> init_IRQ() --> init_arch_irq() ±»µ÷ÓÃ
	struct sys_timer	*timer;		/* ¶¨Ê±Æ÷system tick timer	*/
//_machine_init()º¯ÊıµÄ³õÊ¼»¯¡£ÔÚMACHINE_START½á¹¹ÌåÖĞ£¬º¯ÊıÖ¸Õë¸³Öµ£¬.init_machine =
//smdk_machine_init¡£¶øinit_machine()º¯Êı±»linux/arch/arm/kernel/setup.cÎÄ¼şÖĞ
//µÄcustomize_machine()º¯Êıµ÷ÓÃ²¢±»arch_initcall(Fn)ºê´¦Àí£¬arch_initcall(customize_machine)¡
//£ ±»arch_initcall(Fn)ºê´¦Àí¹ıº¯Êı½«linux/init/main.c  do_initcalls()º¯Êıµ÷ÓÃ¡£	
	void			(*init_machine)(void);//³õÊ¼»¯º¯ÊıÔÚ arch/arm/kernel/setup.c ÖĞ±» customize_machine µ÷ÓÃ£¬·ÅÔÚ arch_initcall() ¶ÎÀïÃæ£¬»á×Ô¶¯°´Ë³Ğò±»µ÷ÓÃ¡£
};

/*
 * Set of macros to define architecture features.  This is built into
 * a table by the linker.
 */
// MACHINE_STARTÖ÷ÒªÊÇ¶¨ÒåÁË"struct machine_desc"µÄÀàĞÍ
#define MACHINE_START(_type,_name)			\           //_type£¬_nameÌæ»»µô£¬È¥µô##
static const struct machine_desc __mach_desc_##_type	\
 __used							\
 __attribute__((__section__(".arch.info.init"))) = {	\
	.nr		= MACH_TYPE_##_type,		\
	.name		= _name,

#define MACHINE_END				\
};

#endif
//MACH_TYPE_S3C2440¿ÉÒÔ¿´×÷ÊÇÏµÍ³Æ½Ì¨ºÅ£¬Ëü°üº¬ÔÚinclude/asm- arm/mach-types.hÍ·ÎÄ¼şÖĞ£¬
//²»¹ıÕâ¸öÍ·ÎÄ¼şÊÇÔÚÅäÖÃÄÚºË»ò±àÒëÄÚºËÊ±×Ô¶¯Éú³ÉµÄ£¬ËùÒÔ²»ÄÜ¸ü¸Ä¡£¡£ÕæÕıÏµÍ³Æ½Ì¨ºÅ
//µÄ¶¨ÒåÎ»ÖÃÔÚarch/arm/tools/mach-typesÎÄ¼şÖĞ¡£

//# machine_is_xxx        CONFIG_xxxx      MACH_TYPE_xxx       number

//s3c2440          ARCH_S3C2440           S3C2440          362

//arch/arm/tools/mach-typesÖĞÃ¿Ò»ĞĞ¶¨ÒåÒ»¸öÏµÍ³Æ½Ì¨ºÅ¡£ ¡°machine_is_xxx¡±ÊÇÓÃÀ´ÅĞ¶Ïµ±Ç°µÄÆ½Ì¨ºÅ
//ÊÇ·ñÕıÈ·µÄº¯Êı£» ¡°CONFIG_xxxx¡±ÊÇÔÚÄÚºËÅäÖÃÊ±Éú³ÉµÄ£» ¡°MACH_TYPE_xxx¡±ÊÇÏµÍ³Æ½Ì¨ºÅµÄ¶¨Òå£» 
//¡°number¡±ÊÇÏµÍ³Æ½Ì¨µÄÖµ¡£ __mach_desc_S3C2440½á¹¹ÌåÖĞµÄº¯Êı½«ÔÚÄÚºËÆô¶¯¹ı³ÌÖĞ£¬Íê³ÉÏµÍ³Æ½Ì¨µÄ
//³õÊ¼»¯¹¤×÷.  ¶ÔÓÚ¾ßÓĞÏàÍ¬´¦ÀíÆ÷µÄÏµÍ³Æ½Ì¨£¬²¢²»ĞèÒª¶ÔÃ¿Ò»¸öÆ½Ì¨¶¼±àĞ´Ò»¸öBSP£¬Èç¹ûËûÃÇµÄÍâÎ§
//½Ó¿ÚµçÂ·»ù±¾ÏàÍ¬£¬Ò²ĞíÖ»ĞèĞŞ¸ÄÒ»Ğ©Êı¾İµÄ¶¨Òå£¬ĞŞ¸Ä¼¸¸öº¯ÊıµÄ²ÎÊı¾Í¿ÉÒÔÁË¡£


