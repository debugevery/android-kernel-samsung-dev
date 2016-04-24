//Real6410移植Linux-2.6.39.1记录                                                                                                                                                                                             
//启动cramfs根文件系统                                                                                                                                                                                                       
//[日期：2011-06-24] 来源：csdn  作者：kevinjz                                                                                                                                                                               
//                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
// 主题：Real6410移植linux-2.6.39.1                                                                                                                                                                                        
// 作者：kevinjz2010@gmail.com                                                                                                                                                                                             
// 版权：kevinjz原创                                                                                                                                                                                                       
// 平台：linux-2.39.1 real6410 （real6410开发板）                                                                                                                                                                          
// 发布日期：2011-06-21                                                                                                                                                                                                    
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
// 最后修改：2011-06-23                                                                                                                                                                                                    
// 注意事项：欢迎转载，但不得在转载的时候擅自修改、删除文章的任何部分                                                                                                                                                      
//-----------------------------------------------------------                                                                                                                                                              
//                                                                                                                                                                                                                           
//一、于http://www.kernel.org/下载linux-2.6.39.1内核源码，解压至文件夹。                                                                                                                                                     
//                                                                                                                                                                                                                           
//二、进入源码所在文件夹,对内核进行配置                                                                                                                                                                                      
//                                                                                                                                                                                                                           
$ make menuconfig                                                                                                                                                                                                          
                                                                                                                                                                                                                           
//将arch/arm/configs/s3c6400_deconfig拷贝至内核根目录，并修改根目录中的Makefile，将其中的                                                                                                                                    
//                                                                                                                                                                                                                           
ARCH = arm                                                                                                                                                                                                                 
                                                                                                                                                                                                                           
CROSS_COMPILE = arm-linux-                                                                                                                                                                                                 
                                                                                                                                                                                                                           
$ make s3c6400_deconfig                                                                                                                                                                                                    
                                                                                                                                                                                                                           
//以上计生成了s3c6410的默认配置，之后在次基础上进行修改。                                                                                                                                                                    
//                                                                                                                                                                                                                           
//修改内核中的机器识别码，/arch/arm/tools/mach-types.h，搜索6410，将其机器码改为1626（与u-boot中的匹配即可，也可一修改uboot中的机器码/include/configs/smdk6410.h                                                             
//                                                                                                                                                                                                                           
//注：编译器采用gcc-4.5.1                                                                                                                                                                                                    
//                                                                                                                                                                                                                           
//三、添加SD驱动（参考华天正论坛上的移植方法）：                                                                                                                                                                             
//                                                                                                                                                                                                                           
// 首先，platform设备注册。修改arch/arm/mach-s3c64xx/mach-real6410.c文件                                                                                                                                                   
//                                                                                                                                                                                                                           
//在其中加入：                                                                                                                                                                                                               
                                                                                                                                                                                                                           
&s3c_device_hsmmc0,                                                                                                                                                                                                        
                                                                                                                                                                                                                           
&s3c_device_hsmmc1,                                                                                                                                                                                                        
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
static struct platform_device *real6410_devices[] __initdata = {//定义6410中的外设->platform_device结构体中的设备种类，各种外设的具体定义一般在plat文件夹中定义。                                                          
                                                                                                                                                                                                                           
//其中包括外设的name，此值需要和相应外设驱动中platform_driver结构体中的name相对应，                                                                                                                                        
                                                                                                                                                                                                                           
//如nand的名称在arch/arm/plat-sumsang/dev-nand.h中                                                                                                                                                                         
                                                                                                                                                                                                                           
//定义为"s3c6410-nand"，在驱动文件/drivers/mtd/nand/s3c_nand.c中对应为"s3c6410-nand"                                                                                                                                       
                                                                                                                                                                                                                           
//又如SD->hsmmc0外设，其name在arch/arm/plat-sumsang/dev-hsmmc.c中定义为"s3c-sdhci",                                                                                                                                        
                                                                                                                                                                                                                           
//在驱动文件drivers/mmc/host/sdhci-s3c.c中的platform_driver中对应为"s3c-sdhci"                                                                                                                                             
                                                                                                                                                                                                                           
//每个外设有其独有的资源->resource（包括寄存器资源以及中断资源，                                                                                                                                                           
                                                                                                                                                                                                                           
//其中申明了外设在cpu寄存其中的地址范围以及中断种类，一般在plat文件夹中定义）                                                                                                                                              
                                                                                                                                                                                                                           
//每个外设有其独有的定义结构体（在plat文件夹中对应的头文件中定义）                                                                                                                                                         
                                                                                                                                                                                                                           
&real6410_device_eth,                                                                                                                                                                                                      
                                                                                                                                                                                                                           
&s3c_device_hsmmc0,                                                                                                                                                                                                        
                                                                                                                                                                                                                           
&s3c_device_hsmmc1,                                                                                                                                                                                                        
                                                                                                                                                                                                                           
&s3c_device_fb,                                                                                                                                                                                                            
                                                                                                                                                                                                                           
&s3c_device_nand,                                                                                                                                                                                                          
                                                                                                                                                                                                                           
&s3c_device_adc,                                                                                                                                                                                                           
                                                                                                                                                                                                                           
&s3c_device_ts,                                                                                                                                                                                                            
                                                                                                                                                                                                                           
&s3c_device_ohci,                                                                                                                                                                                                          
                                                                                                                                                                                                                           
};                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
// 定义platdata，若要使用自定义数据，则在上面的文件中添加：                                                                                                                                                                
//                                                                                                                                                                                                                           
//--------------------------------SD---------------------------------                                                                                                                                                    
                                                                                                                                                                                                                           
//static struct s3c_sdhci_platdata real6410_hsmmc0_pdata = {//该结构体位于plat/sdhci.h                                                                                                                                     
                                                                                                                                                                                                                           
.max_width = 4,                                                                                                                                                                                                            
                                                                                                                                                                                                                           
.cd_type = S3C_SDHCI_CD_INTERNAL,                                                                                                                                                                                          
                                                                                                                                                                                                                           
};                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
static struct s3c_sdhci_platdata real6410_hsmmc1_pdata = {                                                                                                                                                                 
                                                                                                                                                                                                                           
.max_width = 4,                                                                                                                                                                                                            
                                                                                                                                                                                                                           
.cd_type = S3C_SDHCI_CD_PERMANENT,                                                                                                                                                                                         
                                                                                                                                                                                                                           
};                                                                                                                                                                                                                       
                                                                                                                                                                                                                           
//若要使用内核默认设置数据，则在arch/arm/plat-samsung/dev-hsmmc（num）.c中定义了，可以直接使用。                                                                                                                             
//                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
// 在real6410_machine_init函数中加入：                                                                                                                                                                                     
//                                                                                                                                                                                                                           
//--------------------------------若使用自定义，则添加如下--------------SD驱动初始化注册                                                                                                                                   
                                                                                                                                                                                                                           
// s3c_sdhci0_set_platdata(&real6410_hsmmc0_pdata);//该函数位于plat-samsung/dev-hsmmc(0~3).c中                                                                                                                             
                                                                                                                                                                                                                           
// s3c_sdhci1_set_platdata(&real6410_hsmmc1_pdata);                                                                                                                                                                        
                                                                                                                                                                                                                           
//--------------------------------若使用默认定义则用以下的-----------------------------------                                                                                                                              
                                                                                                                                                                                                                           
s3c_sdhci0_set_platdata(&s3c_hsmmc0_def_platdata);                                                                                                                                                                         
                                                                                                                                                                                                                           
s3c_sdhci1_set_platdata(&s3c_hsmmc1_def_platdata);                                                                                                                                                                         
                                                                                                                                                                                                                           
//实际经测试，此步骤可以省略，应该内核某处已经完成了这个任务，但我没有找到在哪里。                                                                                                                                         
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
//                                                                                                                                                                                                                           
// 加入头文件                                                                                                                                                                                                              
                                                                                                                                                                                                                           
//#include <plat/sdhci.h>                                                                                                                                                                                                    
                                                                                                                                                                                                                           
//#include <linux/mmc/host.h>                                                                                                                                                                                                
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
5、在内核中添加配置中选择SD驱动                                                                                                                                                                                            
                                                                                                                                                                                                                           
$ make menuconfig,按REAL手册中的添加SD驱动                                                                                                                                                                                 
                                                                                                                                                                                                                           
/另外在file systems->native language support中，将default NLS option的值改为utf8，并选上NLS UTF-8 以及nls iso8859-1，simple chinene。                                                                                       
/                                                                                                                                                                                                                           
/                                                                                                                                                                                                                           
/                                                                                                                                                                                                                           
/自此，SD驱动配置完成                                                                                                                                                                                                       
/                                                                                                                                                                                                                           
/                                                                                                                                                                                                                           
/四、添加nand驱动（参考华天正论坛上的移植方法），                                                                                                                                                                           
/                                                                                                                                                                                                                           
/                                                                                                                                                                                                                           
/1、在/arch/arm/mach-s3c64xx/mach-real6410.c中添加分区信息（不许要添加头文件）                                                                                                                                              
/                                                                                                                                                                                                                           
struct mtd_partition real6410_nand_part[] = {                                                                                                                                                                              
                                                                                                                                                                                                                           
#if 0                                                                                                                                                                                                                      
                                                                                                                                                                                                                           
{                                                                                                                                                                                                                          
                                                                                                                                                                                                                           
.name = "Bootloader",                                                                                                                                                                                                      
                                                                                                                                                                                                                           
.offset = 0,                                                                                                                                                                                                               
                                                                                                                                                                                                                           
.size = (256*SZ_1K),                                                                                                                                                                                                       
                                                                                                                                                                                                                           
.mask_flags = MTD_CAP_NANDFLASH,                                                                                                                                                                                           
                                                                                                                                                                                                                           
},                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
{                                                                                                                                                                                                                          
                                                                                                                                                                                                                           
.name ="Kernel",                                                                                                                                                                                                           
                                                                                                                                                                                                                           
.offset = (256*SZ_1K),                                                                                                                                                                                                     
                                                                                                                                                                                                                           
.size = (4*SZ_1M)-(256*SZ_1K),                                                                                                                                                                                             
                                                                                                                                                                                                                           
.mask_flags = MTD_CAP_NANDFLASH,                                                                                                                                                                                           
                                                                                                                                                                                                                           
},                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
#endif                                                                                                                                                                                                                     
                                                                                                                                                                                                                           
{                                                                                                                                                                                                                          
                                                                                                                                                                                                                           
.name = "cramfs",                                                                                                                                                                                                          
                                                                                                                                                                                                                           
.offset = (4*SZ_1M),                                                                                                                                                                                                       
                                                                                                                                                                                                                           
.size = (4*SZ_1M),//此处华天正论坛置顶贴上说是定义为，(4*SZ_1M)，但经过实验不成功，可能和UOOT中的定义要匹配才行。                                                                                                          
                                                                                                                                                                                                                           
},                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
{                                                                                                                                                                                                                          
                                                                                                                                                                                                                           
.name = "ubifs",                                                                                                                                                                                                           
                                                                                                                                                                                                                           
.offset = MTDPART_OFS_APPEND,                                                                                                                                                                                              
                                                                                                                                                                                                                           
.size = MTDPART_SIZ_FULL,                                                                                                                                                                                                  
                                                                                                                                                                                                                           
},                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
};                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
//2、定义，在上面的文件加入：                                                                                                                                                                                                
                                                                                                                                                                                                                           
static struct s3c2410_nand_set real6410_nand_sets[] = {                                                                                                                                                                    
                                                                                                                                                                                                                           
[0] = {                                                                                                                                                                                                                    
                                                                                                                                                                                                                           
.name = "nand",                                                                                                                                                                                                            
                                                                                                                                                                                                                           
.nr_chips = 1,                                                                                                                                                                                                             
                                                                                                                                                                                                                           
.nr_partitions = ARRAY_SIZE(real6410_nand_part),                                                                                                                                                                           
                                                                                                                                                                                                                           
.partitions = real6410_nand_part,                                                                                                                                                                                          
                                                                                                                                                                                                                           
},                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
};                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
static struct s3c2410_platform_nand real6410_nand_info = {//读写nand的时钟信息，在S3C6410手册中查找数据                                                                                                                    
                                                                                                                                                                                                                           
.tacls = 25,                                                                                                                                                                                                               
                                                                                                                                                                                                                           
.twrph0 = 55,                                                                                                                                                                                                              
                                                                                                                                                                                                                           
.twrph1 = 40,                                                                                                                                                                                                              
                                                                                                                                                                                                                           
.nr_sets = ARRAY_SIZE(real6410_nand_sets),                                                                                                                                                                                 
                                                                                                                                                                                                                           
.sets = real6410_nand_sets,                                                                                                                                                                                                
                                                                                                                                                                                                                           
};                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
<!-- @page { margin: 2cm } P { margin-bottom: 0.21cm } -->                                                                                                                                                                 
                                                                                                                                                                                                                           
// 在real6410_machine_init函数中加入：                                                                                                                                                                                     
//                                                                                                                                                                                                                           
//---------------------------------nand驱动初始化注册-----------------------------------------                                                                                                                             
                                                                                                                                                                                                                           
s3c_nand_set_platdata(&real6410_nand_info);                                                                                                                                                                                
                                                                                                                                                                                                                           
// 配置内核                                                                                                                                                                                                                
                                                                                                                                                                                                                           
$ make menuconfig                                                                                                                                                                                                          
                                                                                                                                                                                                                           
device driver->MTD support中选中                                                                                                                                                                                           
                                                                                                                                                                                                                           
MTD partitioning support 、Command line partition table parsing、Caching block device access to MTD devices、NAND Device Support、enable ubi                                                                               
                                                                                                                                                                                                                           
//在nand device suppot中选中 NAND Flash support for Samsung S3C SoCs 、 Samsung S3C NAND driver debug、Samsung S3C NAND Hardware ECC 。                                                                                      
//                                                                                                                                                                                                                           
//此处需要注意：对上面几个选项”shift+/”，发现其是对2410进行配置的，所以需要nand驱动文件夹中的Kconfig，将/drivers/mtd/nand/Konfig修改，把对应选项的2410改成3add_mtd_partitionsSC，原因查看Makefile中的对应选项的config要求。
//                                                                                                                                                                                                                           
//在file systems->misc filesystem-> 中加入cramfs、UBI的支持，可以参照real28内核的配置                                                                                                                                        
//                                                                                                                                                                                                                           
//5、将real6410 28内核中的/drivers/mtd/nand/s3c_nand.c拷贝之39内核的相应文件夹，并修改probe函数#if defined(CONFIG_MTD_NAND_S3C_HWECC)之前的部分，可以将友善38内核的相应部分复制过来。                                        
//                                                                                                                                                                                                                           
//6、编译cramfs文件系统                                                                                                                                                                                                      
//                                                                                                                                                                                                                           
//$sudo apt-get install cramfsprogs                                                                                                                                                                                          
//                                                                                                                                                                                                                           
//拷贝REAL6410的cramfs系统源码，                                                                                                                                                                                             
//                                                                                                                                                                                                                           
//$mkcramfs root_mkfs rootfs.cramfs                                                                                                                                                                                          
//                                                                                                                                                                                                                           
//下载文件系统到开发板                                                                                                                                                                                                       
//                                                                                                                                                                                                                           
//7、修改内核启动参数                                                                                                                                                                                                        
//                                                                                                                                                                                                                           
//setenv bootargs noinitrd root=/dev/mtdblock0 console=ttySAC0 init=/linuxrc video=fb:AT070TN83                                                                                                                              
//                                                                                                                                                                                                                           
//8、最后当然要检查一下内核选项，配置好之后编译下载；                                                                                                                                                                        
//                                                                                                                                                                                                                           
//9、至此，REAL6410已经能从CRAMFS文件系统启动了！                                                                                                                                                                            
//                                                                                                                                                                                                                           
//
//===================================================================
//参考REAL论坛的移植步骤                                                                                                                                                                                                 
//                                                                                                         
// 首先，修改mach-real6410.c文件                                                                         
//                                                                                                         
// 1添加所需头文件：                                                                                         
                                                                                                         
#incldeu <linux/fb.h>                                                                                    
                                                                                                         
//#include <video/platform_lcd.h>                                                                          
                                                                                                         
//#include <mach/regs-fb.h>                                                                                
                                                                                                         
//#include <plat/fb.h>                                                                                     
                                                                                                         
//#include <mach/regs-gpio.h>                                                                              
                                                                                                         
//#include <mach/regs-modem.h>                                                                             
                                                                                                         
//另外需要将28内核中的regs-lcd.h复制到plat/                                                                
//                                                                                                         
// 2 、加入设备初始化代码                                                                                    
//                                                                                                         
static struct s3c_fb_pd_win real6410_fb_win[] = {                                                        
                                                                                                         
// {                                                                                                     
                                                                                                         
.win_mode = { 4.3" 480x272                                                                               
                                                                                                         
.left_margin = 3,                                                                                        
                                                                                                         
.right_margin = 2,                                                                                       
                                                                                                         
.upper_margin = 1,                                                                                       
                                                                                                         
.lower_margin = 1,                                                                                       
                                                                                                         
.hsync_len = 40,                                                                                         
                                                                                                         
.vsync_len = 1,                                                                                          
                                                                                                         
.xres = 480,                                                                                             
                                                                                                         
.yres = 272,                                                                                             
                                                                                                         
},                                                                                                       
                                                                                                         
.max_bpp = 32,                                                                                           
                                                                                                         
.default_bpp = 16,                                                                                       
                                                                                                         
},                                                                                                     
                                                                                                         
{                                                                                                        
                                                                                                         
.win_mode = { // 7.0" 800x480                                                                          
                                                                                                         
.left_margin = 8,                                                                                        
                                                                                                         
.right_margin = 13,                                                                                      
                                                                                                         
.upper_margin = 7,                                                                                       
                                                                                                         
.lower_margin = 5,                                                                                       
                                                                                                         
.hsync_len = 3,                                                                                          
                                                                                                         
.vsync_len = 1,                                                                                          
                                                                                                         
.xres = 800,                                                                                             
                                                                                                         
.yres = 480,                                                                                             
                                                                                                         
},                                                                                                       
                                                                                                         
.max_bpp = 32,                                                                                           
                                                                                                         
.default_bpp = 16,                                                                                       
                                                                                                         
},                                                                                                       
                                                                                                         
};//根据所用的显示屏尺寸更改                                                                             
                                                                                                         
                                                                                                         
                                                                                                         
static struct s3c_fb_platdata real6410_lcd_pdata __initdata = {                                          
                                                                                                         
.setup_gpio = s3c64xx_fb_gpio_setup_24bpp,                                                               
                                                                                                         
.win[0] = &real6410_fb_win[0],                                                                           
                                                                                                         
.vidcon0 = VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,                                                     
                                                                                                         
.vidcon1 = VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,                                                        
                                                                                                         
};                                                                                                       
                                                                                                         
static struct map_desc real6410_iodesc[] = {                                                             
                                                                                                         
{                                                                                                        
                                                                                                         
// LCD support                                                                                         
                                                                                                         
.virtual = (unsigned long)S3C_VA_LCD,                                                                    
                                                                                                         
.pfn = __phys_to_pfn(S3C_PA_FB),                                                                         
                                                                                                         
.length = SZ_16K,                                                                                        
                                                                                                         
.type = MT_DEVICE,                                                                                       
                                                                                                         
},                                                                                                       
                                                                                                         
};                                                                                                       
                                                                                                         
在platform_device中加入                                                                                  
                                                                                                         
&s3c_device_fb,                                                                                          
                                                                                                         
在real6410_map_io中加入                                                                                  
                                                                                                         
s3c64xx_init_io(real6410_iodesc, ARRAY_SIZE(real6410_iodesc));                                           
                                                                                                         
// set the LCD type                                                                                    
                                                                                                         
tmp = __raw_readl(S3C64XX_SPCON);                                                                        
                                                                                                         
tmp &= ~S3C64XX_SPCON_LCD_SEL_MASK;                                                                      
                                                                                                         
tmp |= S3C64XX_SPCON_LCD_SEL_RGB;                                                                        
                                                                                                         
__raw_writel(tmp, S3C64XX_SPCON);                                                                        
                                                                                                         
                                                                                                         
                                                                                                         
// remove the LCD bypass                                                                               
                                                                                                         
tmp = __raw_readl(S3C64XX_MODEM_MIFPCON);                                                                
                                                                                                         
tmp &= ~MIFPCON_LCD_BYPASS;                                                                              
                                                                                                         
__raw_writel(tmp, S3C64XX_MODEM_MIFPCON);                                                                
                                                                                                         
在real6410_machine_init加入注册代码                                                                      
                                                                                                         
s3c_fb_set_platdata(&real6410_lcd_pdata);                                                                
                                                                                                         
// 3、修改/mach-s3c64xx/map.h，加入                                                                         
//                                                                                                         
                                                                                                         
                                                                                                         
#define S3C64XX_VA_HOSTIFA S3C_ADDR(0x00B00000)                                                          
                                                                                                         
#define S3C64XX_PA_HOSTIFA (0x74000000)                                                                  
                                                                                                         
#define S3C64XX_SZ_HOSTIFA SZ_1M                                                                         
                                                                                                         
                                                                                                         
                                                                                                         
#define S3C64XX_VA_HOSTIFB S3C_ADDR(0x00C00000)                                                          
                                                                                                         
#define S3C64XX_PA_HOSTIFB (0x74100000)                                                                  
                                                                                                         
#define S3C64XX_SZ_HOSTIFB SZ_1M                                                                         
                                                                                                         
                                                                                                         
                                                                                                         
// 4、  修改plat-samsung/dev-fb.c，加入                                                                       
//                                                                                                         
static struct s3c_platform_fb default_fb_data __initdata = {                                             
                                                                                                         
.hw_ver = 0x40,                                                                                          
                                                                                                         
.clk_name = "lcd",                                                                                       
                                                                                                         
.nr_wins = 5,                                                                                            
                                                                                                         
.default_win = CONFIG_FB_S3C,                                                                            
                                                                                                         
.swap = FB_SWAP_HWORD,                                                                                   
                                                                                                         
};                                                                                                       
                                                                                                         
//并注意s3c_device_fb中的设备名称必须和驱动中的名称相对应，否则驱动不会被加载                              
//                                                                                                         
//                                                                                                         
//                                                                                                         
//修改plat/fb.h                                                                                            
//                                                                                                         
#define FB_SWAP_WORD (1 << 24)                                                                           
                                                                                                         
#define FB_SWAP_HWORD (1 << 16)                                                                          
                                                                                                         
#define FB_SWAP_BYTE (1 << 8)                                                                            
                                                                                                         
#define FB_SWAP_BIT (1 << 0)                                                                             
                                                                                                         
struct s3c_platform_fb {                                                                                 
                                                                                                         
int hw_ver;                                                                                              
                                                                                                         
const char clk_name[16];                                                                                 
                                                                                                         
int nr_wins;                                                                                             
                                                                                                         
int nr_buffers[5];                                                                                       
                                                                                                         
int default_win;                                                                                         
                                                                                                         
int swap;                                                                                                
                                                                                                         
                                                                                                         
                                                                                                         
void (*cfg_gpio)(struct platform_device *dev);                                                           
                                                                                                         
int (*backlight_on)(struct platform_device *dev);                                                        
                                                                                                         
int (*reset_lcd)(struct platform_device *dev);                                                           
                                                                                                         
};                                                                                                       
                                                                                                         
//4、在plat/map-base.h加入                                                                                 
//                                                                                                         
//#define S3C_VA_LCD S3C_ADDR(0x01100000) // LCD                                                         
//                                                                                                         
//                                                                                                         
//                                                                                                         
//5、将28内核中/drivers/video/中samsung文件夹拷贝至相对应目录                                              
//                                                                                                         
//6、修改video中的Kconfig，                                                                                
//                                                                                                         
//加入source “drivers/video/samsung/Kconfig”，并将CONFIG_FB_S3C改成别的名字。                            
//                                                                                                         
//7、修改video中的Makefile，加入                                                                           
//                                                                                                         
//:obj-$(CONFIG_FB_S3C) += SAMSUNG/                                                                        
//                                                                                                         
//8、配置内核                                                                                              
//                                                                                                         
//$make menuconfig                                                                                         
//                                                                                                         
//在 device drivers->Graphics support->Support for frame buffer devices中选中                              
//                                                                                                         
//S3C Framebuffer Support                                                                                  
//                                                                                                         
//                                                                                                         
//                                                                                                         
//S3C Lcd Support Advanced options for S3C Framebuffer                                                     
//                                                                                                         
//Select BPP(Bits Per Pixel) (16 BPP) --->                                                                 
//                                                                                                         
//Number of Framebuffers（4）                                                                              
//                                                                                                         
//Enable Virtual Screen Enable Double Buffering                                                            
//                                                                                                         
//9、编译会有很多错误，大多是头文件的位置问题                                                              
//                                                                                                         
//10、修改samsung/Makefile，屏蔽obj-$(CONFIG_FB_S3C_VIDEO) += ch7026.o，以及s3cfb_video.c中的ch7026_init();
//                                                                                                         
//11、s3cfb_fimd4x.c中的错误按照REAL论坛上的修改，并将1222行屏蔽。                                         
//                                                                                                         
//12、s3cfb.c中的驱动名称和之前设备名称需要对应                                                            
//                                                                                                         
//13、内核启动参数：                                                                                       
//                                                                                                         
//setenv bootargs noinitrd root=/dev/mtdblock0 console=ttySAC0 init=/linuxrc video=fb:AT070TN83            
//                                                                                                         
//本篇文章来源于 Linux公社网站(www.linuxidc.com)  原文链接：http://www.linuxidc.com/Linux/2011-06/37703p2.htm
//
//
//===========================================================================     
//
// 1修改USB驱动的KCONFIG：drivers/usb/Kconfig                                                                                                                                                                       
//                                                                                                                                                                                                                   
//找到config USB_ARCH_HAS_OHCI                                                                                                                                                                                       
//                                                                                                                                                                                                                   
//添加efault y if ARCH_S3C64XX                                                                                                                                                                                       
//                                                                                                                                                                                                                   
// 2查找drivers/usb/host/ohci-hcd.c                                                                                                                                                                                 
//                                                                                                                                                                                                                   
//后段程序是否包含：                                                                                                                                                                                                 
//                                                                                                                                                                                                                   
//#if defined(CONFIG_ARCH_S3C2410) || defined(CONFIG_ARCH_S3C64XX)                                                                                                                                                   
//                                                                                                                                                                                                                   
//#include "ohci-s3c2410.c"                                                                                                                                                                                          
//                                                                                                                                                                                                                   
//#define PLATFORM_DRIVER ohci_hcd_s3c2410_driver                                                                                                                                                                    
//                                                                                                                                                                                                                   
//#endif                                                                                                                                                                                                             
//                                                                                                                                                                                                                   
//未包含则加上，并在ohci-s3c2410.c 文件中包含                                                                                                                                                                        
//                                                                                                                                                                                                                   
// 3、检查/arch/arm/plat-samsung/dev-usb.c中的USBplatform信息是否存在，并检查设备名和第二步上面的驱动名是否相同。                                                                                                     
//                                                                                                                                                                                                                   
//并注意：EXPORT_SYMBOL(s3c_device_ohci);                                                                                                                                                                            
//                                                                                                                                                                                                                   
// 4、修改arch/arm/mach-s3c64xx/mach-real6410.c                                                                                                                                                                       
//                                                                                                                                                                                                                   
//加入头文件：                                                                                                                                                                                                       
//                                                                                                                                                                                                                   
//#include <plat/regs-usb-hsotg.h>                                                                                                                                                                                   
                                                                                                                                                                                                                   
//#include <plat/regs-usb-hsotg-phy.h>                                                                                                                                                                               
                                                                                                                                                                                                                   
//#include <linux/usb/ch9.h>                                                                                                                                                                                         
                                                                                                                                                                                                                   
//#include <plat/clock.h>                                                                                                                                                                                            
                                                                                                                                                                                                                   
//#include <plat/clock-clksrc.h>                                                                                                                                                                                     
                                                                                                                                                                                                                   
//#include <mach/regs-clock.h>                                                                                                                                                                                       
                                                                                                                                                                                                                   
//其中注意#include <plat/clock.h>需要放在#include <plat/clock-clksrc.h>之前，不然，clksrc定义中会找不到clk的引用                                                                                                     
//                                                                                                                                                                                                                   
//在platform_device *real6410_devices[] __initdata中添加                                                                                                                                                             
//                                                                                                                                                                                                                   
//&s3c_device_ohci                                                                                                                                                                                                   
//                                                                                                                                                                                                                   
//5、添加时钟初始化函数，从28内核中复制过来                                                                                                                                                                          
//                                                                                                                                                                                                                   
void usb_host_clk_en(int S3C_USB_CLKSRC) {                                                                                                                                                                         
                                                                                                                                                                                                                   
                                                                                                                                                                                                                   
struct clk *otg_clk;                                                                                                                                                                                               
                                                                                                                                                                                                                   
                                                                                                                                                                                                                   
                                                                                                                                                                                                                   
switch (S3C_USB_CLKSRC) {                                                                                                                                                                                          
                                                                                                                                                                                                                   
case 0: // epll clk                                                                                                                                                                                              
                                                                                                                                                                                                                   
writel((readl(S3C_CLK_SRC)& ~S3C6400_CLKSRC_UHOST_MASK)                                                                                                                                                            
                                                                                                                                                                                                                   
|S3C_CLKSRC_EPLL_CLKSEL|S3C_CLKSRC_UHOST_EPLL,                                                                                                                                                                     
                                                                                                                                                                                                                   
S3C_CLK_SRC);                                                                                                                                                                                                      
                                                                                                                                                                                                                   
                                                                                                                                                                                                                   
                                                                                                                                                                                                                   
// USB host colock divider ratio is 2                                                                                                                                                                            
                                                                                                                                                                                                                   
writel((readl(S3C_CLK_DIV1)& ~S3C6400_CLKDIV1_UHOST_MASK)                                                                                                                                                          
                                                                                                                                                                                                                   
|(0<<20), S3C_CLK_DIV1);//这里需要修改1<<20，改为0<<20，查看手册第三章看为什么                                                                                                                                     
                                                                                                                                                                                                                   
break;                                                                                                                                                                                                             
                                                                                                                                                                                                                   
case 1: // oscillator 48M clk                                                                                                                                                                                    
                                                                                                                                                                                                                   
//otg_clk = clk_get(NULL, "otg");                                                                                                                                                                                  
                                                                                                                                                                                                                   
//clk_enable(otg_clk);                                                                                                                                                                                             
                                                                                                                                                                                                                   
writel(readl(S3C_CLK_SRC)& ~S3C6400_CLKSRC_UHOST_MASK, S3C_CLK_SRC);                                                                                                                                               
                                                                                                                                                                                                                   
// otg_phy_init();                                                                                                                                                                                                 
                                                                                                                                                                                                                   
                                                                                                                                                                                                                   
                                                                                                                                                                                                                   
// USB host colock divider ratio is 1                                                                                                                                                                            
                                                                                                                                                                                                                   
writel(readl(S3C_CLK_DIV1)& ~S3C6400_CLKDIV1_UHOST_MASK, S3C_CLK_DIV1);                                                                                                                                            
                                                                                                                                                                                                                   
break;                                                                                                                                                                                                             
                                                                                                                                                                                                                   
default:                                                                                                                                                                                                           
                                                                                                                                                                                                                   
printk(KERN_INFO "Unknown USB Host Clock Source\n");                                                                                                                                                               
                                                                                                                                                                                                                   
BUG();                                                                                                                                                                                                             
                                                                                                                                                                                                                   
break;                                                                                                                                                                                                             
                                                                                                                                                                                                                   
}                                                                                                                                                                                                                  
                                                                                                                                                                                                                   
//接着在real6410_machine_init();中调用                                                                                                                                                                               
//                                                                                                                                                                                                                   
//#ifdef CONFIG_USB_OHCI_HCD                                                                                                                                                                                         
//usb_host_clk_en(0);                                                                                                                                                                                                
//#endif                                                                                                                                                                                                             
////此步将usb使用源选为EPLL                                                                                                                                                                                          
//                                                                                                                                                                                                                   
// 6、将28内核中的/arch/arm/plat-s3c64xx/include/plat/regs-clock.h中的内容复制到                                                                                                                                      
//                                                                                                                                                                                                                   
//39内核中的plat/regs-clock.h中，最好是对比一下两个文件，然后复制其中缺少的。                                                                                                                                        
//                                                                                                                                                                                                                   
// 7、修改UB00T中的CPU时钟初始化代码                                                                                                                                                                                  
//                                                                                                                                                                                                                   
//在/home/kevinjz/ELinux/REAL6410/s3c-u-boot-1.1.6-Real6410/board/samsung/smdk6410/lowlevel_init.S中搜索#EPLL_CON0_OFFSET，                                                                                          
//                                                                                                                                                                                                                   
//将                                                                                                                                                                                                                 
//                                                                                                                                                                                                                   
//ldr r1, =0x80200203改为                                                                                                                                                                                            
//                                                                                                                                                                                                                   
//ldr r1, =0x80200103                                                                                                                                                                                                
//                                                                                                                                                                                                                   
////此步将EPLL使用修改为48M，USB设备要求48MHZ                                                                                                                                                                        
//                                                                                                                                                                                                                   
// 8、配置内核选项                                                                                                                                                                                                    
//                                                                                                                                                                                                                   
//$make menuconfig                                                                                                                                                                                                   
//                                                                                                                                                                                                                   
//选中device drivers->SCSI device support                                                                                                                                                                            
//                                                                                                                                                                                                                   
//选中device drivers->HID Devices->USB Human Interface Device (full HID) support                                                                                                                                     
//                                                                                                                                                                                                                   
//选中device drivers->USB support :                                                                                                                                                                                  
//                                                                                                                                                                                                                   
//Support for Host-side USB                                                                                                                                                                                          
//                                                                                                                                                                                                                   
//USB announce new devices USB device filesystem (DEPRECATED) USB device class-devices (DEPRECATED) Dynamic USB minor allocation                                                                                     
//                                                                                                                                                                                                                   
//USB Monitor                                                                                                                                                                                                        
//                                                                                                                                                                                                                   
//OHCI HCD support                                                                                                                                                                                                   
//                                                                                                                                                                                                                   
//USB Mass Storage support                                                                                                                                                                                           
//                                                                                                                                                                                                                   
//USB Attached SCSI                                                                                                                                                                                                  
//                                                                                                                                                                                                                   
//USB Serial Converter support ---> USB Serial Console device support USB Generic Serial Driver                                                                                                                      
//                                                                                                                                                                                                                   
//另外确保在file systems选择好了USB设备常用的文件系统：NTSF、VFAT、FAT、MSDOS等                                                                                                                                      
//                                                                                                                                                                                                                   
// 9、编译下载，启动后                                                                                                                                                                                                
//                                                                                                                                                                                                                   
//mount -t ntfs /dev/sda1 /mnt/udisk                                                                                                                                                                                 
//                                                                                                                                                                                                                   
//<!-- @page { margin: 2cm } P { margin-bottom: 0.21cm } -->                                                                                                                                                         
//                                                                                                                                                                                                                   
// 10、USB OTG驱动                                                                                                                                                                                                    
//                                                                                                                                                                                                                   
//关键是记得在arch/arm/mach-s3c64xx/cpu.c中添加USBOTG的PA-VA转换表的初始化信息，说白了就是将自己在map-base.h中定义的相关外设的VA(虚拟地址)和在map.h中定义的相关外设的PA（物理地址）联系起来，否则定义了也没用。      
//                                                                                                                                                                                                                   
//其他的只要把real28内核drivers/usb/host/中的s3c-otg文件夹复制到39内核相应位置，然后修改kconfig、makefile等文件，将相关文件编译进内核，根据错误提示修改即可，错误都不复杂，主要就是找不到文件、或者少了什么定义的问题
//                                                                                                                                                                                                                   
//本篇文章来源于 Linux公社网站(www.linuxidc.com)  原文链接：http://www.linuxidc.com/Linux/2011-06/37703p3.htm                                                                                                        