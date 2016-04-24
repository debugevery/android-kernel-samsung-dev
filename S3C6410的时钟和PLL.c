S3C6410的时钟和PLL
[日期：2011-09-02] 来源：Linux社区  作者：aokikyon 

 
S3C6410有三个PLL，分别为APLL、MPLL和EPLL。

其中APLL产生ACLK，给arm core使用，MPLL产生HCLKX2、HCLK和PCLK，EPLL产生特殊的时钟，比如为USB提供48MHz时钟。

ARM core的时钟手册上最大标明为667MHz，实际使用时跑800MHz基本没有问题。

HCLKX2主要提供时钟给DDR使用，最大可以到266MHz。
 

HCLK可以看做AXI\AHB总线时钟，APB可以看做APB总线时钟。

接AXI和AHB总线的外设最大时钟为133MHz，接APB总线的外设最大时钟为66MHz。

UART的时钟可以由MPLL或者EPLL提供。

=================来看代码===============================================

6410的主时钟初始化是在u-boot中做的，linux中只是负责读取该数值。

1、u-boot-1.1.6/include/configs/smdk6410.h

APLL设置，这是666MHz的配置，可参考手册修改 
#define APLL_MDIV 333 
#define APLL_PDIV 3
#define APLL_SDIV 1

MPLL设置，我尝试修改，UART就没有输出了
/* fixed MPLL 533MHz */
#define MPLL_MDIV 266
#define MPLL_PDIV 3
#define MPLL_SDIV 1

APLL分频因子
#define Startup_APLLdiv   0
MPLL到HCLKX2的分频因子
#define Startup_HCLKx2div 2
HCLKX2到PCLK的分频因子
#define Startup_PCLKdiv   3
HCLKX2到HCLK的分频因子
#define Startup_HCLKdiv   1
MPLL分频因子
#define Startup_MPLLdiv   1

#define CONFIG_SYNC_MODE
同步模式下，HCLK时钟由APLL分频而来

2、u-boot-1.1.6/board/samsung/smdk6410/lowlevel_init.s
来看看UART的时钟，UART的时钟由EXT_UCLK1提供，UCLK是MPLL的分频，不改MPLL，UART就不会乱
/*
* uart_asm_init: Initialize UART in asm mode, 115200bps fixed.
* void uart_asm_init(void)
*/
uart_asm_init:
/* set GPIO to enable UART */
@ GPIO setting for UART
ldr r0, =ELFIN_GPIO_BASE
ldr r1, =0x220022
str   r1, [r0, #GPACON_OFFSET]

ldr r1, =0x2222
str   r1, [r0, #GPBCON_OFFSET]

ldr r0, =ELFIN_UART_CONSOLE_BASE   @0x7F005000
mov r1, #0x0
str r1, [r0, #UFCON_OFFSET]
str r1, [r0, #UMCON_OFFSET]

mov r1, #0x3                @was 0.
str r1, [r0, #ULCON_OFFSET]

#if defined(CONFIG_CLKSRC_CLKUART)//UART的时钟由EXT_UCLK1提供
ldr r1, =0xe45    /* UARTCLK SRC = 11 => EXT_UCLK1*/
#else
ldr r1, =0x245    /* UARTCLK SRC = x0 => PCLK */
#endif
str r1, [r0, #UCON_OFFSET]
#if defined(CONFIG_UART_50)
ldr r1, =0x1A
#elif defined(CONFIG_UART_66) //EXT_UCLK1为66M时的分频参数
ldr r1, =0x22
#else
ldr r1, =0x1A
#endif
str r1, [r0, #UBRDIV_OFFSET]
#if defined(CONFIG_UART_50)
ldr r1, =0x3
#elif defined(CONFIG_UART_66)
ldr r1, =0x1FFF
#else
ldr r1, =0x3
#endif
str r1, [r0, #UDIVSLOT_OFFSET]
ldr r1, =0x4f4f4f4f
str r1, [r0, #UTXH_OFFSET]   @'O'
mov pc, lr

这是配主频的代码，没啥好说的
ldr   r1, [r0, #CLK_DIV0_OFFSET] /*Set Clock Divider*/
bic r1, r1, #0x30000
bic r1, r1, #0xff00
bic r1, r1, #0xff
ldr r2, =CLK_DIV_VAL
orr r1, r1, r2
str r1, [r0, #CLK_DIV0_OFFSET]

ldr r1, =APLL_VAL
str r1, [r0, #APLL_CON_OFFSET]
ldr r1, =MPLL_VAL
str r1, [r0, #MPLL_CON_OFFSET]

ldr r1, =0x80200103    /* FOUT of EPLL is 96MHz */
str r1, [r0, #EPLL_CON0_OFFSET]
ldr r1, =0x0
str r1, [r0, #EPLL_CON1_OFFSET]

ldr r1, [r0, #CLK_SRC_OFFSET] /* APLL, MPLL, EPLL select to Fout */

最后要注意一下同步模式：

内核和总线不同步时，需用异步模式。

我改变了系统主频，但没有改成异步模式，结果导致串口异常。

本篇文章来源于 Linux公社网站(www.linuxidc.com)  原文链接：http://www.linuxidc.com/Linux/2011-09/42027.htm