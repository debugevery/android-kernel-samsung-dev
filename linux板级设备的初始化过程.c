//linux�弶�豸�ĳ�ʼ������(ת) 
start_kernel() [init/main.c]-----> setup_arch(&command_line)[ arch/arm/kernel/setup.c ] 
-----> mdesc =setup_machine(machine_arch_type) [ arch/arm/kernel/setup.c ]----> 
list = lookup_machine_type(nr)[ arch/arm/kernel/setup.c ] ----> return struct machine_desc. 

 

//�ں���������ʱ�������������start_kernel() ,Ȼ�����ͻ������ϵ�ṹ��ص�setup_arch(&command_line),��arm��ϵ�ṹ����arch/arm/kernel/setup.c��, ��һ��, ����Ҫ��ʼ���弶��ص��豸,   ���ڴ�֮ǰ,�������ҵ����Ŀ���������ṹ, ����������ͨ��lookup_machine_type(nr)����������ṹ,����Ĳ�������uboot��������, �洢��r2��. ��������������'SMDK2410' ��nr,lookup_machine_type(nr) �ͻ��ҵ����µ�machine_desc.����ṹ��һ��ר������sddk2410���ļ���--arch/arm/mach-s3c2410/mach-smdk2410.c 


MACHINE_START(SMDK2410, "SMDK2410") // @TODO: request a new identifier and switch
                  //to SMDK2410 //
    // Maintainer: Jonas Dietsche //
    .phys_io    = S3C2410_PA_UART,
    .io_pg_offst    = (((u32)S3C24XX_VA_UART) >> 18) & 0xfffc,
    .boot_params    = S3C2410_SDRAM_PA + 0x100,
//��Ҫ�İ弶��ʼ������
    .map_io        = smdk2410_map_io,
    .init_irq    = s3c24xx_init_irq,
    .init_machine    = smdk2410_init,
    .timer        = &s3c24xx_timer,
MACHINE_END

//MACHINE_START�ĵ�һ������������������������͵�, �������SMDK2410 ,   
//������Ķ��� 
//.nr        = MACH_TYPE_##_type 
//�� nr = MACH_TYPE_SMDK2410
//�� MACH_TYPE_SMDK2410��Щ������������/include/asm-arm/mach-types.h�ж���:
#define MACH_TYPE_SMDK2410             193


//�����Ľṹ��������:

struct machine_desc {
    //
  //Note! The first four elements are used
  //by assembler code in head-armv.S
    //
    unsigned int        nr;        // architecture number    //
    unsigned int        phys_io;    // start of physical io    //
    unsigned int        io_pg_offst;    // byte offset for io 
                      //page tabe entry    //

    const char        *name;        // architecture name    //
    unsigned long        boot_params;    // tagged list        //

    unsigned int        video_start;    // start of video RAM    //
    unsigned int        video_end;    // end of video RAM    //

    unsigned int        reserve_lp0 :1;    // never has lp0    //
    unsigned int        reserve_lp1 :1;    // never has lp1    //
    unsigned int        reserve_lp2 :1;    // never has lp2    //
    unsigned int        soft_reboot :1;    // soft reboot        //
    void            (*fixup)(struct machine_desc *,
                    struct tag *, char **,
                    struct meminfo *);
    void            (*map_io)(void);// IO mapping function    //
    void            (*init_irq)(void);
    struct sys_timer    *timer;        // system tick timer    //
    void            (*init_machine)(void);
};


//
//Set of macros to define architecture features. This is built into
//a table by the linker.
//
#define MACHINE_START(_type,_name)            \
static const struct machine_desc __mach_desc_##_type    \
__used                            \
__attribute__((__section__(".arch.info.init"))) = {    \
    .nr        = MACH_TYPE_##_type,        \
    .name        = _name,

#define MACHINE_END                \
};

 

//��arch/arm/mach-s3c2410/mach-smdk2410.c ������������������ʵ��:
//
static struct map_desc smdk2410_iodesc[] __initdata = {
// nothing here yet //
};

static struct platform_device *smdk2410_devices[] __initdata = {
    &s3c_device_usb,
    &s3c_device_lcd,
    &s3c_device_wdt,
    &s3c_device_i2c,
    &s3c_device_iis,
};

static void __init smdk2410_map_io(void)
{
    //��Ҫ������Χ�豸�������ַ�������ַ��ӳ��
    s3c24xx_init_io(smdk2410_iodesc, ARRAY_SIZE(smdk2410_iodesc));
    //Ƶ�ʵĳ�ʼ��
    s3c24xx_init_clocks(0);
    //���ڵĳ�ʼ��
    s3c24xx_init_uarts(smdk2410_uartcfgs, ARRAY_SIZE(smdk2410_uartcfgs));
}

static void __init smdk2410_init(void)
{
    //ע��smdk2410���е��豸
    platform_add_devices(smdk2410_devices, ARRAY_SIZE(smdk2410_devices));

    //smdkϵ�еĳ�ʼ��, ����֪��smdk��2410, 2412, 2440�ȵ�, 
    //�����������ֳ������һЩ���е���ͬ�Ĳ���, ��ʹ������ĺ�������ʼ������. 
    smdk_machine_init();
}

// devices we initialise //

static struct platform_device __initdata *smdk_devs[] = {
    &s3c_device_nand,
    &smdk_led4,
    &smdk_led5,
    &smdk_led6,
    &smdk_led7,
};


void __init smdk_machine_init(void)
{
    // Configure the LEDs (even if we have no LED support)//

    s3c2410_gpio_cfgpin(S3C2410_GPF4, S3C2410_GPF4_OUTP);
    s3c2410_gpio_cfgpin(S3C2410_GPF5, S3C2410_GPF5_OUTP);
    s3c2410_gpio_cfgpin(S3C2410_GPF6, S3C2410_GPF6_OUTP);
    s3c2410_gpio_cfgpin(S3C2410_GPF7, S3C2410_GPF7_OUTP);

    s3c2410_gpio_setpin(S3C2410_GPF4, 1);
    s3c2410_gpio_setpin(S3C2410_GPF5, 1);
    s3c2410_gpio_setpin(S3C2410_GPF6, 1);
    s3c2410_gpio_setpin(S3C2410_GPF7, 1);

    if (machine_is_smdk2443())
        smdk_nand_info.twrph0 = 50;

    //ע����һ��, ע����nand flash�ķ�����Ϣ
    s3c_device_nand.dev.platform_data = &smdk_nand_info;

    //��һ��ע���豸, ����һ����smdk���е�. ��nand flash�ȵ�
    platform_add_devices(smdk_devs, ARRAY_SIZE(smdk_devs));

   //��Դ����ĳ�ʼ��
    s3c2410_pm_init();
}
