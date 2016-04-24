S3C6410��ʱ�Ӻ�PLL
[���ڣ�2011-09-02] ��Դ��Linux����  ���ߣ�aokikyon 

 
S3C6410������PLL���ֱ�ΪAPLL��MPLL��EPLL��

����APLL����ACLK����arm coreʹ�ã�MPLL����HCLKX2��HCLK��PCLK��EPLL���������ʱ�ӣ�����ΪUSB�ṩ48MHzʱ�ӡ�

ARM core��ʱ���ֲ���������Ϊ667MHz��ʵ��ʹ��ʱ��800MHz����û�����⡣

HCLKX2��Ҫ�ṩʱ�Ӹ�DDRʹ�ã������Ե�266MHz��
 

HCLK���Կ���AXI\AHB����ʱ�ӣ�APB���Կ���APB����ʱ�ӡ�

��AXI��AHB���ߵ��������ʱ��Ϊ133MHz����APB���ߵ��������ʱ��Ϊ66MHz��

UART��ʱ�ӿ�����MPLL����EPLL�ṩ��

=================��������===============================================

6410����ʱ�ӳ�ʼ������u-boot�����ģ�linux��ֻ�Ǹ����ȡ����ֵ��

1��u-boot-1.1.6/include/configs/smdk6410.h

APLL���ã�����666MHz�����ã��ɲο��ֲ��޸� 
#define APLL_MDIV 333 
#define APLL_PDIV 3
#define APLL_SDIV 1

MPLL���ã��ҳ����޸ģ�UART��û�������
/* fixed MPLL 533MHz */
#define MPLL_MDIV 266
#define MPLL_PDIV 3
#define MPLL_SDIV 1

APLL��Ƶ����
#define Startup_APLLdiv   0
MPLL��HCLKX2�ķ�Ƶ����
#define Startup_HCLKx2div 2
HCLKX2��PCLK�ķ�Ƶ����
#define Startup_PCLKdiv   3
HCLKX2��HCLK�ķ�Ƶ����
#define Startup_HCLKdiv   1
MPLL��Ƶ����
#define Startup_MPLLdiv   1

#define CONFIG_SYNC_MODE
ͬ��ģʽ�£�HCLKʱ����APLL��Ƶ����

2��u-boot-1.1.6/board/samsung/smdk6410/lowlevel_init.s
������UART��ʱ�ӣ�UART��ʱ����EXT_UCLK1�ṩ��UCLK��MPLL�ķ�Ƶ������MPLL��UART�Ͳ�����
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

#if defined(CONFIG_CLKSRC_CLKUART)//UART��ʱ����EXT_UCLK1�ṩ
ldr r1, =0xe45    /* UARTCLK SRC = 11 => EXT_UCLK1*/
#else
ldr r1, =0x245    /* UARTCLK SRC = x0 => PCLK */
#endif
str r1, [r0, #UCON_OFFSET]
#if defined(CONFIG_UART_50)
ldr r1, =0x1A
#elif defined(CONFIG_UART_66) //EXT_UCLK1Ϊ66Mʱ�ķ�Ƶ����
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

��������Ƶ�Ĵ��룬ûɶ��˵��
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

���Ҫע��һ��ͬ��ģʽ��

�ں˺����߲�ͬ��ʱ�������첽ģʽ��

�Ҹı���ϵͳ��Ƶ����û�иĳ��첽ģʽ��������´����쳣��

��ƪ������Դ�� Linux������վ(www.linuxidc.com)  ԭ�����ӣ�http://www.linuxidc.com/Linux/2011-09/42027.htm