linux2.6��������ע��˳��ѧϰ��ᣨNAND���������ӣ�2010��02��03�� ������ 15:48    �ӽ��쿪ʼ����¼���ڿ�����ѧϰ�е��ĵã������Ժ�ع˺Ͳ�ȱ��©�������ʼ����6410�ϵ�ANDROID��ֲ�����ڰ�֮ǰ����һЩ������¼������
������˵˵LINUX�ں���������ע���˳�򣬱����Ժ������ı�д�Լ�����ķ�������2.6.29��Ϊ�ںˣ�NAND������Ϊ˵������

LINUX�ں��У���������ʹ��platform_device���������ýṹ�嶨����\include\linux\platform_device.h�С�

struct platform_device {
const char    * name;
int        id;
struct device    dev;
u32        num_resources;
struct resource    * resource;
}; 

�ýṹһ����Ҫ��Ԫ����resource����Ԫ�ش�������Ϊ��Ҫ���豸��Դ��Ϣ��������\include\linux\ioport.h�У�
struct resource { //name,start,end,flags�Ƚϳ���
const char *name; 
unsigned long start, end;
unsigned long flags;
struct resource *parent, *sibling, *child;
};

���磺������Ҫ����һ��NAND��������/arch/arm/mach-s3c6410/mach-smdk6410.c�У��������������һ�δ��룺
static struct resource s3c_nand_resource[] = {
[0] = {
.start = S3C24XX_PA_NAND,
.end   = S3C24XX_PA_NAND + S3C24XX_SZ_NAND - 1,
.flags = IORESOURCE_MEM,
},
/* �����в�û����һ�ֻ��Ϊ��˵��*/
[1] ={
.start = START,
.end = END,
.flags = IORESOURCE_IRQ,
},
};

���ﶨ����һ��resource����������һ��NAND�豸����Դ����1�����������usb host�豸��ռ�õ����ߵ�ַ��Χ��IORESOURCE_MEM��ʾ��1�����������ڴ����͵���Դ��Ϣ������2��IORESOURCE_IRQ��ʾ��2����������һ���ж����͵���Դ��Ϣ��
���Ҫ�ں��������������Ϣ����ô���õ����漸��������ͬ��������platform_device.h�У�

struct resource * platform_get_resource(struct platform_device *dev, unsigned int type, unsigned int num); //���ݲ���type����IORESOURCE_MEM������ȡ��Դ��numΪresource�еĵڼ���

struct int platform_get_irq(struct platform_device *dev, unsigned int num); //��ȡ��Դ�е��жϺ�

struct resource * platform_get_resource_byname(struct platform_device *dev, unsigned int type, char *name); //���ݲ���name��ָ�������ƣ�����ȡָ������Դ��ʹ�øú�����resource��ÿһ����Ҫ���岻ͬ��name

int platform_get_irq_byname(struct platform_device *dev, char *name); //���ݲ���name��ָ�������ƣ�����ȡ��Դ�е��жϺš�ʹ�øú�����resource��ÿһ����Ҫ���岻ͬ��name


��������Ҫ����platform_device��ͬ������mach-s3c6410.c�ж��壺
struct platform_device s3c_device_nand = {
.name          = "s3c-nand", //ע��ʱ���豸�����֣�һ��Ҫ�ͺ����������ʱ���������ͬ
.id          = -1, //ע��ʱ���豸��id��
.num_resources      = ARRAY_SIZE(s3c_nand_resource),
.resource      = s3c_nand_resource, //֮ǰ�����resource
.dev = {
.platform_data = &s3c_nand_mtd_part_info
}
};
����s3c_nand_mtd_part_info��nand�ķ�����Ϣ���ں���������л��ᵽ��

������ɺ�ע��platform_device��
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

�ں���������������Ĵ��룬�����豸��ע���ˣ�
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

�豸ע����ɺ���Ҫ�����������м��ء��ҵ�NAND��������/drivers/mtd/nand/s3c_nand.c�С�
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
ע�⣺�����name�����֮ǰplatform_device�ж����nameͬ��������platform_driver_register()ע��ʱ���������ע�������platform_device�е�name�͵�ǰע���platform_driver��driver.name���бȽϣ�ֻ���ҵ���ͬ�����Ƶ�platfomr_device����ע��ɹ�����֮ǰ��Ϊ��֪������������˲���ʱ�䡣

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

ͨ�����ϴ��룬�豸����register��unregister�ˡ���ע��ɹ�ʱ�����platform_driver�ṹԪ��probe����ָ�룬�������s3c_nand_probe�������ĳ�ʼ���ȶ�����prob��������ɵġ�
 
