/* linux/include/asm-arm/plat-s3c/map.h
 *
 * Copyright 2003, 2007 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C - Memory map definitions (virtual addresses)�ڴ�����ӳ��
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
   Linux�涨��ϵͳ4G�Ŀռ��ǰ��3G���Ǹ��û�̬ʹ�õģ��ں˿ռ䶼�ں�1G��Ҳ����0xc0000000��0xFFFFFFFF��
��ַ�ռ䡣����ģ��������ַ�����������ͨ��MMU����ӳ�䵽�����������ַ��¥����0xF400_0000������
�������ַ�ˡ���ʵ��һ���ǵ���0xF400_0000,ֻҪ����ϵͳ������ӳ���ͻ�Ϳ����ˡ����ڸ���ģ���Offset��
�⣬����MMU�����Խ���ӳ����ӳ���λ�ã����OffsetҲ��û�й�ϵ�ġ���Щӳ����start_kernel�����ͨ
��map_io����ӳ�䣬���ϵͳ��֪���ġ�
   ��Ȼӳ��Ҳ����˵������ӳ��ģ�ARM����Сӳ�䵥λ��4K���������ģ��ĵ�ַ�������һ��4K���������
û��ӳ�俪�ˡ�
	��ʵ��������ַ�����Լ�ָ���ģ�ֻҪ�����ַû�б�ʹ�ã�����ҳ����Ϳ�����
    ��ʵ����˵0x70000000�����ַ���û�̬�õģ�LinuxҪ����ӳ�䵽0xc0000000��ȥ������F4000000,MMU����
��ȷ�����ں��з��������ַF4000000���Ƿ��������0x70000000��
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
