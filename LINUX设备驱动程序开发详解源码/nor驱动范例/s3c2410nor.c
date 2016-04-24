/*
�� Linux ϵͳ�У�ʵ������� cfi��jedec �Ƚӿ�
��ͨ�� NOR ��������һ�������ֱ������ mtd_info
�ĳ�Ա��������ʹ�� NOR ��оƬ���������ʮ�ּ�
���� ֻ��Ҫ���������ڴ�ӳ������ṹ�� map_info
��ʹ��ָ���ӿ����͵��� do_map_ probe()�� 
NOR Flash�����ĺ����Ƕ��� map_info�ṹ�壬��
ָ����NOR Flash�Ļ�ַ�� λ����С����Ϣ�Լ� Flash
�Ķ�д�������ýṹ����� NOR  Flash ����������Ϊ
�ؼ������� NOR  Flash �����Ĵ��뱾���Ͽ��Ա�����
�Ǹ��� map_info ̽��оƬ�Ĺ��̣��䶨��������嵥
19.7��ʾ�� 

NOR Flash������Linux�е�ʵ�ַǳ��򵥣���ͼ 19.4 ��ʾ����Ҫ�Ĺ������¡� 
��1������map_info��ʵ������ʼ�����еĳ�Ա������Ŀ�������Ϊ name��size��
bankwidth��phys��ֵ��
��2�����FlashҪ����������mtd_partition���飬��ʵ�ʵ�·����Flash������Ϣ
��¼�����С� 
��3���� map_info ��̽��Ľӿ����ͣ���"cfi_probe"��"jedec_probe"�ȣ�Ϊ������
��do_map_ probe()��̽��Flash�õ�mtd_info�� 
��4����ģ���ʼ��ʱ�� mtd_info Ϊ�������� add_mtd_device()���� mtd_info��
mtd_partition���鼰������Ϊ��������add_mtd_partitions()ע���豸���������Ȼ������֮
ǰ���Ե���parse_mtd_partitions()�鿴Flash ���Ƿ����з�����Ϣ�������鿴���ķ�����Ϣ
ͨ��add_mtd_partitions()ע�ᡣ 
��5����ģ��ж��ʱ���õ�4�к����ġ���������ɾ���豸������� 
*/


#define WINDOW_ADDR 0x01000000      /* NOR FLASH�����ַ */
#define WINDOW_SIZE 0x800000         /* NOR FLASH��С */
#define BUSWIDTH    2
/* ̽��Ľӿ����ͣ�������"cfi_probe", "jedec_probe", "map_rom", NULL }; */
#define PROBETYPES { "cfi_probe", NULL }

#define MSG_PREFIX "S3C2410-NOR:"   /* prefix for our printk()'s */
#define MTDID      "s3c2410-nor"    /* for mtdparts= partitioning */

static struct mtd_info *mymtd;

struct map_info s3c2410nor_map =  // map_info
{
  .name = "NOR flash on S3C2410",
  .size = WINDOW_SIZE,
  .bankwidth = BUSWIDTH,
  .phys = WINDOW_ADDR,
};

#ifdef CONFIG_MTD_PARTITIONS
  /* MTD������Ϣ  */
  static struct mtd_partition static_partitions[] =
  {
    {
      .name = "BootLoader", .size = 0x040000, .offset = 0x0  //bootloader��ŵ�����
    } ,
    {
      .name = "Kernel", .size = 0x0100000, .offset = 0x40000 //�ں�ӳ���ŵ�����
    }
    ,
    {
      .name = "RamDisk", .size = 0x400000, .offset = 0x140000 //ramdisk��ŵ�����
    }
    ,
    {
      .name = "cramfs(2MB)", .size = 0x200000, .offset = 0x540000 //ֻ����cramfs����
    }
    ,
    {
      .name = "jffs2(0.75MB)", .size = 0xc0000, .offset = 0x740000 //�ɶ�д��jffs2����
    }
    ,
  };
#endif

static int mtd_parts_nb = 0;
static struct mtd_partition *mtd_parts = 0;

int __init init_s3c2410nor(void)
{
  static const char *rom_probe_types[] = PROBETYPES;
  const char **type;
  const char *part_type = 0;

  printk(KERN_NOTICE MSG_PREFIX "0x%08x at 0x%08x\n", WINDOW_SIZE, WINDOW_ADDR);
  s3c2410nor_map.virt = ioremap(WINDOW_ADDR, WINDOW_SIZE);//����->�����ַ

  if (!s3c2410nor_map.virt)
  {
    printk(MSG_PREFIX "failed to ioremap\n");
    return  - EIO;
  }

  simple_map_init(&s3c2410nor_map);

  mymtd = 0;
  type = rom_probe_types;
  for (; !mymtd &&  *type; type++)
  {
    mymtd = do_map_probe(*type, &s3c2410nor_map);//̽��NOR FLASH
  }
  if (mymtd)
  {
    mymtd->owner = THIS_MODULE;

    #ifdef CONFIG_MTD_PARTITIONS
      mtd_parts_nb = parse_mtd_partitions(mymtd, NULL, &mtd_parts, MTDID);//̽�������Ϣ
      if (mtd_parts_nb > 0)
        part_type = "detected";

      if (mtd_parts_nb == 0) //δ̽�⵽��ʹ�����鶨��ķ�����Ϣ
      {
        mtd_parts = static_partitions;
        mtd_parts_nb = ARRAY_SIZE(static_partitions);
        part_type = "static";
      }
    #endif
    add_mtd_device(mymtd);
    if (mtd_parts_nb == 0)
      printk(KERN_NOTICE MSG_PREFIX "no partition info available\n");
    else
    {
      printk(KERN_NOTICE MSG_PREFIX "using %s partition definition\n",
        part_type);
      add_mtd_partitions(mymtd, mtd_parts, mtd_parts_nb);//��ӷ�����Ϣ
    }
    return 0;
  }

  iounmap((void*)s3c2410nor_map.virt);
  return  - ENXIO;
}

static void __exit cleanup_s3c2410nor(void)
{
  if (mymtd)
  {
    del_mtd_partitions(mymtd);  //ɾ������
    del_mtd_device(mymtd);   //ɾ���豸
    map_destroy(mymtd);     
  }
  if (s3c2410nor_map.virt)
  {
    iounmap((void*)s3c2410nor_map.virt);
    s3c2410nor_map.virt = 0;
  }
}
