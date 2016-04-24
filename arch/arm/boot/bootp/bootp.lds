/*
 *  linux/arch/arm/boot/bootp/bootp.lds
 *
 *  Copyright (C) 2000-2002 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 内核启动引导地址由bootp.lds决定
 */
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
  . = 0;//// .= 0可以确定解压代码运行的开始地址在0x0的位置
  .text : {
   _stext = .;
   *(.start)
   *(.text)
   initrd_size = initrd_end - initrd_start;
   _etext = .;
  }
  
  .stab 0 : { *(.stab) }
  .stabstr 0 : { *(.stabstr) }
  .stab.excl 0 : { *(.stab.excl) }
  .stab.exclstr 0 : { *(.stab.exclstr) }
  .stab.index 0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment 0 : { *(.comment) }
}




/*
1.       内核启动地址
1.1.   名词解释
ZTEXTADDR

解压代码运行的开始地址。没有物理地址和虚拟地址之分，因为此时MMU处于关闭状态。这个地址不一定时RAM的地址，可以是支持读写寻址的flash等存储中介。

Start address of decompressor. here's no point in talking about virtual or physical addresses here, since the MMU will be off at the time when you call the decompressor code. You normally call   the kernel at this address to start it booting. This doesn't have to be located in RAM, it can be in flash or other read-only or      read-write addressable medium.

ZRELADDR

       内核启动在RAM中的地址。压缩的内核映像被解压到这个地址，然后执行。

This is the address where the decompressed kernel will be written, and eventually executed. The following constraint must be valid:

              __virt_to_phys(TEXTADDR) == ZRELADDR

       The initial part of the kernel is carefully coded to be position independent.

TEXTADDR

       内核启动的虚拟地址，与ZRELADDR相对应。一般内核启动的虚拟地址为RAM的第一个bank地址加上0x8000。

       TEXTADDR = PAGE_OFFSET + TEXTOFFST

       Virtual start address of kernel, normally PAGE_OFFSET + 0x8000.This is where the kernel image ends up.  With the latest kernels, it must be located at 32768 bytes into a 128MB region.  Previous kernels placed a restriction of 256MB here.

TEXTOFFSET

       内核偏移地址。在arch/arm/makefile中设定。

PHYS_OFFSET

       RAM第一个bank的物理起始地址。

Physical start address of the first bank of RAM.

PAGE_OFFSET

RAM第一个bank的虚拟起始地址。

       Virtual start address of the first bank of RAM.  During the kernel

       boot phase, virtual address PAGE_OFFSET will be mapped to physical

       address PHYS_OFFSET, along with any other mappings you supply.

       This should be the same value as TASK_SIZE.

 */