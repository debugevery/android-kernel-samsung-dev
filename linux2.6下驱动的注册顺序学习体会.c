linux2.6下驱动的注册顺序学习体会（NAND驱动做例子）2010年02月03日 星期三 15:48    从今天开始，记录下在开发和学习中的心得，便于以后回顾和查缺补漏。最近开始着手6410上的ANDROID移植。现在把之前做的一些工作记录下来。
首先来说说LINUX内核中驱动的注册的顺序，便于以后驱动的编写以及代码的分析。以2.6.29作为内核，NAND的驱动为说明对象。

LINUX内核中，驱动都是使用platform_device来描述，该结构体定义在\include\linux\platform_device.h中。

struct platform_device {
const char    * name;
int        id;
struct device    dev;
u32        num_resources;
struct resource    * resource;
}; 

该结构一个重要的元素是resource，该元素存入了最为重要的设备资源信息，定义在\include\linux\ioport.h中，
struct resource { //name,start,end,flags比较常用
const char *name; 
unsigned long start, end;
unsigned long flags;
struct resource *parent, *sibling, *child;
};

例如：现在我要加载一个NAND驱动。在/arch/arm/mach-s3c6410/mach-smdk6410.c中，在其中添加这样一段代码：
static struct resource s3c_nand_resource[] = {
[0] = {
.start = S3C24XX_PA_NAND,
.end   = S3C24XX_PA_NAND + S3C24XX_SZ_NAND - 1,
.flags = IORESOURCE_MEM,
},
/* 代码中并没有这一项，只是为了说明*/
[1] ={
.start = START,
.end = END,
.flags = IORESOURCE_IRQ,
},
};

这里定义了一组resource，它描述了一个NAND设备的资源，第1组描述了这个usb host设备所占用的总线地址范围，IORESOURCE_MEM表示第1组描述的是内存类型的资源信息。而第2组IORESOURCE_IRQ表示第2组描述的是一组中断类型的资源信息。
如果要在后面调用这两组信息，那么将用到下面几个函数，同样定义在platform_device.h中：

struct resource * platform_get_resource(struct platform_device *dev, unsigned int type, unsigned int num); //根据参数type（如IORESOURCE_MEM），获取资源，num为resource中的第几个

struct int platform_get_irq(struct platform_device *dev, unsigned int num); //获取资源中的中断号

struct resource * platform_get_resource_byname(struct platform_device *dev, unsigned int type, char *name); //根据参数name所指定的名称，来获取指定的资源。使用该函数，resource中每一组需要定义不同的name

int platform_get_irq_byname(struct platform_device *dev, char *name); //根据参数name所指定的名称，来获取资源中的中断号。使用该函数，resource中每一组需要定义不同的name


接下来需要定义platform_device，同样，在mach-s3c6410.c中定义：
struct platform_device s3c_device_nand = {
.name          = "s3c-nand", //注册时候设备的名字，一定要和后面加载驱动时候的名字相同
.id          = -1, //注册时，设备的id号
.num_resources      = ARRAY_SIZE(s3c_nand_resource),
.resource      = s3c_nand_resource, //之前定义的resource
.dev = {
.platform_data = &s3c_nand_mtd_part_info
}
};
其中s3c_nand_mtd_part_info是nand的分区信息，在后面的文章中会提到。

定义完成后，注册platform_device。
static struct platform_device *smdk6410_devices[] __initdata = {
......
&s3c_device_nand, //+ chachi
......
};

static void __init smdk6410_machine_init(void)
{
......
platform_add_devices(smdk6410_devices, ARRAY_SIZE(smdk6410_devices));
}

内核启动会运行下面的代码，这样设备就注册了：
MACHINE_START(SMDK6410, "SMDK6410")
/* Maintainer: Ben Dooks <ben@fluff.org> */
.phys_io    = S3C_PA_UART & 0xfff00000,
.io_pg_offst    = (((u32)S3C_VA_UART) >> 18) & 0xfffc,
.boot_params    = S3C64XX_PA_SDRAM + 0x100,

.init_irq    = s3c6410_init_irq,
.map_io        = smdk6410_map_io,
.init_machine    = smdk6410_machine_init,
.timer        = &s3c24xx_timer,
MACHINE_END

设备注册完成后，需要在驱动程序中加载。我的NAND驱动放在/drivers/mtd/nand/s3c_nand.c中。
static struct platform_driver s3c_nand_driver = {
.probe        = s3c_nand_probe,
.remove        = s3c_nand_remove,
.suspend    = s3c_nand_suspend,
.resume        = s3c_nand_resume,
.driver        = {
.name    = "s3c-nand", 
.owner    = THIS_MODULE,
},
};
注意：这里的name必须和之前platform_device中定义的name同名，这样platform_driver_register()注册时会对所有已注册的所有platform_device中的name和当前注册的platform_driver的driver.name进行比较，只有找到相同的名称的platfomr_device才能注册成功，我之前因为不知道，在这里费了不少时间。

static int __init s3c_nand_init(void)
{
return platform_driver_register(&s3c_nand_driver); //- chachi
}

static void __exit s3c_nand_exit(void)
{
platform_driver_unregister(&s3c_nand_driver);
}

//module_init(s3c_nand_init);
//module_exit(s3c_nand_exit);

通过以上代码，设备就能register和unregister了。当注册成功时会调用platform_driver结构元素probe函数指针，这里就是s3c_nand_probe。驱动的初始化等都是在prob函数中完成的。
 
