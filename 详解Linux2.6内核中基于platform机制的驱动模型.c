详解Linux2.6内核中基于platform机制的驱动模型(2010-10-22 14:27:45)转载▼标签： 杂谈 分类： 2010.3~  
摘要 本文以Linux 2.6.25 内核为例，分析了基于platform总线的驱动模型。首先介绍了Platform总线的基本概念，接着介绍了platform device和platform driver的定义和加载过程，分析了其与基类device 和driver的派生关系及在此过程中面向对象的设计思想。最后以ARM S3C2440中I2C控制器为例介绍了基于platform总线的驱动开发流程。

【关键字】platform_bus, platform_device, resource , platform_driver, file_operations

目录

1    何谓platform bus？    2
2    device和platform_device    3
3    device_register和platform_device_register    5
4    device_driver和platform driver    8
5    driver_register 和platform_driver_register    10
6    bus、device及driver三者之间的关系    17
7    哪些适用于plarform驱动？    18
8    基于platform总线的驱动开发流程    18
8.1    初始化platform_bus    19
8.2    定义platform_device    22
8.3    注册platform_device    22
8.4    定义platform_driver    28
8.5    注册platform_driver    29
8.6    操作设备    32

1    何谓platform bus？
Linux系统中许多部分对设备是如何链接的并不感兴趣，但是他们需要知道哪些类型的设备是可以使用的。设备模型提供了一种机制来对设备进行分类，在更高的功能层面上描述这些设备，并使得这些设备对用户空间可见。因此从2.6内核开始引入了设备模型。

总线是处理器和一个或多个设备之间的通道，在设备模型中, 所有的设备都通过总线相连。总线可以相互插入。设备模型展示了总线和它们所控制的设备之间的实际连接。

Platform总线是2.6 kernel中最近引入的一种虚拟总线，主要用来管理CPU的片上资源，具有更好的移植性，因此在2.6 kernel中，很多驱动都用platform改写了。

platform_bus_type的定义如下:
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

总线名称是"platform"，其只是bus_type的一种，定义了总线的属性，同时platform_bus_type还有相关操作方法，如挂起、中止、匹配及hotplug事件等。

总线bus是联系driver和device的中间枢纽。Device通过所属的bus找到driver，由match操作方法进行匹配。

 
Bus、driver及devices的连接关系

2    device和platform_device
Plarform device会有一个名字用于driver binding（在注册driver的时候会查找driver的目标设备的bus位置，这个过程称为driver binding），另外IRQ以及地址空间等资源也要给出 。

platform_device结构体用来描述设备的名称、资源信息等。该结构被定义在http://lxr.linux.no/#linux+v2.6.25/include/linux/platform_device.h#L16中，定义原型如下：

  16struct platform_device {
  17        const char      * name; //定义平台设备的名称，此处设备的命名应和相应驱动程序命名一致

  18        int             id;
  19        struct device   dev;
  20        u32             num_resources;
  21        struct resource * resource;  //定义平台设备的资源
  22};

在这个结构里封装了struct device及struct resource。可知：platform_device由device派生而来，是一种特殊的device。

下面来看一下platform_device结构体中最重要的一个成员struct resource * resource。struct resource被定义在http://lxr.linux.no/#linux+v2.6.25/include/linux/ioport.h#L18中，定义原型如下：
  14
  18struct resource {
  19        resource_size_t start;  //定义资源的起始地址
  20        resource_size_t end;  //定义资源的结束地址
  21        const char *name; //定义资源的名称
  22        unsigned long flags; 定义资源的类型，比如MEM，IO，IRQ，DMA类型
  23        struct resource *parent, *sibling, *child;
  24};

这个结构表示设备所拥有的资源，即I/O端口、I/O映射内存、中断及DMA等。这里的地址指的是物理地址。

另外还需要注意platform_device中的device结构，它详细描述了设备的情况，其为所有设备的基类，定义如下：
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

3    device_register和platform_device_register

http://lxr.linux.no/#linux+v2.6.25/drivers/base/core.c#L881
 870
 881int device_register(struct device *dev)
 882{
 883        device_initialize(dev);
 884        return device_add(dev);
 885}
初始化一个设备，然后加入到系统中。

http://lxr.linux.no/#linux+v2.6.25/drivers/base/platform.c#L325
316
 320int platform_device_register(struct platform_device *pdev)
 321{
 322        device_initialize(&pdev->dev);
 323        return platform_device_add(pdev);
 324}
 325//EXPORT_SYMBOL_GPL(platform_device_register);

我们看到注册一个platform device分为了两部分，初始化这个platform_device，然后将此platform_device添加到platform总线中。输入参数platform_device可以是静态的全局设备。

另外一种机制就是动态申请platform_device_alloc一个platform_device设备，然后通过platform_device_add_resources及platform_device_add_data等添加相关资源和属性。

无论哪一种platform_device，最终都将通过platform_device_add这册到platform总线上。

229
 236int platform_device_add(struct platform_device *pdev)
 237{
 238        int i, ret = 0;
 239
 240        if (!pdev)
 241                return -EINVAL;
 242
初始化设备的parent为platform_bus，初始化驱备的总线为platform_bus_type。
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
设置设备struct device 的bus_id成员，留心这个地方，在以后还需要用到这个的。
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
//resources分为两种IORESOURCE_MEM和IORESOURCE_IO
 //CPU对外设IO端口物理地址的编址方式有两种：I/O映射方式和内存映射方式
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

由platform_device_register和platform_device_add的实现可知，device_register()和platform_device_register()都会首先初始化设备
区别在于第二步：其实platform_device_add()包括device_add()，不过要先注册resources，然后将设备挂接到特定的platform总线。

4    device_driver和platform driver
Platform device是一种device自己是不会做事情的，要有人为它做事情，那就是platform driver。platform driver遵循linux系统的driver model。对于device的discovery/enumerate都不是driver自己完成的而是由由系统的driver注册机制完成。driver编写人员只要将注册必须的数据结构初始化并调用注册driver的kernel API就可以了。

接下来来看platform_driver结构体的原型定义，在http://lxr.linux.no/#linux+v2.6.25/include/linux/platform_device.h#L48中，代码如下：
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

可见，它包含了设备操作的几个功能函数，同时包含了一个device_driver结构，说明device_driver是platform_driver的基类。驱动程序中需要初始化这个变量。下面看一下这个变量的定义，位于http://lxr.linux.no/#linux+v2.6.25/include/linux/device.h#L121中：
 
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

device_driver提供了一些操作接口，但其并没有实现，相当于一些虚函数，由派生类platform_driver进行重载，无论何种类型的driver都是基于device_driver派生而来的，具体的各种操作都是基于统一的基类接口的，这样就实现了面向对象的设计。

需要注意这两个变量：name和owner。其作用主要是为了和相关的platform_device关联起来，owner的作用是说明模块的所有者，驱动程序中一般初始化为THIS_MODULE。

device_driver结构中也有一个name变量。platform_driver从字面上来看就知道是设备驱动。设备驱动是为谁服务的呢？当然是设备了。内核正是通过这个一致性来为驱动程序找到资源，即 platform_device中的resource。

5    driver_register 和platform_driver_register

内核提供的platform_driver结构体的注册函数为platform_driver_register（），其原型定义在http://lxr.linux.no/#linux+v2.6.25/drivers/base/platform.c#L458文件中，具体实现代码如下：
439
 443int platform_driver_register(struct platform_driver *drv)
 444{
 445        drv->driver.bus = &platform_bus_type;
  

 446        if (drv->probe)
 447                drv->driver.probe = platform_drv_probe;
 //在really_probe函数中，回调了platform_drv_probe函数

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

不要被上面的platform_drv_XXX吓倒了，它们其实很简单，就是将struct device转换为struct platform_device和struct platform_driver，然后调用platform_driver中的相应接口函数。那为什么不直接调用platform_drv_XXX等接口呢？这就是Linux内核中面向对象的设计思想。

device_driver提供了一些操作接口，但其并没有实现，相当于一些虚函数，由派生类platform_driver进行重载，无论何种类型的driver都是基于device_driver派生而来的，device_driver中具体的各种操作都是基于统一的基类接口的，这样就实现了面向对象的设计。

在文件http://lxr.linux.no/#linux+v2.6.25/drivers/base/driver.c#L234中，实现了driver_register()函数。

209
 217int driver_register(struct device_driver *drv)
 218{
 219        int ret;
 220
//如果总线的方法和设备自己的方法同时存在，将打印告警信息，对于platform bus，其没有probe等接口
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

226        其主要将驱动挂接到总线上，通过总线来驱动设备。

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

如果总线上的driver是自动probe的话，则将该总线上的driver和device绑定起来。

http://lxr.linux.no/#linux+v2.6.25/drivers/base/dd.c#L285
272
 281int driver_attach(struct device_driver *drv)
 282{
 283        return bus_for_each_dev(drv->bus, NULL, drv, __driver_attach);
 284}
 285//EXPORT_SYMBOL_GPL(driver_attach);

扫描该总线上的每一个设备，将当前driver和总线上的设备进行match，如果匹配成功，则将设备和driver绑定起来。

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

263，如果该设备尚没有匹配的driver，则尝试匹配。

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

193，如果该总线上的设备需要进行匹配，则验证是否匹配。对于platform总线，其匹配过程如下：
http://lxr.linux.no/#linux+v2.6.25/drivers/base/platform.c#L555
542
 555static int platform_match(struct device *dev, struct device_driver *drv)
 556{
 557        struct platform_device *pdev;
 558
 559        pdev = container_of(dev, struct platform_device, dev);
 560        return (strncmp(pdev->name, drv->name, BUS_ID_SIZE) == 0);
 561}

560，简单的进行字符串匹配，这也是我们强调platform_device和platform_driver中的name属性需要一致的原因。

匹配成功后，则调用probe接口。
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

如果bus和driver同时具备probe方法，则优先调用总线的probe函数。否则调用device_driver的probe函数，此probe函数是经过各种类型的driver重载的函数，这就实现了利用基类的统一方法来实现不同的功能。对于platform_driver来说，其就是：
http://lxr.linux.no/#linux+v2.6.25/drivers/base/platform.c#L394
394static int platform_drv_probe(struct device *_dev)
 395{
 396        struct platform_driver *drv = to_platform_driver(_dev->driver);
 397        struct platform_device *dev = to_platform_device(_dev);
 398
 399        return drv->probe(dev);
 400}

然后调用特定platform_driver所定义的操作方法，这个是在定义某个platform_driver时静态指定的操作接口。

至此，platform_driver成功挂接到platform bus上了，并与特定的设备实现了绑定，并对设备进行了probe处理。

6    bus、device及driver三者之间的关系
在数据结构设计上，总线、设备及驱动三者相互关联。

platform device包含device，根据device可以获得相应的bus及driver。

设备添加到总线上后形成一个双向循环链表，根据总线可以获得其上挂接的所有device，进而获得了 platform device。根据device也可以获得驱动该总线上所有设备的相关driver。

platform driver包含driver，根据driver可以获得相应的bus，进而获得bus上所有的device，进一步获得platform device，根据name对driver与platform device进行匹配，匹配成功后将device与相应的driver关联起来，即实现了platform device和platform driver的关联。

匹配成功后调用driver的probe进而调用platform driver的probe，在probe里实现驱动特定的功能。
 

7    哪些适用于plarform驱动？
platform机制将设备本身的资源注册进内核，由内核统一管理，在驱动程序中使用这些资源时通过platform device提供的标准接口进行申请并使用。这样提高了驱动和资源管理的独立性，这样拥有更好的可移植性。platform机制的本身使用并不复杂，由两部分组成：platform_device和platfrom_driver。Platform driver通过platform bus获取platform_device。

通常情况下只要和内核本身运行依赖性不大的外围设备，相对独立的，拥有各自独立的资源(地址总线和IRQs)，都可以用 platform_driver来管理，而timer，irq等小系统之内的设备则最好不用platfrom_driver机制。

platform_device最大的特定是CPU直接寻址设备的寄存器空间，即使对于其他总线设备，设备本身的寄存器无法通过CPU总线访问，但总线的controller仍然需要通过platform bus来管理。

总之，platfrom_driver的根本目的是为了统一管理系统的外设资源，为驱动程序提供统一的接口来访问系统资源，将驱动和资源分离，提高程序的可移植性。

8    基于platform总线的驱动开发流程
基于Platform总线的驱动开发流程如下：
?    定义初始化platform bus
?    定义各种platform devices
?    注册各种platform devices
?    定义相关platform driver
?    注册相关platform driver
?    操作相关设备

 
图 platform机制开发驱动流程

以S3C24xx平台为例，来简单讲述下platform驱动的实现流程。
8.1    初始化platform_bus
Platform总线的初始化是在platform_bus_init()完成的，代码如下:
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

该函数创建了一个名为 “platform”的设备，后续platform的设备都会以此为parent。在sysfs中表示为：所有platform类型的设备都会添加在 platform_bus所代表的目录下，即 /sys/devices/platform下面。
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

platform_bus必须在系统注册任何platform driver和platform device之前初始化，那么这是如何实现的呢？

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
start_kernel  》 rest_init  》 kernel_init  》 do_basic_setup》driver_init 》platform_bus_init

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

platform driver和platform device的初始化是在do_initcalls中进行的。

8.2    定义platform_device
http://lxr.linux.no/#linux+v2.6.25/arch/arm/plat-s3c24xx/devs.c#L276中定义了系统的资源，是一个高度可移植的文件，大部分板级资源都在这里集中定义。

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

设备名称为s3c2410-i2c，“-1”只有一个i2c设备，两个资源s3c_i2c_resource，分别为i2c控制器的寄存器空间和中断信息。

8.3    注册platform_device

定义了platform_device后，需要添加到系统中，就可以调用函数platform_add_devices。
http://lxr.linux.no/#linux+v2.6.25/arch/arm/mach-s3c2440/mach-smdk2440.c

smdk2440_devices将系统资源组织起来，统一注册进内核。

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
将系统所有资源注册进系统，在此之前platform bus需要初始化成功，否则无法将platform devices挂接到platform bus上。为了保证platform drive初始化时，相关platform资源已经注册进系统，smdk2440_machine_init需要很早执行，而其作为平台初始化init_machine 时，将优先于系统所有驱动的初始化。

其调用顺序如下：
start_kernel》setup_arch》init_machine》arch_initcall(customize_machine)
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
//根据machine id获得移植时定义的machine desc结构
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
//对init_machine指针赋值
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
arch_initcall将customize_machine放在特定的段中，系统将在某个地方运行所有的arch_initcall修饰的函数。

http://lxr.linux.no/#linux+v2.6.25/include/linux/init.h#L182
152#ifndef MODULE  //非可加载模块，即编译链接进内核的代码
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
。。。。。。。。。
 239#endif
 240
 241
 249#define //module_init(x)  __initcall(x);
 250
 251
 261#define //module_exit(x)  __exitcall(x);
 262
 263#else

各种xx_core_initcall被定义到了不同的分级的段中
所以arch_initcall == __initcall_fn3 它将被链接器放于section  .initcall3.init. 中

//module_init()==__initcall(fn)==device_initcall(fn)== __initcall_fn6

各个段的优先级由链接脚本定义
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

这个__initcall_start是在文件arch/xxx/kernel/vmlinux.lds.S定义的:
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
.。。。。
 682
 683                result = (*call)();
 684
。。。 }              
 720       
 721        flush_scheduled_work();
 722}

因此__initcall_fnx，数字越小，越先被调用，故arch_initcall优先于//module_init所修饰的函数。

arch_initcall修饰的函数的调用顺序如下：
start_kernel  》 rest_init（在setup_arch之后）  》 kernel_init  》 do_basic_setup》do_initcalls（在driver_init()之后），因为platform_bus_init在此之前已经初始化完毕了，便可将设备挂接到总线上了。

8.4    定义platform_driver
Platform bus和设备都定义好了后，需要定义一个platform driver用来驱动此设备。

对于设备来说：
290struct platform_device s3c_device_i2c = {
 291        .name             = "s3c2410-i2c",
 292        .id               = -1,
 293        .num_resources    = ARRAY_SIZE(s3c_i2c_resource),
 294        .resource         = s3c_i2c_resource,
 295};
 296
 297//EXPORT_SYMBOL(s3c_device_i2c);

根据platform总线上device和driver的匹配规则可知，I2C 的platform driver的名字是s3c2410-i2c。

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

8.5    注册platform_driver
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

在i2c_adap_s3c_init中注册s3c2410_i2c_driver，那么i2c_adap_s3c_init何时执行的呢？//module_init(i2c_adap_s3c_init)表明其存放在initcall段，调用顺序如下：
init/main.c
start_kernel  》 rest_init  》 kernel_init  》 do_basic_setup》do_initcalls，因为platform_bus_init在此之前已经初始化完毕了，且设备已经注册到内核中了，驱动将和内核绑定，并最终调用s3c24xx_i2c_probe。

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

当进入probe函数后，需要获取设备的资源信息，常用获取资源的函数主要是：
struct resource * platform_get_resource(struct platform_device *dev, unsigned int type, unsigned int num);
根据参数type所指定类型，例如IORESOURCE_MEM，来获取指定的资源。
struct int platform_get_irq(struct platform_device *dev, unsigned int num);
获取资源中的中断号。
struct resource * platform_get_resource_byname(struct platform_device *dev, unsigned int type, char *name);
根据参数name所指定的名称，来获取指定的资源。
int platform_get_irq_byname(struct platform_device *dev, char *name);
根据参数name所指定的名称，来获取资源中的中断号。

此probe函数获取物理IO空间，通过request_mem_region和ioremap等操作物理地址转换成内核中的虚拟地址，初始化I2C控制器，通过platform_get_irq或platform_get_resource得到设备的中断号以后，就可以调用request_irq函数来向系统注册中断，并将此I2C控制器添加到系统中。

8.6    操作设备
进行了platform_device_register 和platform_driver_register后，驱动的相应信息就出现在sys目录的相应文件夹下，然后，我们该如何调用设备呢？？怎么对设备进行打开读写等操作呢？？？

Platform总线只是为了方便管理挂接在CPU总线上的设备，与用户空间的交互，如读写还是需要利用file_operations。当然如果此platform设备无需和用户空间交互，则无需file_operations实例。

对于I2C总线来说，其file_operations如下：
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

其和platform bus的区别在于，platform bus提供机制访问I2C 控制器本身的资源，而I2C总线提供访问I2C 控制器上挂接的I2C设备的机制。

