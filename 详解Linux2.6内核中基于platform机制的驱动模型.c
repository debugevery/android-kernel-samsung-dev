���Linux2.6�ں��л���platform���Ƶ�����ģ��(2010-10-22 14:27:45)ת�ب���ǩ�� ��̸ ���ࣺ 2010.3~  
ժҪ ������Linux 2.6.25 �ں�Ϊ���������˻���platform���ߵ�����ģ�͡����Ƚ�����Platform���ߵĻ���������Ž�����platform device��platform driver�Ķ���ͼ��ع��̣��������������device ��driver��������ϵ���ڴ˹����������������˼�롣�����ARM S3C2440��I2C������Ϊ�������˻���platform���ߵ������������̡�

���ؼ��֡�platform_bus, platform_device, resource , platform_driver, file_operations

Ŀ¼

1    ��νplatform bus��    2
2    device��platform_device    3
3    device_register��platform_device_register    5
4    device_driver��platform driver    8
5    driver_register ��platform_driver_register    10
6    bus��device��driver����֮��Ĺ�ϵ    17
7    ��Щ������plarform������    18
8    ����platform���ߵ�������������    18
8.1    ��ʼ��platform_bus    19
8.2    ����platform_device    22
8.3    ע��platform_device    22
8.4    ����platform_driver    28
8.5    ע��platform_driver    29
8.6    �����豸    32

1    ��νplatform bus��
Linuxϵͳ����ಿ�ֶ��豸��������ӵĲ�������Ȥ������������Ҫ֪����Щ���͵��豸�ǿ���ʹ�õġ��豸ģ���ṩ��һ�ֻ��������豸���з��࣬�ڸ��ߵĹ��ܲ�����������Щ�豸����ʹ����Щ�豸���û��ռ�ɼ�����˴�2.6�ں˿�ʼ�������豸ģ�͡�

�����Ǵ�������һ�������豸֮���ͨ�������豸ģ����, ���е��豸��ͨ���������������߿����໥���롣�豸ģ��չʾ�����ߺ����������Ƶ��豸֮���ʵ�����ӡ�

Platform������2.6 kernel����������һ���������ߣ���Ҫ��������CPU��Ƭ����Դ�����и��õ���ֲ�ԣ������2.6 kernel�У��ܶ���������platform��д�ˡ�

platform_bus_type�Ķ�������:
http://lxr.linux.no/#linux+v2.6.25/drivers/base/platform.c#L609
609struct bus_type platform_bus_type = {
 610        .name           = "platform",
 611        .dev_attrs      = platform_dev_attrs,
 612        .match          = platform_match,
 613        .uevent         = platform_uevent,
 614        .suspend        = platform_suspend,
 615        .suspend_late   = platform_suspend_late,
 616        .resume_early   = platform_resume_early,
 617        .resume         = platform_resume,
 618};
 619//EXPORT_SYMBOL_GPL(platform_bus_type);

http://lxr.linux.no/#linux+v2.6.25/include/linux/device.h#L55
  55struct bus_type {
  56        const char              *name;
  57        struct bus_attribute    *bus_attrs;
  58        struct device_attribute *dev_attrs;
  59        struct driver_attribute *drv_attrs;
  60
  61        int (*match)(struct device *dev, struct device_driver *drv);
  62        int (*uevent)(struct device *dev, struct kobj_uevent_env *env);
  63        int (*probe)(struct device *dev);
  64        int (*remove)(struct device *dev);
  65        void (*shutdown)(struct device *dev);
  66
  67        int (*suspend)(struct device *dev, pm_message_t state);
  68        int (*suspend_late)(struct device *dev, pm_message_t state);
  69        int (*resume_early)(struct device *dev);
  70        int (*resume)(struct device *dev);
  71
  72        struct bus_type_private *p;
  73};

����������"platform"����ֻ��bus_type��һ�֣����������ߵ����ԣ�ͬʱplatform_bus_type������ز����������������ֹ��ƥ�估hotplug�¼��ȡ�

����bus����ϵdriver��device���м���Ŧ��Deviceͨ��������bus�ҵ�driver����match������������ƥ�䡣

 
Bus��driver��devices�����ӹ�ϵ

2    device��platform_device
Plarform device����һ����������driver binding����ע��driver��ʱ������driver��Ŀ���豸��busλ�ã�������̳�Ϊdriver binding��������IRQ�Լ���ַ�ռ����ԴҲҪ���� ��

platform_device�ṹ�����������豸�����ơ���Դ��Ϣ�ȡ��ýṹ��������http://lxr.linux.no/#linux+v2.6.25/include/linux/platform_device.h#L16�У�����ԭ�����£�

  16struct platform_device {
  17        const char      * name; //����ƽ̨�豸�����ƣ��˴��豸������Ӧ����Ӧ������������һ��

  18        int             id;
  19        struct device   dev;
  20        u32             num_resources;
  21        struct resource * resource;  //����ƽ̨�豸����Դ
  22};

������ṹ���װ��struct device��struct resource����֪��platform_device��device������������һ�������device��

��������һ��platform_device�ṹ��������Ҫ��һ����Աstruct resource * resource��struct resource��������http://lxr.linux.no/#linux+v2.6.25/include/linux/ioport.h#L18�У�����ԭ�����£�
  14
  18struct resource {
  19        resource_size_t start;  //������Դ����ʼ��ַ
  20        resource_size_t end;  //������Դ�Ľ�����ַ
  21        const char *name; //������Դ������
  22        unsigned long flags; ������Դ�����ͣ�����MEM��IO��IRQ��DMA����
  23        struct resource *parent, *sibling, *child;
  24};

����ṹ��ʾ�豸��ӵ�е���Դ����I/O�˿ڡ�I/Oӳ���ڴ桢�жϼ�DMA�ȡ�����ĵ�ַָ���������ַ��

���⻹��Ҫע��platform_device�е�device�ṹ������ϸ�������豸���������Ϊ�����豸�Ļ��࣬�������£�
http://lxr.linux.no/#linux+v2.6.25/include/linux/device.h#L422
422struct device {
 423        struct klist            klist_children;
 424        struct klist_node       knode_parent;  
 425        struct klist_node       knode_driver;
 426        struct klist_node       knode_bus;
 427        struct device           *parent;
 428
 429        struct kobject kobj;
 430        char    bus_id[BUS_ID_SIZE];   
 431        struct device_type      *type;
 432        unsigned                is_registered:1;
 433        unsigned                uevent_suppress:1;
 434
 435        struct semaphore        sem;   
 438
 439        struct bus_type *bus;          
 440        struct device_driver *driver;  
 442        void            *driver_data;  
 443        void            *platform_data;
 445        struct dev_pm_info      power;
 446
 447#ifdef CONFIG_NUMA
 448        int             numa_node;     
 449#endif
 450        u64             *dma_mask;     
 451        u64             coherent_dma_mask;
 456
 457        struct device_dma_parameters *dma_parms;
 458
 459        struct list_head        dma_pools;     
 460
 461        struct dma_coherent_mem *dma_mem;
 463       
 464        struct dev_archdata     archdata;
 465
 466        spinlock_t              devres_lock;
 467        struct list_head        devres_head;
 468
 469       
 470        struct list_head        node;
 471        struct class            *class;
 472        dev_t                   devt;  
 473        struct attribute_group  **groups;      
 474
 475        void    (*release)(struct device *dev);
 476};
 477

3    device_register��platform_device_register

http://lxr.linux.no/#linux+v2.6.25/drivers/base/core.c#L881
 870
 881int device_register(struct device *dev)
 882{
 883        device_initialize(dev);
 884        return device_add(dev);
 885}
��ʼ��һ���豸��Ȼ����뵽ϵͳ�С�

http://lxr.linux.no/#linux+v2.6.25/drivers/base/platform.c#L325
316
 320int platform_device_register(struct platform_device *pdev)
 321{
 322        device_initialize(&pdev->dev);
 323        return platform_device_add(pdev);
 324}
 325//EXPORT_SYMBOL_GPL(platform_device_register);

���ǿ���ע��һ��platform device��Ϊ�������֣���ʼ�����platform_device��Ȼ�󽫴�platform_device��ӵ�platform�����С��������platform_device�����Ǿ�̬��ȫ���豸��

����һ�ֻ��ƾ��Ƕ�̬����platform_device_allocһ��platform_device�豸��Ȼ��ͨ��platform_device_add_resources��platform_device_add_data����������Դ�����ԡ�

������һ��platform_device�����ն���ͨ��platform_device_add��ᵽplatform�����ϡ�

229
 236int platform_device_add(struct platform_device *pdev)
 237{
 238        int i, ret = 0;
 239
 240        if (!pdev)
 241                return -EINVAL;
 242
��ʼ���豸��parentΪplatform_bus����ʼ������������Ϊplatform_bus_type��
 243        if (!pdev->dev.parent)
 244                pdev->dev.parent = &platform_bus;
 245
 246        pdev->dev.bus = &platform_bus_type;
 247

 248        if (pdev->id != -1)
 249                snprintf(pdev->dev.bus_id, BUS_ID_SIZE, "%s.%d", pdev->name,
 250                         pdev->id);
 251        else
 252                strlcpy(pdev->dev.bus_id, pdev->name, BUS_ID_SIZE);
 253
�����豸struct device ��bus_id��Ա����������ط������Ժ���Ҫ�õ�����ġ�
 254        for (i = 0; i < pdev->num_resources; i++) {
 255                struct resource *p, *r = &pdev->resource[i];
 256
 257                if (r->name == NULL)
 258                        r->name = pdev->dev.bus_id;
 259
 260                p = r->parent;
 261                if (!p) {
 262                        if (r->flags & IORESOURCE_MEM)
 263                                p = &iomem_resource;
 264                        else if (r->flags & IORESOURCE_IO)
 265                                p = &ioport_resource;
 266                }
//resources��Ϊ����IORESOURCE_MEM��IORESOURCE_IO
 //CPU������IO�˿������ַ�ı�ַ��ʽ�����֣�I/Oӳ�䷽ʽ���ڴ�ӳ�䷽ʽ
 267
 268                if (p && insert_resource(p, r)) {
 269                        printk(KERN_ERR
 270                               "%s: failed to claim resource %d\n",
 271                               pdev->dev.bus_id, i);
 272                        ret = -EBUSY;
 273                        goto failed;
 274                }
 275        }
 276
 277        pr_debug("Registering platform device '%s'. Parent at %s\n",
 278                 pdev->dev.bus_id, pdev->dev.parent->bus_id);
 279
 280        ret = device_add(&pdev->dev);
 281        if (ret == 0)
 282                return ret;
 283
 284 failed:
 285        while (--i >= 0)
 286                if (pdev->resource[i].flags & (IORESOURCE_MEM|IORESOURCE_IO))
 287                        release_resource(&pdev->resource[i]);
 288        return ret;
 289}
 290//EXPORT_SYMBOL_GPL(platform_device_add);

��platform_device_register��platform_device_add��ʵ�ֿ�֪��device_register()��platform_device_register()�������ȳ�ʼ���豸
�������ڵڶ�������ʵplatform_device_add()����device_add()������Ҫ��ע��resources��Ȼ���豸�ҽӵ��ض���platform���ߡ�

4    device_driver��platform driver
Platform device��һ��device�Լ��ǲ���������ģ�Ҫ����Ϊ�������飬�Ǿ���platform driver��platform driver��ѭlinuxϵͳ��driver model������device��discovery/enumerate������driver�Լ���ɵĶ�������ϵͳ��driverע�������ɡ�driver��д��ԱֻҪ��ע���������ݽṹ��ʼ��������ע��driver��kernel API�Ϳ����ˡ�

����������platform_driver�ṹ���ԭ�Ͷ��壬��http://lxr.linux.no/#linux+v2.6.25/include/linux/platform_device.h#L48�У��������£�
48 struct platform_driver {
  49        int (*probe)(struct platform_device *);
  50        int (*remove)(struct platform_device *);
  51        void (*shutdown)(struct platform_device *);
  52        int (*suspend)(struct platform_device *, pm_message_t state);
  53        int (*suspend_late)(struct platform_device *, pm_message_t state);
  54        int (*resume_early)(struct platform_device *);
  55        int (*resume)(struct platform_device *);
  56        struct device_driver driver;
  57};

�ɼ������������豸�����ļ������ܺ�����ͬʱ������һ��device_driver�ṹ��˵��device_driver��platform_driver�Ļ��ࡣ������������Ҫ��ʼ��������������濴һ����������Ķ��壬λ��http://lxr.linux.no/#linux+v2.6.25/include/linux/device.h#L121�У�
 
121struct device_driver {
 122        const char              *name;
 123        struct bus_type         *bus;
 124
 125        struct module           *owner;
 126        const char              *mod_name;     
 127
 128        int (*probe) (struct device *dev);
 129        int (*remove) (struct device *dev);
 130        void (*shutdown) (struct device *dev);
 131        int (*suspend) (struct device *dev, pm_message_t state);
 132        int (*resume) (struct device *dev);
 133        struct attribute_group **groups;
 134
 135        struct driver_private *p;
 136};

device_driver�ṩ��һЩ�����ӿڣ����䲢û��ʵ�֣��൱��һЩ�麯������������platform_driver�������أ����ۺ������͵�driver���ǻ���device_driver���������ģ�����ĸ��ֲ������ǻ���ͳһ�Ļ���ӿڵģ�������ʵ��������������ơ�

��Ҫע��������������name��owner����������Ҫ��Ϊ�˺���ص�platform_device����������owner��������˵��ģ��������ߣ�����������һ���ʼ��ΪTHIS_MODULE��

device_driver�ṹ��Ҳ��һ��name������platform_driver��������������֪�����豸�������豸������Ϊ˭������أ���Ȼ���豸�ˡ��ں�����ͨ�����һ������Ϊ���������ҵ���Դ���� platform_device�е�resource��

5    driver_register ��platform_driver_register

�ں��ṩ��platform_driver�ṹ���ע�ắ��Ϊplatform_driver_register��������ԭ�Ͷ�����http://lxr.linux.no/#linux+v2.6.25/drivers/base/platform.c#L458�ļ��У�����ʵ�ִ������£�
439
 443int platform_driver_register(struct platform_driver *drv)
 444{
 445        drv->driver.bus = &platform_bus_type;
  

 446        if (drv->probe)
 447                drv->driver.probe = platform_drv_probe;
 //��really_probe�����У��ص���platform_drv_probe����

448        if (drv->remove)
 449                drv->driver.remove = platform_drv_remove;
 450        if (drv->shutdown)
 451                drv->driver.shutdown = platform_drv_shutdown;
 452        if (drv->suspend)
 453                drv->driver.suspend = platform_drv_suspend;
 454        if (drv->resume)
 455                drv->driver.resume = platform_drv_resume;
 456        return driver_register(&drv->driver);
 457}
 458//EXPORT_SYMBOL_GPL(platform_driver_register);

��Ҫ�������platform_drv_XXX�ŵ��ˣ�������ʵ�ܼ򵥣����ǽ�struct deviceת��Ϊstruct platform_device��struct platform_driver��Ȼ�����platform_driver�е���Ӧ�ӿں�������Ϊʲô��ֱ�ӵ���platform_drv_XXX�Ƚӿ��أ������Linux�ں��������������˼�롣

device_driver�ṩ��һЩ�����ӿڣ����䲢û��ʵ�֣��൱��һЩ�麯������������platform_driver�������أ����ۺ������͵�driver���ǻ���device_driver���������ģ�device_driver�о���ĸ��ֲ������ǻ���ͳһ�Ļ���ӿڵģ�������ʵ��������������ơ�

���ļ�http://lxr.linux.no/#linux+v2.6.25/drivers/base/driver.c#L234�У�ʵ����driver_register()������

209
 217int driver_register(struct device_driver *drv)
 218{
 219        int ret;
 220
//������ߵķ������豸�Լ��ķ���ͬʱ���ڣ�����ӡ�澯��Ϣ������platform bus����û��probe�Ƚӿ�
 221        if ((drv->bus->probe && drv->probe) ||
 222            (drv->bus->remove && drv->remove) ||
 223            (drv->bus->shutdown && drv->shutdown))
 224                printk(KERN_WARNING "Driver '%s' needs updating - please use "
 225                        "bus_type methods\n", drv->name);
 226        ret = bus_add_driver(drv);
 227        if (ret)
 228                return ret;
 229        ret = driver_add_groups(drv, drv->groups);
 230        if (ret)
 231                bus_remove_driver(drv);
 232        return ret;
 233}
 234//EXPORT_SYMBOL_GPL(driver_register);

226        ����Ҫ�������ҽӵ������ϣ�ͨ�������������豸��

644
 648int bus_add_driver(struct device_driver *drv)
 649{
 650        struct bus_type *bus;
 651        struct driver_private *priv;
 652        int error = 0;
 653
 654        bus = bus_get(drv->bus);
 655        if (!bus)
 656                return -EINVAL;
 657
 658        pr_debug("bus: '%s': add driver %s\n", bus->name, drv->name);
 659
 660        priv = kzalloc(sizeof(*priv), GFP_KERNEL);
 661        if (!priv) {
 662                error = -ENOMEM;
 663                goto out_put_bus;
 664        }
 665        klist_init(&priv->klist_devices, NULL, NULL);
 666        priv->driver = drv;
 667        drv->p = priv;
 668        priv->kobj.kset = bus->p->drivers_kset;
 669        error = kobject_init_and_add(&priv->kobj, &driver_ktype, NULL,
 670                                     "%s", drv->name);
 671        if (error)
 672                goto out_unregister;
 673
 674        if (drv->bus->p->drivers_autoprobe) {
 675                error = driver_attach(drv);
 676                if (error)
 677                        goto out_unregister;
 678        }
 679        klist_add_tail(&priv->knode_bus, &bus->p->klist_drivers);
 680        module_add_driver(drv->owner, drv);
 681
 682        error = driver_create_file(drv, &driver_attr_uevent);
 683        if (error) {
 684                printk(KERN_ERR "%s: uevent attr (%s) failed\n",
 685                        __FUNCTION__, drv->name);
 686        }
 687        error = driver_add_attrs(bus, drv);
 688        if (error) {
 689               
 690                printk(KERN_ERR "%s: driver_add_attrs(%s) failed\n",
 691                        __FUNCTION__, drv->name);
 692        }
 693        error = add_bind_files(drv);
 694        if (error) {
 695               
 696                printk(KERN_ERR "%s: add_bind_files(%s) failed\n",
 697                        __FUNCTION__, drv->name);
 698        }
 699
 700        kobject_uevent(&priv->kobj, KOBJ_ADD);
 701        return error;
 702out_unregister:
 703        kobject_put(&priv->kobj);
 704out_put_bus:
 705        bus_put(bus);
 706        return error;
 707}

��������ϵ�driver���Զ�probe�Ļ����򽫸������ϵ�driver��device��������

http://lxr.linux.no/#linux+v2.6.25/drivers/base/dd.c#L285
272
 281int driver_attach(struct device_driver *drv)
 282{
 283        return bus_for_each_dev(drv->bus, NULL, drv, __driver_attach);
 284}
 285//EXPORT_SYMBOL_GPL(driver_attach);

ɨ��������ϵ�ÿһ���豸������ǰdriver�������ϵ��豸����match�����ƥ��ɹ������豸��driver��������

246static int __driver_attach(struct device *dev, void *data)
 247{
 248        struct device_driver *drv = data;
 249
 250       
 259
 260        if (dev->parent)       
 261                down(&dev->parent->sem);
 262        down(&dev->sem);
 263        if (!dev->driver)
 264                driver_probe_device(drv, dev);
 265        up(&dev->sem);
 266        if (dev->parent)
 267                up(&dev->parent->sem);
 268
 269        return 0;
 270}

263��������豸��û��ƥ���driver������ƥ�䡣

http://lxr.linux.no/#linux+v2.6.25/drivers/base/dd.c#L187
170
 187int driver_probe_device(struct device_driver *drv, struct device *dev)
 188{
 189        int ret = 0;
 190
 191        if (!device_is_registered(dev))
 192                return -ENODEV;
 193        if (drv->bus->match && !drv->bus->match(dev, drv))
 194                goto done;
 195
 196        pr_debug("bus: '%s': %s: matched device %s with driver %s\n",
 197                 drv->bus->name, __FUNCTION__, dev->bus_id, drv->name);
 198
 199        ret = really_probe(dev, drv);
 200
 201done:
 202        return ret;
 203}

193������������ϵ��豸��Ҫ����ƥ�䣬����֤�Ƿ�ƥ�䡣����platform���ߣ���ƥ��������£�
http://lxr.linux.no/#linux+v2.6.25/drivers/base/platform.c#L555
542
 555static int platform_match(struct device *dev, struct device_driver *drv)
 556{
 557        struct platform_device *pdev;
 558
 559        pdev = container_of(dev, struct platform_device, dev);
 560        return (strncmp(pdev->name, drv->name, BUS_ID_SIZE) == 0);
 561}

560���򵥵Ľ����ַ���ƥ�䣬��Ҳ������ǿ��platform_device��platform_driver�е�name������Ҫһ�µ�ԭ��

ƥ��ɹ��������probe�ӿڡ�
http://lxr.linux.no/#linux+v2.6.25/drivers/base/dd.c#L101
  98static atomic_t probe_count = ATOMIC_INIT(0);
  99static DECLARE_WAIT_QUEUE_HEAD(probe_waitqueue);
 100
 101static int really_probe(struct device *dev, struct device_driver *drv)
 102{
 103        int ret = 0;
 104
 105        atomic_inc(&probe_count);
 106        pr_debug("bus: '%s': %s: probing driver %s with device %s\n",
 107                 drv->bus->name, __FUNCTION__, drv->name, dev->bus_id);
 108        WARN_ON(!list_empty(&dev->devres_head));
 109
 110        dev->driver = drv;
 111        if (driver_sysfs_add(dev)) {
 112                printk(KERN_ERR "%s: driver_sysfs_add(%s) failed\n",
 113                        __FUNCTION__, dev->bus_id);
 114                goto probe_failed;
 115        }
 116
 117        if (dev->bus->probe) {
 118                ret = dev->bus->probe(dev);
 119                if (ret)
 120                        goto probe_failed;
 121        } else if (drv->probe) {
 122                ret = drv->probe(dev);
 123                if (ret)
 124                        goto probe_failed;
 125        }
 126
 127        driver_bound(dev);
 128        ret = 1;
 129        pr_debug("bus: '%s': %s: bound device %s to driver %s\n",
 130                 drv->bus->name, __FUNCTION__, dev->bus_id, drv->name);
 131        goto done;
 132
 133probe_failed:
 134        devres_release_all(dev);
 135        driver_sysfs_remove(dev);
 136        dev->driver = NULL;
 137
 138        if (ret != -ENODEV && ret != -ENXIO) {
 139               
 140                printk(KERN_WARNING
 141                       "%s: probe of %s failed with error %d\n",
 142                       drv->name, dev->bus_id, ret);
 143        }
 144       
 148        ret = 0;
 149done:
 150        atomic_dec(&probe_count);
 151        wake_up(&probe_waitqueue);
 152        return ret;
 153}
 154

���bus��driverͬʱ�߱�probe�����������ȵ������ߵ�probe�������������device_driver��probe��������probe�����Ǿ����������͵�driver���صĺ��������ʵ�������û����ͳһ������ʵ�ֲ�ͬ�Ĺ��ܡ�����platform_driver��˵������ǣ�
http://lxr.linux.no/#linux+v2.6.25/drivers/base/platform.c#L394
394static int platform_drv_probe(struct device *_dev)
 395{
 396        struct platform_driver *drv = to_platform_driver(_dev->driver);
 397        struct platform_device *dev = to_platform_device(_dev);
 398
 399        return drv->probe(dev);
 400}

Ȼ������ض�platform_driver������Ĳ���������������ڶ���ĳ��platform_driverʱ��ָ̬���Ĳ����ӿڡ�

���ˣ�platform_driver�ɹ��ҽӵ�platform bus���ˣ������ض����豸ʵ���˰󶨣������豸������probe����

6    bus��device��driver����֮��Ĺ�ϵ
�����ݽṹ����ϣ����ߡ��豸�����������໥������

platform device����device������device���Ի����Ӧ��bus��driver��

�豸��ӵ������Ϻ��γ�һ��˫��ѭ�������������߿��Ի�����Ϲҽӵ�����device����������� platform device������deviceҲ���Ի�������������������豸�����driver��

platform driver����driver������driver���Ի����Ӧ��bus���������bus�����е�device����һ�����platform device������name��driver��platform device����ƥ�䣬ƥ��ɹ���device����Ӧ��driver������������ʵ����platform device��platform driver�Ĺ�����

ƥ��ɹ������driver��probe��������platform driver��probe����probe��ʵ�������ض��Ĺ��ܡ�
 

7    ��Щ������plarform������
platform���ƽ��豸�������Դע����ںˣ����ں�ͳһ����������������ʹ����Щ��Դʱͨ��platform device�ṩ�ı�׼�ӿڽ������벢ʹ�á������������������Դ����Ķ����ԣ�����ӵ�и��õĿ���ֲ�ԡ�platform���Ƶı���ʹ�ò������ӣ�����������ɣ�platform_device��platfrom_driver��Platform driverͨ��platform bus��ȡplatform_device��

ͨ�������ֻҪ���ں˱������������Բ������Χ�豸����Զ����ģ�ӵ�и��Զ�������Դ(��ַ���ߺ�IRQs)���������� platform_driver��������timer��irq��Сϵͳ֮�ڵ��豸����ò���platfrom_driver���ơ�

platform_device�����ض���CPUֱ��Ѱַ�豸�ļĴ����ռ䣬��ʹ�������������豸���豸����ļĴ����޷�ͨ��CPU���߷��ʣ������ߵ�controller��Ȼ��Ҫͨ��platform bus������

��֮��platfrom_driver�ĸ���Ŀ����Ϊ��ͳһ����ϵͳ��������Դ��Ϊ���������ṩͳһ�Ľӿ�������ϵͳ��Դ������������Դ���룬��߳���Ŀ���ֲ�ԡ�

8    ����platform���ߵ�������������
����Platform���ߵ����������������£�
?    �����ʼ��platform bus
?    �������platform devices
?    ע�����platform devices
?    �������platform driver
?    ע�����platform driver
?    ��������豸

 
ͼ platform���ƿ�����������

��S3C24xxƽ̨Ϊ�������򵥽�����platform������ʵ�����̡�
8.1    ��ʼ��platform_bus
Platform���ߵĳ�ʼ������platform_bus_init()��ɵģ���������:
http://lxr.linux.no/#linux+v2.6.25/drivers/base/platform.c#L621
  26struct device platform_bus = {
  27        .bus_id         = "platform",
  28};
  29//EXPORT_SYMBOL_GPL(platform_bus);

621int __init platform_bus_init(void)
 622{
 623        int error;
 624
 625        error = device_register(&platform_bus);
 626        if (error)
 627                return error;
 628        error =  bus_register(&platform_bus_type);
 629        if (error)
 630                device_unregister(&platform_bus);
 631        return error;
 632}

�ú���������һ����Ϊ ��platform�����豸������platform���豸�����Դ�Ϊparent����sysfs�б�ʾΪ������platform���͵��豸��������� platform_bus�������Ŀ¼�£��� /sys/devices/platform���档
-sh-3.1# ls /sys/devices/platform/  
Fixed MDIO bus.0     fsl-i2c.0            serial8250
fsl-ehci.0           fsl-i2c.1            serial8250.0
fsl-gianfar.0        mpc83xx_spi.0        uevent
fsl-gianfar.1        mpc83xx_wdt.0
fsl-gianfar_mdio.-5  power

-sh-3.1# ls /sys/
block/    class/    firmware/ kernel/   power/   
bus/      devices/  fs/       module/  
-sh-3.1# ls /sys/bus/
i2c/         of_platform/ pci_express/ scsi/        usb/        
mdio_bus/    pci/         platform/    spi/        
-sh-3.1# ls /sys/bus/i2c/
devices/           drivers_autoprobe  uevent            
drivers/           drivers_probe   

-sh-3.1# ls /sys/bus/platform/devices/
Fixed MDIO bus.0/    fsl-gianfar_mdio.-5/ mpc83xx_wdt.0/
fsl-ehci.0/          fsl-i2c.0/           serial8250/
fsl-gianfar.0/       fsl-i2c.1/           serial8250.0/
fsl-gianfar.1/       mpc83xx_spi.0/      
-sh-3.1# ls /sys/bus/platform/drivers
drivers/           drivers_autoprobe  drivers_probe     
-sh-3.1# ls /sys/bus/platform/drivers/
fsl-ehci/         fsl-gianfar_mdio/ mpc83xx_spi/      serial8250/
fsl-gianfar/      fsl-i2c/          mpc83xx_wdt/    

platform_bus������ϵͳע���κ�platform driver��platform device֮ǰ��ʼ������ô�������ʵ�ֵ��أ�

http://lxr.linux.no/#linux+v2.6.25/drivers/base/init.c

  14
  20void __init driver_init(void)
  21{
  22       
  23        devices_init();
  24        buses_init();
  25        classes_init();
  26        firmware_init();
  27        hypervisor_init();
  28
  29       
  32        platform_bus_init();
  33        system_bus_init();
  34        cpu_dev_init();
  35        memory_dev_init();
  36}

init/main.c
start_kernel  �� rest_init  �� kernel_init  �� do_basic_setup��driver_init ��platform_bus_init

http://lxr.linux.no/#linux+v2.6.25/drivers/base/init.c#L32
724
 731static void __init do_basic_setup(void)
 732{
 733       
 734        init_workqueues();
 735        usermodehelper_init();
 736        driver_init();
 737        init_irq_proc();
 738        do_initcalls();
 739}

platform driver��platform device�ĳ�ʼ������do_initcalls�н��еġ�

8.2    ����platform_device
http://lxr.linux.no/#linux+v2.6.25/arch/arm/plat-s3c24xx/devs.c#L276�ж�����ϵͳ����Դ����һ���߶ȿ���ֲ���ļ����󲿷ְ弶��Դ�������Ｏ�ж��塣

274
 275
 276static struct resource s3c_i2c_resource[] = {
 277        [0] = {
 278                .start = S3C24XX_PA_IIC,
 279                .end   = S3C24XX_PA_IIC + S3C24XX_SZ_IIC - 1,
 280                .flags = IORESOURCE_MEM,
 281        },
 282        [1] = {
 283                .start = IRQ_IIC,
 284                .end   = IRQ_IIC,
 285                .flags = IORESOURCE_IRQ,
 286        }
 287
 288};
 289
 290struct platform_device s3c_device_i2c = {
 291        .name             = "s3c2410-i2c",
 292        .id               = -1,
 293        .num_resources    = ARRAY_SIZE(s3c_i2c_resource),
 294        .resource         = s3c_i2c_resource,
 295};
 296
 297//EXPORT_SYMBOL(s3c_device_i2c);

�豸����Ϊs3c2410-i2c����-1��ֻ��һ��i2c�豸��������Դs3c_i2c_resource���ֱ�Ϊi2c�������ļĴ����ռ���ж���Ϣ��

8.3    ע��platform_device

������platform_device����Ҫ��ӵ�ϵͳ�У��Ϳ��Ե��ú���platform_add_devices��
http://lxr.linux.no/#linux+v2.6.25/arch/arm/mach-s3c2440/mach-smdk2440.c

smdk2440_devices��ϵͳ��Դ��֯������ͳһע����ںˡ�

151static struct platform_device *smdk2440_devices[] __initdata = {
 152        &s3c_device_usb,
 153        &s3c_device_lcd,
 154        &s3c_device_wdt,
 155        &s3c_device_i2c,
 156        &s3c_device_iis,
 157};

166static void __init smdk2440_machine_init(void)
 167{
 168        s3c24xx_fb_set_platdata(&smdk2440_fb_info);
 169
 170        platform_add_devices(smdk2440_devices, ARRAY_SIZE(smdk2440_devices));
 171        smdk_machine_init();
 172}
 173
 174MACHINE_START(S3C2440, "SMDK2440")
 175       
 176        .phys_io        = S3C2410_PA_UART,
 177        .io_pg_offst    = (((u32)S3C24XX_VA_UART) >> 18) & 0xfffc,
 178        .boot_params    = S3C2410_SDRAM_PA + 0x100,
 179
 180        .init_irq       = s3c24xx_init_irq,
 181        .map_io         = smdk2440_map_io,
 182        .init_machine   = smdk2440_machine_init,
 183        .timer          = &s3c24xx_timer,
 184MACHINE_END

170        platform_add_devices(smdk2440_devices, ARRAY_SIZE(smdk2440_devices));
��ϵͳ������Դע���ϵͳ���ڴ�֮ǰplatform bus��Ҫ��ʼ���ɹ��������޷���platform devices�ҽӵ�platform bus�ϡ�Ϊ�˱�֤platform drive��ʼ��ʱ�����platform��Դ�Ѿ�ע���ϵͳ��smdk2440_machine_init��Ҫ����ִ�У�������Ϊƽ̨��ʼ��init_machine ʱ����������ϵͳ���������ĳ�ʼ����

�����˳�����£�
start_kernel��setup_arch��init_machine��arch_initcall(customize_machine)
http://lxr.linux.no/#linux+v2.6.25/arch/arm/kernel/setup.c#L788
786arch_initcall(customize_machine);
 787
 788void __init setup_arch(char **cmdline_p)
 789{
 790        struct tag *tags = (struct tag *)&init_tags;
 791        struct machine_desc *mdesc;
 792        char *from = default_command_line;
 793
 794        setup_processor();
 795        mdesc = setup_machine(machine_arch_type);
//����machine id�����ֲʱ�����machine desc�ṹ
 796        machine_name = mdesc->name;
 797
 798        if (mdesc->soft_reboot)
 799                reboot_setup("s");
 800
 801        if (__atags_pointer)
 802                tags = phys_to_virt(__atags_pointer);
 803        else if (mdesc->boot_params)
 804                tags = phys_to_virt(mdesc->boot_params);
 805
 806       
 810        if (tags->hdr.tag != ATAG_CORE)
 811                convert_to_tag_list(tags);
 812        if (tags->hdr.tag != ATAG_CORE)
 813                tags = (struct tag *)&init_tags;
 814
 815        if (mdesc->fixup)
 816                mdesc->fixup(mdesc, tags, &from, &meminfo);
 817
 818        if (tags->hdr.tag == ATAG_CORE) {
 819                if (meminfo.nr_banks != 0)
 820                        squash_mem_tags(tags);
 821                save_atags(tags);
 822                parse_tags(tags);
 823        }
 824
 825        init_mm.start_code = (unsigned long) &_text;
 826        init_mm.end_code   = (unsigned long) &_etext;
 827        init_mm.end_data   = (unsigned long) &_edata;
 828        init_mm.brk        = (unsigned long) &_end;
 829
 830        memcpy(boot_command_line, from, COMMAND_LINE_SIZE);
 831        boot_command_line[COMMAND_LINE_SIZE-1] = '\0';
 832        parse_cmdline(cmdline_p, from);
 833        paging_init(&meminfo, mdesc);
 834        request_standard_resources(&meminfo, mdesc);
 835
 836#ifdef CONFIG_SMP
 837        smp_init_cpus();
 838#endif
 839
 840        cpu_init();
 841
 842       
 845        init_arch_irq = mdesc->init_irq;
 846        system_timer = mdesc->timer;
 847        init_machine = mdesc->init_machine;
//��init_machineָ�븳ֵ
 848
 849#ifdef CONFIG_VT
 850#if defined(CONFIG_VGA_CONSOLE)
 851        conswitchp = &vga_con;
 852#elif defined(CONFIG_DUMMY_CONSOLE)
 853        conswitchp = &dummy_con;
 854#endif
 855#endif
 856}

777static void (*init_machine)(void) __initdata;
 778
 779static int __init customize_machine(void)
 780{
 781       
 782        if (init_machine)
 783                init_machine();
 784        return 0;
 785}
 786arch_initcall(customize_machine);
arch_initcall��customize_machine�����ض��Ķ��У�ϵͳ����ĳ���ط��������е�arch_initcall���εĺ�����

http://lxr.linux.no/#linux+v2.6.25/include/linux/init.h#L182
152#ifndef MODULE  //�ǿɼ���ģ�飬���������ӽ��ں˵Ĵ���
 153
 154#ifndef __ASSEMBLY__
 155
 156
 165
 166#define __define_initcall(level,fn,id) \
 167        static initcall_t __initcall_##fn##id __used \
 168        __attribute__((__section__(".initcall" level ".init"))) = fn
 169
 170
 176#define pure_initcall(fn)               __define_initcall("0",fn,0)
 177
 178#define core_initcall(fn)               __define_initcall("1",fn,1)
 179#define core_initcall_sync(fn)          __define_initcall("1s",fn,1s)
 180#define postcore_initcall(fn)           __define_initcall("2",fn,2)
 181#define postcore_initcall_sync(fn)      __define_initcall("2s",fn,2s)
 182#define arch_initcall(fn)               __define_initcall("3",fn,3)
 183#define arch_initcall_sync(fn)          __define_initcall("3s",fn,3s)
 184#define subsys_initcall(fn)             __define_initcall("4",fn,4)
 185#define subsys_initcall_sync(fn)        __define_initcall("4s",fn,4s)
 186#define fs_initcall(fn)                 __define_initcall("5",fn,5)
 187#define fs_initcall_sync(fn)            __define_initcall("5s",fn,5s)
 188#define rootfs_initcall(fn)             __define_initcall("rootfs",fn,rootfs)
 189#define device_initcall(fn)             __define_initcall("6",fn,6)
 190#define device_initcall_sync(fn)        __define_initcall("6s",fn,6s)
 191#define late_initcall(fn)               __define_initcall("7",fn,7)
 192#define late_initcall_sync(fn)          __define_initcall("7s",fn,7s)
 193
 194#define __initcall(fn) device_initcall(fn)
 195
 196#define __exitcall(fn) \
 197        static exitcall_t __exitcall_##fn __exit_call = fn
 198
������������������
 239#endif
 240
 241
 249#define //module_init(x)  __initcall(x);
 250
 251
 261#define //module_exit(x)  __exitcall(x);
 262
 263#else

����xx_core_initcall�����嵽�˲�ͬ�ķּ��Ķ���
����arch_initcall == __initcall_fn3 ����������������section  .initcall3.init. ��

//module_init()==__initcall(fn)==device_initcall(fn)== __initcall_fn6

�����ε����ȼ������ӽű�����
http://lxr.linux.no/#linux+v2.6.25/include/asm-generic/vmlinux.lds.h#L328
#define INITCALLS       \
   *(.initcall0.init)      \
   *(.initcall0s.init)      \
   *(.initcall1.init)      \
   *(.initcall1s.init)      \
   *(.initcall2.init)      \
   *(.initcall2s.init)      \
   *(.initcall3.init)      \
   *(.initcall3s.init)      \
   *(.initcall4.init)      \
   *(.initcall4s.init)      \
   *(.initcall5.init)      \
   *(.initcall5s.init)      \
 *(.initcallrootfs.init)      \
   *(.initcall6.init)      \
   *(.initcall6s.init)      \
   *(.initcall7.init)      \
   *(.initcall7s.init)

���__initcall_start�����ļ�arch/xxx/kernel/vmlinux.lds.S�����:
__initcall_start = .;
   INITCALLS
  __initcall_end = .;

http://lxr.linux.no/#linux+v2.6.25/init/main.c#L664
664static void __init do_initcalls(void)
 665{
 666        initcall_t *call;
 667        int count = preempt_count();
 668
 669        for (call = __initcall_start; call < __initcall_end; call++) {
.��������
 682
 683                result = (*call)();
 684
������ }              
 720       
 721        flush_scheduled_work();
 722}

���__initcall_fnx������ԽС��Խ�ȱ����ã���arch_initcall������//module_init�����εĺ�����

arch_initcall���εĺ����ĵ���˳�����£�
start_kernel  �� rest_init����setup_arch֮��  �� kernel_init  �� do_basic_setup��do_initcalls����driver_init()֮�󣩣���Ϊplatform_bus_init�ڴ�֮ǰ�Ѿ���ʼ������ˣ���ɽ��豸�ҽӵ��������ˡ�

8.4    ����platform_driver
Platform bus���豸��������˺���Ҫ����һ��platform driver�����������豸��

�����豸��˵��
290struct platform_device s3c_device_i2c = {
 291        .name             = "s3c2410-i2c",
 292        .id               = -1,
 293        .num_resources    = ARRAY_SIZE(s3c_i2c_resource),
 294        .resource         = s3c_i2c_resource,
 295};
 296
 297//EXPORT_SYMBOL(s3c_device_i2c);

����platform������device��driver��ƥ������֪��I2C ��platform driver��������s3c2410-i2c��

http://lxr.linux.no/#linux+v2.6.25/drivers/i2c/busses/i2c-s3c2410.c#L1
903
 904
 905static struct platform_driver s3c2410_i2c_driver = {
 906        .probe          = s3c24xx_i2c_probe,
 907        .remove         = s3c24xx_i2c_remove,
 908        .resume         = s3c24xx_i2c_resume,
 909        .driver         = {
 910                .owner  = THIS_MODULE,
 911                .name   = "s3c2410-i2c",
 912        },
 913};

8.5    ע��platform_driver
http://lxr.linux.no/#linux+v2.6.25/drivers/i2c/busses/i2c-s3c2410.c#L1

925static int __init i2c_adap_s3c_init(void)
 926{
 927        int ret;
 928
 929        ret = platform_driver_register(&s3c2410_i2c_driver);
 930        if (ret == 0) {
 931                ret = platform_driver_register(&s3c2440_i2c_driver);
 932                if (ret)
 933                        platform_driver_unregister(&s3c2410_i2c_driver);
 934        }
 935
 936        return ret;
 937}
 938

945//module_init(i2c_adap_s3c_init);
 946//module_exit(i2c_adap_s3c_exit);

��i2c_adap_s3c_init��ע��s3c2410_i2c_driver����ôi2c_adap_s3c_init��ʱִ�е��أ�//module_init(i2c_adap_s3c_init)����������initcall�Σ�����˳�����£�
init/main.c
start_kernel  �� rest_init  �� kernel_init  �� do_basic_setup��do_initcalls����Ϊplatform_bus_init�ڴ�֮ǰ�Ѿ���ʼ������ˣ����豸�Ѿ�ע�ᵽ�ں����ˣ����������ں˰󶨣������յ���s3c24xx_i2c_probe��

748
 752
 753static int s3c24xx_i2c_probe(struct platform_device *pdev)
 754{
 755        struct s3c24xx_i2c *i2c = &s3c24xx_i2c;
 756        struct resource *res;
 757        int ret;
 758
 759       
 760
 761        i2c->dev = &pdev->dev;
 762        i2c->clk = clk_get(&pdev->dev, "i2c");
 763        if (IS_ERR(i2c->clk)) {
 764                dev_err(&pdev->dev, "cannot get clock\n");
 765                ret = -ENOENT;
 766                goto err_noclk;
 767        }
 768
 769        dev_dbg(&pdev->dev, "clock source %p\n", i2c->clk);
 770
 771        clk_enable(i2c->clk);
 772
 773       
 774
 775        res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
 776        if (res == NULL) {
 777                dev_err(&pdev->dev, "cannot find IO resource\n");
 778                ret = -ENOENT;
 779                goto err_clk;
 780        }
 781
 782        i2c->ioarea = request_mem_region(res->start, (res->end-res->start)+1,
 783                                         pdev->name);
 784
 785        if (i2c->ioarea == NULL) {
 786                dev_err(&pdev->dev, "cannot request IO\n");
 787                ret = -ENXIO;
 788                goto err_clk;
 789        }
 790
 791        i2c->regs = ioremap(res->start, (res->end-res->start)+1);
 792
 793        if (i2c->regs == NULL) {
 794                dev_err(&pdev->dev, "cannot map IO\n");
 795                ret = -ENXIO;
 796                goto err_ioarea;
 797        }
 798
 799        dev_dbg(&pdev->dev, "registers %p (%p, %p)\n", i2c->regs, i2c->ioarea, res);
 800
 801       
 802
 803        i2c->adap.algo_data = i2c;
 804        i2c->adap.dev.parent = &pdev->dev;
 805
 806       
 807
 808        ret = s3c24xx_i2c_init(i2c);
 809        if (ret != 0)
 810                goto err_iomap;
 811
 812       
 815
 816        res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
 817        if (res == NULL) {
 818                dev_err(&pdev->dev, "cannot find IRQ\n");
 819                ret = -ENOENT;
 820                goto err_iomap;
 821        }
 822
 823        ret = request_irq(res->start, s3c24xx_i2c_irq, IRQF_DISABLED,
 824                          pdev->name, i2c);
 825
 826        if (ret != 0) {
 827                dev_err(&pdev->dev, "cannot claim IRQ\n");
 828                goto err_iomap;
 829        }
 830
 831        i2c->irq = res;
 832               
 833        dev_dbg(&pdev->dev, "irq resource %p (%lu)\n", res,
 834                (unsigned long)res->start);
 835
 836        ret = i2c_add_adapter(&i2c->adap);
 837        if (ret < 0) {
 838                dev_err(&pdev->dev, "failed to add bus to i2c core\n");
 839                goto err_irq;
 840        }
 841
 842        platform_set_drvdata(pdev, i2c);
 843
 844        dev_info(&pdev->dev, "%s: S3C I2C adapter\n", i2c->adap.dev.bus_id);
 845        return 0;
 846
 847 err_irq:
 848        free_irq(i2c->irq->start, i2c);
 849
 850 err_iomap:
 851        iounmap(i2c->regs);
 852
 853 err_ioarea:
 854        release_resource(i2c->ioarea);
 855        kfree(i2c->ioarea);
 856
 857 err_clk:
 858        clk_disable(i2c->clk);
 859        clk_put(i2c->clk);
 860
 861 err_noclk:
 862        return ret;
 863}

������probe��������Ҫ��ȡ�豸����Դ��Ϣ�����û�ȡ��Դ�ĺ�����Ҫ�ǣ�
struct resource * platform_get_resource(struct platform_device *dev, unsigned int type, unsigned int num);
���ݲ���type��ָ�����ͣ�����IORESOURCE_MEM������ȡָ������Դ��
struct int platform_get_irq(struct platform_device *dev, unsigned int num);
��ȡ��Դ�е��жϺš�
struct resource * platform_get_resource_byname(struct platform_device *dev, unsigned int type, char *name);
���ݲ���name��ָ�������ƣ�����ȡָ������Դ��
int platform_get_irq_byname(struct platform_device *dev, char *name);
���ݲ���name��ָ�������ƣ�����ȡ��Դ�е��жϺš�

��probe������ȡ����IO�ռ䣬ͨ��request_mem_region��ioremap�Ȳ��������ַת�����ں��е������ַ����ʼ��I2C��������ͨ��platform_get_irq��platform_get_resource�õ��豸���жϺ��Ժ󣬾Ϳ��Ե���request_irq��������ϵͳע���жϣ�������I2C��������ӵ�ϵͳ�С�

8.6    �����豸
������platform_device_register ��platform_driver_register����������Ӧ��Ϣ�ͳ�����sysĿ¼����Ӧ�ļ����£�Ȼ�����Ǹ���ε����豸�أ�����ô���豸���д򿪶�д�Ȳ����أ�����

Platform����ֻ��Ϊ�˷������ҽ���CPU�����ϵ��豸�����û��ռ�Ľ��������д������Ҫ����file_operations����Ȼ�����platform�豸������û��ռ佻����������file_operationsʵ����

����I2C������˵����file_operations���£�
http://lxr.linux.no/#linux+v2.6.25/drivers/i2c/i2c-core.c#L461
 478static const struct file_operations i2cdev_fops = {
 479        .owner          = THIS_MODULE,
 480        .llseek         = no_llseek,
 481        .read           = i2cdev_read,
 482        .write          = i2cdev_write,
 483        .ioctl          = i2cdev_ioctl,
 484        .open           = i2cdev_open,
 485        .release        = i2cdev_release,
 486};

���platform bus���������ڣ�platform bus�ṩ���Ʒ���I2C �������������Դ����I2C�����ṩ����I2C �������Ϲҽӵ�I2C�豸�Ļ��ơ�

