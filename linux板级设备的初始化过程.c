//linux板级设备的初始化过程(转) 
start_kernel() [init/main.c]-----> setup_arch(&command_line)[ arch/arm/kernel/setup.c ] 
-----> mdesc =setup_machine(machine_arch_type) [ arch/arm/kernel/setup.c ]----> 
list = lookup_machine_type(nr)[ arch/arm/kernel/setup.c ] ----> return struct machine_desc. 

 

//内核在启动的时候就是最先运行start_kernel() ,然后她就会调用体系结构相关的setup_arch(&command_line),如arm体系结构的在arch/arm/kernel/setup.c中, 进一步, 她就要初始化板级相关的设备,   但在此之前,她必须找到这块目标板的描述结构, 所以她就先通过lookup_machine_type(nr)来查找这个结构,传入的参数是又uboot传过来的, 存储在r2中. 如假设她传入的是'SMDK2410' 的nr,lookup_machine_type(nr) 就会找到如下的machine_desc.这个结构在一个专门描述sddk2410的文件中--arch/arm/mach-s3c2410/mach-smdk2410.c 


MACHINE_START(SMDK2410, "SMDK2410") // @TODO: request a new identifier and switch
                  //to SMDK2410 //
    // Maintainer: Jonas Dietsche //
    .phys_io    = S3C2410_PA_UART,
    .io_pg_offst    = (((u32)S3C24XX_VA_UART) >> 18) & 0xfffc,
    .boot_params    = S3C2410_SDRAM_PA + 0x100,
//重要的板级初始化函数
    .map_io        = smdk2410_map_io,
    .init_irq    = s3c24xx_init_irq,
    .init_machine    = smdk2410_init,
    .timer        = &s3c24xx_timer,
MACHINE_END

//MACHINE_START的第一个参数是用来构造机器的类型的, 如这里的SMDK2410 ,   
//又下面的定义 
//.nr        = MACH_TYPE_##_type 
//有 nr = MACH_TYPE_SMDK2410
//而 MACH_TYPE_SMDK2410这些机器类型则在/include/asm-arm/mach-types.h中定义:
#define MACH_TYPE_SMDK2410             193


//完整的结构描述如下:

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

 

//在arch/arm/mach-s3c2410/mach-smdk2410.c 定义了以下两个函数实现:
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
    //主要是做外围设备的物理地址到虚拟地址的映射
    s3c24xx_init_io(smdk2410_iodesc, ARRAY_SIZE(smdk2410_iodesc));
    //频率的初始化
    s3c24xx_init_clocks(0);
    //串口的初始化
    s3c24xx_init_uarts(smdk2410_uartcfgs, ARRAY_SIZE(smdk2410_uartcfgs));
}

static void __init smdk2410_init(void)
{
    //注册smdk2410特有的设备
    platform_add_devices(smdk2410_devices, ARRAY_SIZE(smdk2410_devices));

    //smdk系列的初始化, 我们知道smdk有2410, 2412, 2440等等, 
    //所以这里她又抽象出了一些共有的相同的部分, 都使用下面的函数做初始化工作. 
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

    //注意这一行, 注册了nand flash的分区信息
    s3c_device_nand.dev.platform_data = &smdk_nand_info;

    //再一次注册设备, 但这一次是smdk共有的. 如nand flash等等
    platform_add_devices(smdk_devs, ARRAY_SIZE(smdk_devs));

   //电源管理的初始化
    s3c2410_pm_init();
}
