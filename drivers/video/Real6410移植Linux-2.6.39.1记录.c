//Real6410��ֲLinux-2.6.39.1��¼                                                                                                                                                                                             
//����cramfs���ļ�ϵͳ                                                                                                                                                                                                       
//[���ڣ�2011-06-24] ��Դ��csdn  ���ߣ�kevinjz                                                                                                                                                                               
//                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
// ���⣺Real6410��ֲlinux-2.6.39.1                                                                                                                                                                                        
// ���ߣ�kevinjz2010@gmail.com                                                                                                                                                                                             
// ��Ȩ��kevinjzԭ��                                                                                                                                                                                                       
// ƽ̨��linux-2.39.1 real6410 ��real6410�����壩                                                                                                                                                                          
// �������ڣ�2011-06-21                                                                                                                                                                                                    
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
// ����޸ģ�2011-06-23                                                                                                                                                                                                    
// ע�������ӭת�أ���������ת�ص�ʱ�������޸ġ�ɾ�����µ��κβ���                                                                                                                                                      
//-----------------------------------------------------------                                                                                                                                                              
//                                                                                                                                                                                                                           
//һ����http://www.kernel.org/����linux-2.6.39.1�ں�Դ�룬��ѹ���ļ��С�                                                                                                                                                     
//                                                                                                                                                                                                                           
//��������Դ�������ļ���,���ں˽�������                                                                                                                                                                                      
//                                                                                                                                                                                                                           
$ make menuconfig                                                                                                                                                                                                          
                                                                                                                                                                                                                           
//��arch/arm/configs/s3c6400_deconfig�������ں˸�Ŀ¼�����޸ĸ�Ŀ¼�е�Makefile�������е�                                                                                                                                    
//                                                                                                                                                                                                                           
ARCH = arm                                                                                                                                                                                                                 
                                                                                                                                                                                                                           
CROSS_COMPILE = arm-linux-                                                                                                                                                                                                 
                                                                                                                                                                                                                           
$ make s3c6400_deconfig                                                                                                                                                                                                    
                                                                                                                                                                                                                           
//���ϼ�������s3c6410��Ĭ�����ã�֮���ڴλ����Ͻ����޸ġ�                                                                                                                                                                    
//                                                                                                                                                                                                                           
//�޸��ں��еĻ���ʶ���룬/arch/arm/tools/mach-types.h������6410������������Ϊ1626����u-boot�е�ƥ�伴�ɣ�Ҳ��һ�޸�uboot�еĻ�����/include/configs/smdk6410.h                                                             
//                                                                                                                                                                                                                           
//ע������������gcc-4.5.1                                                                                                                                                                                                    
//                                                                                                                                                                                                                           
//�������SD�������ο���������̳�ϵ���ֲ��������                                                                                                                                                                             
//                                                                                                                                                                                                                           
// ���ȣ�platform�豸ע�ᡣ�޸�arch/arm/mach-s3c64xx/mach-real6410.c�ļ�                                                                                                                                                   
//                                                                                                                                                                                                                           
//�����м��룺                                                                                                                                                                                                               
                                                                                                                                                                                                                           
&s3c_device_hsmmc0,                                                                                                                                                                                                        
                                                                                                                                                                                                                           
&s3c_device_hsmmc1,                                                                                                                                                                                                        
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
static struct platform_device *real6410_devices[] __initdata = {//����6410�е�����->platform_device�ṹ���е��豸���࣬��������ľ��嶨��һ����plat�ļ����ж��塣                                                          
                                                                                                                                                                                                                           
//���а��������name����ֵ��Ҫ����Ӧ����������platform_driver�ṹ���е�name���Ӧ��                                                                                                                                        
                                                                                                                                                                                                                           
//��nand��������arch/arm/plat-sumsang/dev-nand.h��                                                                                                                                                                         
                                                                                                                                                                                                                           
//����Ϊ"s3c6410-nand"���������ļ�/drivers/mtd/nand/s3c_nand.c�ж�ӦΪ"s3c6410-nand"                                                                                                                                       
                                                                                                                                                                                                                           
//����SD->hsmmc0���裬��name��arch/arm/plat-sumsang/dev-hsmmc.c�ж���Ϊ"s3c-sdhci",                                                                                                                                        
                                                                                                                                                                                                                           
//�������ļ�drivers/mmc/host/sdhci-s3c.c�е�platform_driver�ж�ӦΪ"s3c-sdhci"                                                                                                                                             
                                                                                                                                                                                                                           
//ÿ������������е���Դ->resource�������Ĵ�����Դ�Լ��ж���Դ��                                                                                                                                                           
                                                                                                                                                                                                                           
//����������������cpu�Ĵ����еĵ�ַ��Χ�Լ��ж����࣬һ����plat�ļ����ж��壩                                                                                                                                              
                                                                                                                                                                                                                           
//ÿ������������еĶ���ṹ�壨��plat�ļ����ж�Ӧ��ͷ�ļ��ж��壩                                                                                                                                                         
                                                                                                                                                                                                                           
&real6410_device_eth,                                                                                                                                                                                                      
                                                                                                                                                                                                                           
&s3c_device_hsmmc0,                                                                                                                                                                                                        
                                                                                                                                                                                                                           
&s3c_device_hsmmc1,                                                                                                                                                                                                        
                                                                                                                                                                                                                           
&s3c_device_fb,                                                                                                                                                                                                            
                                                                                                                                                                                                                           
&s3c_device_nand,                                                                                                                                                                                                          
                                                                                                                                                                                                                           
&s3c_device_adc,                                                                                                                                                                                                           
                                                                                                                                                                                                                           
&s3c_device_ts,                                                                                                                                                                                                            
                                                                                                                                                                                                                           
&s3c_device_ohci,                                                                                                                                                                                                          
                                                                                                                                                                                                                           
};                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
// ����platdata����Ҫʹ���Զ������ݣ�����������ļ�����ӣ�                                                                                                                                                                
//                                                                                                                                                                                                                           
//--------------------------------SD---------------------------------                                                                                                                                                    
                                                                                                                                                                                                                           
//static struct s3c_sdhci_platdata real6410_hsmmc0_pdata = {//�ýṹ��λ��plat/sdhci.h                                                                                                                                     
                                                                                                                                                                                                                           
.max_width = 4,                                                                                                                                                                                                            
                                                                                                                                                                                                                           
.cd_type = S3C_SDHCI_CD_INTERNAL,                                                                                                                                                                                          
                                                                                                                                                                                                                           
};                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
static struct s3c_sdhci_platdata real6410_hsmmc1_pdata = {                                                                                                                                                                 
                                                                                                                                                                                                                           
.max_width = 4,                                                                                                                                                                                                            
                                                                                                                                                                                                                           
.cd_type = S3C_SDHCI_CD_PERMANENT,                                                                                                                                                                                         
                                                                                                                                                                                                                           
};                                                                                                                                                                                                                       
                                                                                                                                                                                                                           
//��Ҫʹ���ں�Ĭ���������ݣ�����arch/arm/plat-samsung/dev-hsmmc��num��.c�ж����ˣ�����ֱ��ʹ�á�                                                                                                                             
//                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
// ��real6410_machine_init�����м��룺                                                                                                                                                                                     
//                                                                                                                                                                                                                           
//--------------------------------��ʹ���Զ��壬���������--------------SD������ʼ��ע��                                                                                                                                   
                                                                                                                                                                                                                           
// s3c_sdhci0_set_platdata(&real6410_hsmmc0_pdata);//�ú���λ��plat-samsung/dev-hsmmc(0~3).c��                                                                                                                             
                                                                                                                                                                                                                           
// s3c_sdhci1_set_platdata(&real6410_hsmmc1_pdata);                                                                                                                                                                        
                                                                                                                                                                                                                           
//--------------------------------��ʹ��Ĭ�϶����������µ�-----------------------------------                                                                                                                              
                                                                                                                                                                                                                           
s3c_sdhci0_set_platdata(&s3c_hsmmc0_def_platdata);                                                                                                                                                                         
                                                                                                                                                                                                                           
s3c_sdhci1_set_platdata(&s3c_hsmmc1_def_platdata);                                                                                                                                                                         
                                                                                                                                                                                                                           
//ʵ�ʾ����ԣ��˲������ʡ�ԣ�Ӧ���ں�ĳ���Ѿ������������񣬵���û���ҵ������                                                                                                                                         
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
//                                                                                                                                                                                                                           
// ����ͷ�ļ�                                                                                                                                                                                                              
                                                                                                                                                                                                                           
//#include <plat/sdhci.h>                                                                                                                                                                                                    
                                                                                                                                                                                                                           
//#include <linux/mmc/host.h>                                                                                                                                                                                                
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
5�����ں������������ѡ��SD����                                                                                                                                                                                            
                                                                                                                                                                                                                           
$ make menuconfig,��REAL�ֲ��е����SD����                                                                                                                                                                                 
                                                                                                                                                                                                                           
/������file systems->native language support�У���default NLS option��ֵ��Ϊutf8����ѡ��NLS UTF-8 �Լ�nls iso8859-1��simple chinene��                                                                                       
/                                                                                                                                                                                                                           
/                                                                                                                                                                                                                           
/                                                                                                                                                                                                                           
/�Դˣ�SD�����������                                                                                                                                                                                                       
/                                                                                                                                                                                                                           
/                                                                                                                                                                                                                           
/�ġ����nand�������ο���������̳�ϵ���ֲ��������                                                                                                                                                                           
/                                                                                                                                                                                                                           
/                                                                                                                                                                                                                           
/1����/arch/arm/mach-s3c64xx/mach-real6410.c����ӷ�����Ϣ������Ҫ���ͷ�ļ���                                                                                                                                              
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
                                                                                                                                                                                                                           
.size = (4*SZ_1M),//�˴���������̳�ö�����˵�Ƕ���Ϊ��(4*SZ_1M)��������ʵ�鲻�ɹ������ܺ�UOOT�еĶ���Ҫƥ����С�                                                                                                          
                                                                                                                                                                                                                           
},                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
{                                                                                                                                                                                                                          
                                                                                                                                                                                                                           
.name = "ubifs",                                                                                                                                                                                                           
                                                                                                                                                                                                                           
.offset = MTDPART_OFS_APPEND,                                                                                                                                                                                              
                                                                                                                                                                                                                           
.size = MTDPART_SIZ_FULL,                                                                                                                                                                                                  
                                                                                                                                                                                                                           
},                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
};                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
//2�����壬��������ļ����룺                                                                                                                                                                                                
                                                                                                                                                                                                                           
static struct s3c2410_nand_set real6410_nand_sets[] = {                                                                                                                                                                    
                                                                                                                                                                                                                           
[0] = {                                                                                                                                                                                                                    
                                                                                                                                                                                                                           
.name = "nand",                                                                                                                                                                                                            
                                                                                                                                                                                                                           
.nr_chips = 1,                                                                                                                                                                                                             
                                                                                                                                                                                                                           
.nr_partitions = ARRAY_SIZE(real6410_nand_part),                                                                                                                                                                           
                                                                                                                                                                                                                           
.partitions = real6410_nand_part,                                                                                                                                                                                          
                                                                                                                                                                                                                           
},                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
};                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
                                                                                                                                                                                                                           
static struct s3c2410_platform_nand real6410_nand_info = {//��дnand��ʱ����Ϣ����S3C6410�ֲ��в�������                                                                                                                    
                                                                                                                                                                                                                           
.tacls = 25,                                                                                                                                                                                                               
                                                                                                                                                                                                                           
.twrph0 = 55,                                                                                                                                                                                                              
                                                                                                                                                                                                                           
.twrph1 = 40,                                                                                                                                                                                                              
                                                                                                                                                                                                                           
.nr_sets = ARRAY_SIZE(real6410_nand_sets),                                                                                                                                                                                 
                                                                                                                                                                                                                           
.sets = real6410_nand_sets,                                                                                                                                                                                                
                                                                                                                                                                                                                           
};                                                                                                                                                                                                                         
                                                                                                                                                                                                                           
<!-- @page { margin: 2cm } P { margin-bottom: 0.21cm } -->                                                                                                                                                                 
                                                                                                                                                                                                                           
// ��real6410_machine_init�����м��룺                                                                                                                                                                                     
//                                                                                                                                                                                                                           
//---------------------------------nand������ʼ��ע��-----------------------------------------                                                                                                                             
                                                                                                                                                                                                                           
s3c_nand_set_platdata(&real6410_nand_info);                                                                                                                                                                                
                                                                                                                                                                                                                           
// �����ں�                                                                                                                                                                                                                
                                                                                                                                                                                                                           
$ make menuconfig                                                                                                                                                                                                          
                                                                                                                                                                                                                           
device driver->MTD support��ѡ��                                                                                                                                                                                           
                                                                                                                                                                                                                           
MTD partitioning support ��Command line partition table parsing��Caching block device access to MTD devices��NAND Device Support��enable ubi                                                                               
                                                                                                                                                                                                                           
//��nand device suppot��ѡ�� NAND Flash support for Samsung S3C SoCs �� Samsung S3C NAND driver debug��Samsung S3C NAND Hardware ECC ��                                                                                      
//                                                                                                                                                                                                                           
//�˴���Ҫע�⣺�����漸��ѡ�shift+/�����������Ƕ�2410�������õģ�������Ҫnand�����ļ����е�Kconfig����/drivers/mtd/nand/Konfig�޸ģ��Ѷ�Ӧѡ���2410�ĳ�3add_mtd_partitionsSC��ԭ��鿴Makefile�еĶ�Ӧѡ���configҪ��
//                                                                                                                                                                                                                           
//��file systems->misc filesystem-> �м���cramfs��UBI��֧�֣����Բ���real28�ں˵�����                                                                                                                                        
//                                                                                                                                                                                                                           
//5����real6410 28�ں��е�/drivers/mtd/nand/s3c_nand.c����֮39�ں˵���Ӧ�ļ��У����޸�probe����#if defined(CONFIG_MTD_NAND_S3C_HWECC)֮ǰ�Ĳ��֣����Խ�����38�ں˵���Ӧ���ָ��ƹ�����                                        
//                                                                                                                                                                                                                           
//6������cramfs�ļ�ϵͳ                                                                                                                                                                                                      
//                                                                                                                                                                                                                           
//$sudo apt-get install cramfsprogs                                                                                                                                                                                          
//                                                                                                                                                                                                                           
//����REAL6410��cramfsϵͳԴ�룬                                                                                                                                                                                             
//                                                                                                                                                                                                                           
//$mkcramfs root_mkfs rootfs.cramfs                                                                                                                                                                                          
//                                                                                                                                                                                                                           
//�����ļ�ϵͳ��������                                                                                                                                                                                                       
//                                                                                                                                                                                                                           
//7���޸��ں���������                                                                                                                                                                                                        
//                                                                                                                                                                                                                           
//setenv bootargs noinitrd root=/dev/mtdblock0 console=ttySAC0 init=/linuxrc video=fb:AT070TN83                                                                                                                              
//                                                                                                                                                                                                                           
//8�����ȻҪ���һ���ں�ѡ����ú�֮��������أ�                                                                                                                                                                        
//                                                                                                                                                                                                                           
//9�����ˣ�REAL6410�Ѿ��ܴ�CRAMFS�ļ�ϵͳ�����ˣ�                                                                                                                                                                            
//                                                                                                                                                                                                                           
//
//===================================================================
//�ο�REAL��̳����ֲ����                                                                                                                                                                                                 
//                                                                                                         
// ���ȣ��޸�mach-real6410.c�ļ�                                                                         
//                                                                                                         
// 1�������ͷ�ļ���                                                                                         
                                                                                                         
#incldeu <linux/fb.h>                                                                                    
                                                                                                         
//#include <video/platform_lcd.h>                                                                          
                                                                                                         
//#include <mach/regs-fb.h>                                                                                
                                                                                                         
//#include <plat/fb.h>                                                                                     
                                                                                                         
//#include <mach/regs-gpio.h>                                                                              
                                                                                                         
//#include <mach/regs-modem.h>                                                                             
                                                                                                         
//������Ҫ��28�ں��е�regs-lcd.h���Ƶ�plat/                                                                
//                                                                                                         
// 2 �������豸��ʼ������                                                                                    
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
                                                                                                         
};//�������õ���ʾ���ߴ����                                                                             
                                                                                                         
                                                                                                         
                                                                                                         
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
                                                                                                         
��platform_device�м���                                                                                  
                                                                                                         
&s3c_device_fb,                                                                                          
                                                                                                         
��real6410_map_io�м���                                                                                  
                                                                                                         
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
                                                                                                         
��real6410_machine_init����ע�����                                                                      
                                                                                                         
s3c_fb_set_platdata(&real6410_lcd_pdata);                                                                
                                                                                                         
// 3���޸�/mach-s3c64xx/map.h������                                                                         
//                                                                                                         
                                                                                                         
                                                                                                         
#define S3C64XX_VA_HOSTIFA S3C_ADDR(0x00B00000)                                                          
                                                                                                         
#define S3C64XX_PA_HOSTIFA (0x74000000)                                                                  
                                                                                                         
#define S3C64XX_SZ_HOSTIFA SZ_1M                                                                         
                                                                                                         
                                                                                                         
                                                                                                         
#define S3C64XX_VA_HOSTIFB S3C_ADDR(0x00C00000)                                                          
                                                                                                         
#define S3C64XX_PA_HOSTIFB (0x74100000)                                                                  
                                                                                                         
#define S3C64XX_SZ_HOSTIFB SZ_1M                                                                         
                                                                                                         
                                                                                                         
                                                                                                         
// 4��  �޸�plat-samsung/dev-fb.c������                                                                       
//                                                                                                         
static struct s3c_platform_fb default_fb_data __initdata = {                                             
                                                                                                         
.hw_ver = 0x40,                                                                                          
                                                                                                         
.clk_name = "lcd",                                                                                       
                                                                                                         
.nr_wins = 5,                                                                                            
                                                                                                         
.default_win = CONFIG_FB_S3C,                                                                            
                                                                                                         
.swap = FB_SWAP_HWORD,                                                                                   
                                                                                                         
};                                                                                                       
                                                                                                         
//��ע��s3c_device_fb�е��豸���Ʊ���������е��������Ӧ�������������ᱻ����                              
//                                                                                                         
//                                                                                                         
//                                                                                                         
//�޸�plat/fb.h                                                                                            
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
                                                                                                         
//4����plat/map-base.h����                                                                                 
//                                                                                                         
//#define S3C_VA_LCD S3C_ADDR(0x01100000) // LCD                                                         
//                                                                                                         
//                                                                                                         
//                                                                                                         
//5����28�ں���/drivers/video/��samsung�ļ��п��������ӦĿ¼                                              
//                                                                                                         
//6���޸�video�е�Kconfig��                                                                                
//                                                                                                         
//����source ��drivers/video/samsung/Kconfig��������CONFIG_FB_S3C�ĳɱ�����֡�                            
//                                                                                                         
//7���޸�video�е�Makefile������                                                                           
//                                                                                                         
//:obj-$(CONFIG_FB_S3C) += SAMSUNG/                                                                        
//                                                                                                         
//8�������ں�                                                                                              
//                                                                                                         
//$make menuconfig                                                                                         
//                                                                                                         
//�� device drivers->Graphics support->Support for frame buffer devices��ѡ��                              
//                                                                                                         
//S3C Framebuffer Support                                                                                  
//                                                                                                         
//                                                                                                         
//                                                                                                         
//S3C Lcd Support Advanced options for S3C Framebuffer                                                     
//                                                                                                         
//Select BPP(Bits Per Pixel) (16 BPP) --->                                                                 
//                                                                                                         
//Number of Framebuffers��4��                                                                              
//                                                                                                         
//Enable Virtual Screen Enable Double Buffering                                                            
//                                                                                                         
//9��������кܶ���󣬴����ͷ�ļ���λ������                                                              
//                                                                                                         
//10���޸�samsung/Makefile������obj-$(CONFIG_FB_S3C_VIDEO) += ch7026.o���Լ�s3cfb_video.c�е�ch7026_init();
//                                                                                                         
//11��s3cfb_fimd4x.c�еĴ�����REAL��̳�ϵ��޸ģ�����1222�����Ρ�                                         
//                                                                                                         
//12��s3cfb.c�е��������ƺ�֮ǰ�豸������Ҫ��Ӧ                                                            
//                                                                                                         
//13���ں�����������                                                                                       
//                                                                                                         
//setenv bootargs noinitrd root=/dev/mtdblock0 console=ttySAC0 init=/linuxrc video=fb:AT070TN83            
//                                                                                                         
//��ƪ������Դ�� Linux������վ(www.linuxidc.com)  ԭ�����ӣ�http://www.linuxidc.com/Linux/2011-06/37703p2.htm
//
//
//===========================================================================     
//
// 1�޸�USB������KCONFIG��drivers/usb/Kconfig                                                                                                                                                                       
//                                                                                                                                                                                                                   
//�ҵ�config USB_ARCH_HAS_OHCI                                                                                                                                                                                       
//                                                                                                                                                                                                                   
//���efault y if ARCH_S3C64XX                                                                                                                                                                                       
//                                                                                                                                                                                                                   
// 2����drivers/usb/host/ohci-hcd.c                                                                                                                                                                                 
//                                                                                                                                                                                                                   
//��γ����Ƿ������                                                                                                                                                                                                 
//                                                                                                                                                                                                                   
//#if defined(CONFIG_ARCH_S3C2410) || defined(CONFIG_ARCH_S3C64XX)                                                                                                                                                   
//                                                                                                                                                                                                                   
//#include "ohci-s3c2410.c"                                                                                                                                                                                          
//                                                                                                                                                                                                                   
//#define PLATFORM_DRIVER ohci_hcd_s3c2410_driver                                                                                                                                                                    
//                                                                                                                                                                                                                   
//#endif                                                                                                                                                                                                             
//                                                                                                                                                                                                                   
//δ��������ϣ�����ohci-s3c2410.c �ļ��а���                                                                                                                                                                        
//                                                                                                                                                                                                                   
// 3�����/arch/arm/plat-samsung/dev-usb.c�е�USBplatform��Ϣ�Ƿ���ڣ�������豸���͵ڶ���������������Ƿ���ͬ��                                                                                                     
//                                                                                                                                                                                                                   
//��ע�⣺EXPORT_SYMBOL(s3c_device_ohci);                                                                                                                                                                            
//                                                                                                                                                                                                                   
// 4���޸�arch/arm/mach-s3c64xx/mach-real6410.c                                                                                                                                                                       
//                                                                                                                                                                                                                   
//����ͷ�ļ���                                                                                                                                                                                                       
//                                                                                                                                                                                                                   
//#include <plat/regs-usb-hsotg.h>                                                                                                                                                                                   
                                                                                                                                                                                                                   
//#include <plat/regs-usb-hsotg-phy.h>                                                                                                                                                                               
                                                                                                                                                                                                                   
//#include <linux/usb/ch9.h>                                                                                                                                                                                         
                                                                                                                                                                                                                   
//#include <plat/clock.h>                                                                                                                                                                                            
                                                                                                                                                                                                                   
//#include <plat/clock-clksrc.h>                                                                                                                                                                                     
                                                                                                                                                                                                                   
//#include <mach/regs-clock.h>                                                                                                                                                                                       
                                                                                                                                                                                                                   
//����ע��#include <plat/clock.h>��Ҫ����#include <plat/clock-clksrc.h>֮ǰ����Ȼ��clksrc�����л��Ҳ���clk������                                                                                                     
//                                                                                                                                                                                                                   
//��platform_device *real6410_devices[] __initdata�����                                                                                                                                                             
//                                                                                                                                                                                                                   
//&s3c_device_ohci                                                                                                                                                                                                   
//                                                                                                                                                                                                                   
//5�����ʱ�ӳ�ʼ����������28�ں��и��ƹ���                                                                                                                                                                          
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
                                                                                                                                                                                                                   
|(0<<20), S3C_CLK_DIV1);//������Ҫ�޸�1<<20����Ϊ0<<20���鿴�ֲ�����¿�Ϊʲô                                                                                                                                     
                                                                                                                                                                                                                   
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
                                                                                                                                                                                                                   
//������real6410_machine_init();�е���                                                                                                                                                                               
//                                                                                                                                                                                                                   
//#ifdef CONFIG_USB_OHCI_HCD                                                                                                                                                                                         
//usb_host_clk_en(0);                                                                                                                                                                                                
//#endif                                                                                                                                                                                                             
////�˲���usbʹ��ԴѡΪEPLL                                                                                                                                                                                          
//                                                                                                                                                                                                                   
// 6����28�ں��е�/arch/arm/plat-s3c64xx/include/plat/regs-clock.h�е����ݸ��Ƶ�                                                                                                                                      
//                                                                                                                                                                                                                   
//39�ں��е�plat/regs-clock.h�У�����ǶԱ�һ�������ļ���Ȼ��������ȱ�ٵġ�                                                                                                                                        
//                                                                                                                                                                                                                   
// 7���޸�UB00T�е�CPUʱ�ӳ�ʼ������                                                                                                                                                                                  
//                                                                                                                                                                                                                   
//��/home/kevinjz/ELinux/REAL6410/s3c-u-boot-1.1.6-Real6410/board/samsung/smdk6410/lowlevel_init.S������#EPLL_CON0_OFFSET��                                                                                          
//                                                                                                                                                                                                                   
//��                                                                                                                                                                                                                 
//                                                                                                                                                                                                                   
//ldr r1, =0x80200203��Ϊ                                                                                                                                                                                            
//                                                                                                                                                                                                                   
//ldr r1, =0x80200103                                                                                                                                                                                                
//                                                                                                                                                                                                                   
////�˲���EPLLʹ���޸�Ϊ48M��USB�豸Ҫ��48MHZ                                                                                                                                                                        
//                                                                                                                                                                                                                   
// 8�������ں�ѡ��                                                                                                                                                                                                    
//                                                                                                                                                                                                                   
//$make menuconfig                                                                                                                                                                                                   
//                                                                                                                                                                                                                   
//ѡ��device drivers->SCSI device support                                                                                                                                                                            
//                                                                                                                                                                                                                   
//ѡ��device drivers->HID Devices->USB Human Interface Device (full HID) support                                                                                                                                     
//                                                                                                                                                                                                                   
//ѡ��device drivers->USB support :                                                                                                                                                                                  
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
//����ȷ����file systemsѡ�����USB�豸���õ��ļ�ϵͳ��NTSF��VFAT��FAT��MSDOS��                                                                                                                                      
//                                                                                                                                                                                                                   
// 9���������أ�������                                                                                                                                                                                                
//                                                                                                                                                                                                                   
//mount -t ntfs /dev/sda1 /mnt/udisk                                                                                                                                                                                 
//                                                                                                                                                                                                                   
//<!-- @page { margin: 2cm } P { margin-bottom: 0.21cm } -->                                                                                                                                                         
//                                                                                                                                                                                                                   
// 10��USB OTG����                                                                                                                                                                                                    
//                                                                                                                                                                                                                   
//�ؼ��Ǽǵ���arch/arm/mach-s3c64xx/cpu.c�����USBOTG��PA-VAת����ĳ�ʼ����Ϣ��˵���˾��ǽ��Լ���map-base.h�ж������������VA(�����ַ)����map.h�ж������������PA�������ַ����ϵ��������������Ҳû�á�      
//                                                                                                                                                                                                                   
//������ֻҪ��real28�ں�drivers/usb/host/�е�s3c-otg�ļ��и��Ƶ�39�ں���Ӧλ�ã�Ȼ���޸�kconfig��makefile���ļ���������ļ�������ںˣ����ݴ�����ʾ�޸ļ��ɣ����󶼲����ӣ���Ҫ�����Ҳ����ļ�����������ʲô���������
//                                                                                                                                                                                                                   
//��ƪ������Դ�� Linux������վ(www.linuxidc.com)  ԭ�����ӣ�http://www.linuxidc.com/Linux/2011-06/37703p3.htm                                                                                                        