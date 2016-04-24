// Linux input子系统分析
// 概述与数据结构
// [日期：2011-09-18] 来源：Linux社区  作者：YAOZHENGUO2006 
// 
//  
// Input子系统处理输入事务，任何输入设备的驱动程序都可以通过Input输入子系统提供的接口注册到内核，利用子系统提供的功能来与用户空间交互。输入设备一般包括键盘，鼠标，触摸屏等，在内核中都是以输入设备出现的。下面分析input输入子系统的结构，以及功能实现。
// 一. Input子系统结构与功能实现
//   1. Input子系统是分层结构的，总共分为三层： 硬件驱动层，子系统核心层，事件处理层。  
// 
//     （1）其中硬件驱动层负责操作具体的硬件设备，这层的代码是针对具体的驱动程序的，需要驱动程序的作者来编写。
//     （2）子系统核心层是链接其他两个层之间的纽带与桥梁，向下提供驱动层的接口，向上提供事件处理层的接口。
//     （3）事件处理层负责与用户程序打交道，将硬件驱动层传来的事件报告给用户程序。
//   2. 各层之间通信的基本单位就是事件，任何一个输入设备的动作都可以抽象成一种事件，如键盘的按下，触摸屏的按下，鼠标的移动等。事件有三种属性：类型（type），编码(code)，值(value)，Input子系统支持的所有事件都定义在input.h中，包括所有支持的类型，所属类型支持的编码等。事件传送的方向是 硬件驱动层-->子系统核心-->事件处理层-->用户空间
//   3. 以触摸屏为例说明输入子系统的工作流程:
//      注：mini2440的触摸屏驱动所用驱动层对应的模块文件为：s3c2410_ts.c，事件处理层对应的模块文件为 evdev.c
//     （1）s3c2410_ts模块初始化函数中将触摸屏注册到了输入子系统中，于此同时，注册函数在事件处理层链表中寻找事件处理器，这里找到的是evdev，并且将驱动与事件处理器挂载。并且在/dev/input中生成设备文件event0，以后我们访问这个文件就会找的我们的触摸屏驱动程序。
//     （2）应用程序打开设备文件/dev/input/event0，读取设备文件，调用evdev模块中read,如果没有事件进程就会睡眠。  
//     （3）当触摸屏按下，驱动层通过子系统核心将事件（就是X，Y坐标）,传给事件处理层也就是evdev,evdev唤醒睡眠的进程，将事件传给进程处理。
// 
// 二.主要input通用数据结构
//   1.input_dev 这是input设备基本的设备结构，每个input驱动程序中都必须分配初始化这样一个结构，成员比较多 
//     （1）有以下几个数组：
// 
1.unsigned long evbit[BITS_TO_LONGS(EV_CNT)];   //事件支持的类型   
2.        // 下面是每种类型支持的编码   3.    unsigned long keybit[BITS_TO_LONGS(KEY_CNT)];   //按键     4.    unsigned long relbit[BITS_TO_LONGS(REL_CNT)];     5.    unsigned long absbit[BITS_TO_LONGS(ABS_CNT)];   //绝对坐标，其中触摸屏驱动使用的就是这个   6.    unsigned long mscbit[BITS_TO_LONGS(MSC_CNT)];  7.    unsigned long ledbit[BITS_TO_LONGS(LED_CNT)];  8.    unsigned long sndbit[BITS_TO_LONGS(SND_CNT)];  9.    unsigned long ffbit[BITS_TO_LONGS(FF_CNT)];  10.    unsigned long swbit[BITS_TO_LONGS(SW_CNT)];      evbit[BITS_TO_LONGS(EV_CNT)]; 这个数组以位掩码的形式，代表了这个设备支持的事件的类型。设置方式如：
//    dev->evbit[0] = BIT(EV_SYN) | BIT(EV_KEY) | BIT(EV_ABS)
//    absbit[BITS_TO_LONGS(ABS_CNT)]; 这个数组也是以位掩码的形式，代表这个类型的事件支持的编码
//    触摸屏驱动支持EV_ABS,所以要设置这个数组， 有一个专门设置这个数组的函数input_set_abs_params，代码如下: 
1.static inline void input_set_abs_params(struct input_dev *dev, int axis, int min, int max, int fuzz, int flat)  
2.{  
3.    dev->absmin[axis] = min;  
4.    dev->absmax[axis] = max;  
5.    dev->absfuzz[axis] = fuzz;  
6.    dev->absflat[axis] = flat;  
7.  
8.    dev->absbit[BIT_WORD(axis)] |= BIT_MASK(axis);  //填充了absbit这个数组   9.}  
//   触摸屏驱动中是这样调用的
    input_set_abs_params(dev, ABS_X, 0, 0x3FF, 0, 0)；   //这个是设置ad转换的x坐标
    input_set_abs_params(dev, ABS_Y, 0, 0x3FF, 0, 0);   //这个是设置ad转换的y坐标
    input_set_abs_params(dev, ABS_PRESSURE, 0, 1, 0, 0); //这个是设置触摸屏是否按下的标志
//    设置ABS_X编码值范围为0-0x3ff，因为mini2440的AD转换出的数据最大为10位，所以不会超过0x3ff。 
//
//  （2） struct input_id id 成员
//     这个是标识设备驱动特征的
//
1.struct input_id {  
2.    __u16 bustype;   //总线类型   3.    __u16 vendor;    //生产厂商   4.    __u16 product;   //产品类型   5.    __u16 version;   //版本   6. };  
//   如果需要特定的事件处理器来处理这个设备的话，这几个就非常重要，因为子系统核心是通过他们，将设备驱动与事件处理层联系起来的。但是因为触摸屏驱动所用的事件处理器为evdev，匹配所有，所有这个初始化
//    也无关紧要。
//  （3） 还有其他一些成员，也比较重要，但是驱动程序可以不用管，都是由子系统核心来处理的。
//  （4） 可以看出input_dev 结构所属层为硬件驱动层，以后就用input_dev来表示输入设备。
//  2. input_handler 这是事件处理器的数据结构，代表一个事件处理器
//   （1）几个操作函数
    void (*event)(struct input_handle *handle, unsigned int type, unsigned int code, int value);
    int (*connect)(struct input_handler *handler, struct input_dev *dev, const struct input_device_id *id);
    void (*disconnect)(struct input_handle *handle);
    void (*start)(struct input_handle *handle);
//    event 函数是当事件处理器接收到了来自input设备传来的事件时调用的处理函数，负责处理事件，非常重要，在事件传递过程中会详细分析。
//    connect 函数是当一个input设备模块注册到内核的时候调用的，将事件处理器与输入设备联系起来的函数，也就是将input_dev和input_handler配对的函数。
//    disconnect 函数实现connect相反的功能。
//    start 暂时没有发现有什么作用。
//  （2） 两个id
    const struct input_device_id *id_table; //这个是事件处理器所支持的input设备
//    const struct input_device_id *blacklist; //这个是事件处理器应该忽略的input设备
//     这两个数组都会用在connect函数中，input_device_id结构与input_id结构类似，但是input_device_id有一个flag，用来让程序选择比较哪项，如：busytype,vendor还是其他。
//   （3） 两个链表
    struct list_headh_list;  //这个链表用来链接他所支持的input_handle结构,input_dev与input_handler配对之后就会生成一个input_handle结构
    struct list_headnode;    //链接到input_handler_list，这个链表链接了所有注册到内核的事件处理器
//  3.  input_handle 结构体代表一个成功配对的input_dev和input_handler 
1.struct input_handle {  
2.    void *private;   //每个配对的事件处理器都会分配一个对应的设备结构，如evdev事件处理器的evdev结构，注意这个结构与设备驱动层的input_dev不同，初始化handle时，保存到这里。   3.    int open;        //打开标志，每个input_handle 打开后才能操作，这个一般通过事件处理器的open方法间接设置   4.    const char *name;   5.    struct input_dev *dev;  //关联的input_dev结构   6.    struct input_handler *handler; //关联的input_handler结构   7.    struct list_head    d_node;  //input_handle通过d_node连接到了input_dev上的h_list链表上   8.    struct list_head    h_node;  //input_handle通过h_node连接到了input_handler的h_list链表上   9.};  
//  4. 三个数据结构之间的关系
//     input_dev 是硬件驱动层，代表一个input设备
//     input_handler 是事件处理层，代表一个事件处理器
//     input_handle 个人认为属于核心层，代表一个配对的input设备与input事件处理器
//     input_dev 通过全局的input_dev_list链接在一起。设备注册的时候实现这个操作。
//     input_handler 通过全局的input_handler_list链接在一起。事件处理器注册的时候实现这个操作（事件处理器一般内核自带，一般不需要我们来写）
//
//     input_hande 没有一个全局的链表，它注册的时候将自己分别挂在了input_dev 和 input_handler 的h_list上了。通过input_dev 和input_handler就可以找到input_handle 在设备注册和事件处理器， 注册的时候都要进行配对工作，配对后就会实现链接。通过input_handle也可以找到input_dev和input_handler。
//
//本篇文章来源于 Linux公社网站(www.linuxidc.com)  原文链接：http://www.linuxidc.com/Linux/2011-09/43187.htm
//
//
//一. 各种注册函数 
//    因为分析一所讲的每种数据结构都代表一类对象，所以每种数据结构都会对应一个注册函数，他们都定义在子系统核心的input.c文件中。主要有三个注册函数
//     input_register_device    向内核注册一个input设备
//     input_register_handle    向内核注册一个handle结构
// 
//
//     input_register_handler   注册一个事件处理器
//  1. input_register_device 注册一个input输入设备，这个注册函数在三个注册函数中是驱动程序唯一调用的。下面分析这个函数：
//
//
 
1.int input_register_device(struct input_dev *dev)  
2.{  
3.    static atomic_t input_no = ATOMIC_INIT(0);    4.        //这个原子变量，代表总共注册的input设备，每注册一个加1，因为是静态变量，所以每次调用都不会清零的   5.    struct input_handler *handler;  6.    const char *path;  7.    int error;  8.  
9.    __set_bit(EV_SYN, dev->evbit);  //EN_SYN 这个是设备都要支持的事件类型，所以要设置   10.  
11.    /* 12.     * If delay and period are pre-set by the driver, then autorepeating 
13.     * is handled by the driver itself and we don't do it in input.c. 
14.     */  
15.        // 这个内核定时器是为了重复按键而设置的   16.    init_timer(&dev->timer);  
17.    if (!dev->rep[REP_DELAY] && !dev->rep[REP_PERIOD]) {  18.        dev->timer.data = (long) dev;  19.        dev->timer.function = input_repeat_key;  
20.        dev->rep[REP_DELAY] = 250;  
21.        dev->rep[REP_PERIOD] = 33;  
22.        //如果没有定义有关重复按键的相关值，就用内核默认的   23.    }  
24.  
25.    if (!dev->getkeycode)  26.        dev->getkeycode = input_default_getkeycode;  
27.    if (!dev->setkeycode)  28.        dev->setkeycode = input_default_setkeycode;  
29.        //以上设置的默认函数由input核心提供   30.    dev_set_name(&dev->dev, "input%ld",  31.             (unsigned long) atomic_inc_return(&input_no) - 1);  32.        //设置input_dev中device的名字，这个名字会在/class/input中出现   33.    error = device_add(&dev->dev);  
34.        //将device加入到linux设备模型中去   35.    if (error)  36.        return error;  37.  
38.    path = kobject_get_path(&dev->dev.kobj, GFP_KERNEL);  
39.    printk(KERN_INFO "input: %s as %s\n",  40.        dev->name ? dev->name : "Unspecified device", path ? path : "N/A");  41.    kfree(path);  
42.        //这个得到路径名称，并打印出来   43.    error = mutex_lock_interruptible(&input_mutex);  
44.    if (error) {  45.        device_del(&dev->dev);  
46.        return error;  47.    }  
48.  
49.    list_add_tail(&dev->node, &input_dev_list);  
50.        // 将新分配的input设备连接到input_dev_list链表上   51.    list_for_each_entry(handler, &input_handler_list, node)  
52.        input_attach_handler(dev, handler);  
53.        //遍历input_handler_list链表，配对 input_dev 和 input_handler   54.        //input_attach_handler 这个函数是配对的关键，下面将详细分析   55.    input_wakeup_procfs_readers();  
56.        // 和proc文件系统有关，暂时不考虑   57.    mutex_unlock(&input_mutex);  
58.  
59.    return 0;  60.   }  
//   input_register_device完成的主要功能就是：初始化一些默认的值，将自己的device结构添加到linux设备模型当中，将input_dev添加到input_dev_list链表中，然后寻找合适的handler与input_handler配对,配对的核心函数是input_attach_handler。下面分析input_attach_handler函数：
//
 
1.static int input_attach_handler(struct input_dev *dev, struct input_handler *handler)  
2.{  
3.    const struct input_device_id *id;  4.    int error;  5.  
6.    if (handler->blacklist && input_match_device(handler->blacklist, dev))  7.        return -ENODEV;  8.        //blacklist是handler因该忽略的input设备类型，如果应该忽略的input设备也配对上了，那就出错了   9.    id = input_match_device(handler->id_table, dev);  
10.        //这个是主要的配对函数，主要比较id中的各项，下面详细分析   11.    if (!id)  12.        return -ENODEV;  13.  
14.    error = handler->connect(handler, dev, id);  
15.        //配对成功调用handler的connect函数，这个函数在事件处理器中定义，主要生成一个input_handle结构，并初始化，还生成一个事件处理器相关的设备结构，后面详细分析   16.    if (error && error != -ENODEV)  17.        printk(KERN_ERR  
18.            "input: failed to attach handler %s to device %s, "  19.            "error: %d\n",  20.            handler->name, kobject_name(&dev->dev.kobj), error);  
21.        //出错处理   22.    return error;  23. }  
//    input_attach_handler的主要功能就是调用了两个函数，一个input_match_device进行配对，一个connect处理配对成功后续工作。
//   下面分析input_match_device函数：

 
1.static const struct input_device_id *input_match_device(const struct input_device_id *id,  
2.                            struct input_dev *dev)  3.{  
4.    int i;  5.        //函数传入的参数是所要配对handler的id_table，下面遍历这个id_table寻找合适的id进行配对   6.    for (; id->flags || id->driver_info; id++) {  7.        if (id->flags & INPUT_DEVICE_ID_MATCH_BUS)  8.            if (id->bustype != dev->id.bustype)  9.                continue;  10.                ......  
11.                //针对handler->id->flag，比较不同的类型   12.                //如果比较成功进入下面的宏，否则进入下一个id   13.                MATCH_BIT(evbit,  EV_MAX);  
14.            ......    
15.        MATCH_BIT(swbit,  SW_MAX);  
16.  
17.  
18.        return id;  19.    }  
2/0. }  
//    此函数主要是比较input_dev中的id和handler支持的id,这个存放在handler的id_table中。首先看id->driver_info有没有设置，如果设置了说明它匹配所有的id，evdev就是这个样的handler
//    然后依据id->flag来比较内容，如果都比较成功进入MATCH_BIT，这个宏是用来按位进行比较的，功能是比较所支持事件的类型，只有所有的位都匹配才成功返回，否则进行下一个id的比较。
//
// 
// 1.#define MATCH_BIT(bit, max) \   
// 2.for (i = 0; i < BITS_TO_LONGS(max); i++) \  3.    if ((id->bit[i] & dev->bit[i]) != id->bit[i]) \  4.        break; \  5.if (i != BITS_TO_LONGS(max)) \  6.    continue;      这个宏对于每种事件类型，以及每种事件类型支持的编码所有的位都比较一次，看handler的id是否支持，如果有一个不支持就不会比较成功，进入下一个id进行比较。
//    对于connect函数，每种事件处理器的实现都有差异，但原理都相同，因为触摸屏用的事件处理器为evdev，下面分析evdev的connect函数evdev_connect

 
1.static int evdev_connect(struct input_handler *handler, struct input_dev *dev,  
2.             const struct input_device_id *id)  3.{  
4.        //此函数传入三个参数，分别是：handler，dev,id   5.    struct evdev *evdev;  6.    int minor;  7.    int error;  8.  
9.  
10.    for (minor = 0; minor < EVDEV_MINORS; minor++)  11.        if (!evdev_table[minor])  12.            break;  13.        //EVDEV_MINORS为32，说明evdev这个handler可以同时有32个输入设备和他配对，evdev_table中以minor（非次设备号，但是有一个换算关系）存放evdev结构体，后面要详细分析这个结构体   14.    if (minor == EVDEV_MINORS) {  15.        printk(KERN_ERR "evdev: no more free evdev devices\n");  16.        return -ENFILE;  17.    }  
18.        //这个说明32个位置全都被占用了，连接失败   19.    evdev = kzalloc(sizeof(struct evdev), GFP_KERNEL);  20.        //分配一个evdev结构体，这个结构体是evdev事件处理器特有的，后面会详细分析   21.    if (!evdev)  22.        return -ENOMEM;  23.  
24.  
25.    INIT_LIST_HEAD(&evdev->client_list);  
26.    spin_lock_init(&evdev->client_lock);  
27.    mutex_init(&evdev->mutex);  
28.    init_waitqueue_head(&evdev->wait);  
29.        //初始化结构体的一些成员   30.    dev_set_name(&evdev->dev, "event%d", minor);  31.        //这个是设置evdev中device的名字，他将出现在/class/input中。   32.        //前面也有一个device是input_dev的，名字是input（n），注意与他的不同   33.        //这个结构是配对后的虚拟设备结构，没有对应的硬件，但是通过它可以找到相关的硬件   34.    evdev->exist = 1;  
35.    evdev->minor = minor;  
36.  
37.  
38.    evdev->handle.dev = input_get_device(dev);  
39.    evdev->handle.name = dev_name(&evdev->dev);  
40.    evdev->handle.handler = handler;  
41.    evdev->handle.private = evdev;  42.        //因为evdev中包含handle了，所以初始化它就可以了，这样就连接了input_handler与input_dev   43.    evdev->dev.devt = MKDEV(INPUT_MAJOR, EVDEV_MINOR_BASE + minor); //注意：这个minor不是真正的次设备号，还要加上EVDEV_MINOR_BASE   44.    evdev->dev.class = &input_class;  45.    evdev->dev.parent = &dev->dev;  
46.        //配对生成的device，父设备是与他相关连的input_dev   47.    evdev->dev.release = evdev_free;  
48.    device_initialize(&evdev->dev);  
49.  
50.  
51.    error = input_register_handle(&evdev->handle);  
52.        //注册handle结构体,这个函数后面详细分析   53.    if (error)  54.        goto err_free_evdev;  55.  
56.  
57.    error = evdev_install_chrdev(evdev);  
58.        //这个函数只做了一件事，就是把evdev结构保存到evdev_table中，这个数组也minor为索引   59.    if (error)  60.        goto err_unregister_handle;  61.  
62.  
63.    error = device_add(&evdev->dev);  
64.        //注册到linux设备模型中   65.    if (error)  66.        goto err_cleanup_evdev;  67.  
68.  
69.    return 0;  70.  
71.  
72.  err_cleanup_evdev:  
73.    evdev_cleanup(evdev);  
74.  err_unregister_handle:  
75.    input_unregister_handle(&evdev->handle);  
76.  err_free_evdev:  
77.    put_device(&evdev->dev);  
78.    return error;  79.}  
//    evdev_connect函数做配对后的善后工作，分配一个evdev结构体，并初始化相关成员，evdev结构体中有input_handle结构，初始化并注册之。
// 2. input_register_handle 注册一个input_handle结构体，比较简单

 
1.int input_register_handle(struct input_handle *handle)  
2.{  
3.    struct input_handler *handler = handle->handler;  4.    struct input_dev *dev = handle->dev;  5.    int error;  6.  
7.  
8.    /* 9.     * We take dev->mutex here to prevent race with 
10.     * input_release_device(). 
11.     */  
12.    error = mutex_lock_interruptible(&dev->mutex);  
13.    if (error)  14.        return error;  15.    list_add_tail_rcu(&handle->d_node, &dev->h_list);  
16.        //将handle的d_node，链接到其相关的input_dev的h_list链表中   17.    mutex_unlock(&dev->mutex);  
18.  
19.  
20.    list_add_tail(&handle->h_node, &handler->h_list);  
21.        //将handle的h_node，链接到其相关的input_handler的h_list链表中   22.    if (handler->start)  23.        handler->start(handle);  
24.  
25.  
26.    return 0;  27.}  
//   这个函数基本没做什么事，就是把一个handle结构体通过d_node链表项，分别链接到input_dev的h_list,input_handler的h_list上。以后通过这个h_list就可以遍历相关的input_handle了。
//3. input_register_handler 注册一个input_handler结构体

 
1.int input_register_handler(struct input_handler *handler)  
2. {  
3.    struct input_dev *dev;  4.    int retval;  5.  
6.  
7.    retval = mutex_lock_interruptible(&input_mutex);  
8.    if (retval)  9.        return retval;  10.  
11.  
12.    INIT_LIST_HEAD(&handler->h_list);  
13.  
14.  
15.    if (handler->fops != NULL) {  16.        if (input_table[handler->minor >> 5]) {  17.            retval = -EBUSY;  
18.            goto out;  19.        }  
20.        input_table[handler->minor >> 5] = handler;  
21.    }  
22.        //input_table，每个注册的handler都会将自己保存到这里，索引值为handler->minor右移5为，也就是除以32   23.        //为什么会这样呢，因为每个handler都会处理最大32个input_dev，所以要以minor的32为倍数对齐,这个minor是传进来的handler的MINOR_BASE   24.        //每一个handler都有一个这一个MINOR_BASE，以evdev为例,EVDEV_MINOR_BASE = 64,可以看出系统总共可以注册8个handler   25.    list_add_tail(&handler->node, &input_handler_list);  
26.        //连接到input_handler_list链表中   27.    list_for_each_entry(dev, &input_dev_list, node)  
28.        input_attach_handler(dev, handler);  
29.        //又是配对，不过这次遍历input_dev，和注册input_dev过程一样的   30.    input_wakeup_procfs_readers();  
31.  
32.  
33. out:  
34.    mutex_unlock(&input_mutex);  
35.    return retval;  36.}  
//    这个函数其实和input_register_device大同小异，都是注册，都要配对。
//本篇文章来源于 Linux公社网站(www.linuxidc.com)  原文链接：http://www.linuxidc.com/Linux/2011-09/43187p2.htm
//
//
//一.  输入子系统核心分析。
//
//    1.输入子系统核心对应与/drivers/input/input.c文件,这个也是作为一个模块注册到内核的。所以首先分析模块初始化函数。
//
 
 
1.static int __init input_init(void)  
2.{  
3.    int err;  4.  
5.    input_init_abs_bypass();  
6.        //这个暂时没有发现是做什么的   7.    err = class_register(&input_class);  
8.        //向内核注册一个类，用于linux设备模型。注册后会在/sys/class下面出现input目录   9.    if (err) {  10.        printk(KERN_ERR "input: unable to register input_dev class\n");  11.        return err;  12.    }  
13.  
14.    err = input_proc_init();  
15.        //和proc文件系统有关，暂时不管   16.    if (err)  17.        goto fail1;  18.  
19.  
20.    err = register_chrdev(INPUT_MAJOR, "input", &input_fops);  21.        //注册字符设备，接口是2.4内核的。以主设备号INPUT_MAJOR,次设备号0-255,注册266个设备，说明input设备最大只能有255个   22.    if (err) {  23.        printk(KERN_ERR "input: unable to register char major %d", INPUT_MAJOR);  24.        goto fail2;  25.    }  
26.  
27.    return 0;  28.  
29. fail2: input_proc_exit();  
30. fail1: class_unregister(&input_class);  
3/1.    return err;  32.}    
//    这个函数主要是注册了字符设备，这里和杂项设备的原理是一样，所以input设备也是一类字符设备，只不过操作方法交给了输入子系统。从这里可以看出无论linux设备驱动这块有多复杂，他们都是由一些基本的组件构成的，都是ldd3所讲的基本驱动程序模型。 
//    2. 输入子系统的核心其他部分都是提供的接口，向上连接事件处理层，向下连接驱动层。
//    向下对驱动层的接口主要有：
//    input_allocate_device    这个函数主要是分配一个input_dev接口，并初始化一些基本的成员，这就是我们不能简单用kmalloc分配input_dev结构的原因，因为缺少了一些初始化。
//    input_unregister_device  注册一个input设备
//    input_event              这个函数很重要，是驱动层向input子系统核心报告事件的函数，在事件传递过程中再分析。
//    input_allocate_device    分配并初始化一个input_dev结构
//    向上对事件处理层接口主要有：
//    input_register_handler   注册一个事件处理器
//    input_register_handle    注册一个input_handle结构
//本篇文章来源于 Linux公社网站(www.linuxidc.com)  原文链接：http://www.linuxidc.com/Linux/2011-09/43187p3.htm
//
//
//二.  事件处理层分析（以evdev事件处理器为例）
//    1.事件处理层与用户程序和输入子系统核心打交道，是他们两层的桥梁。一般内核有好几个事件处理器，像evdev mousedev jotdev。evdev事件处理器可以处理所有的事件，触摸屏驱动就是用的这个，所以下面分析这个事件处理器的实现。它也是作为模块注册到内核中的，首先分析它的模块初始化函数。 
//
/
 
1.static int __init evdev_init(void)  
2.{  
3.    return input_register_handler(&evdev_handler);  4.}  
//   模块初始化函数就调用一个注册handler函数，将evdev_handler注册到系统中。
//    2.主要数据结构
//    （1） evdev设备结构
//
 
1.struct evdev {  
2.    int exist;  3.    int open;           //打开标志   4.    int minor;          //次设备号   5.    struct input_handle handle;  //关联的input_handle   6.    wait_queue_head_t wait;      //等待队列，当进程读取设备，而没有事件产生的时候，进程就会睡在其上面   7.    struct evdev_client *grab;   //强制绑定的evdev_client结构，这个结构后面再分析   8.    struct list_head client_list;  //evdev_client 链表，这说明一个evdev设备可以处理多个evdev_client，可以有多个进程访问evdev设备   9.    spinlock_t client_lock; /* protects client_list */  10.    struct mutex mutex;  11.    struct device dev;       //device结构，说明这是一个设备结构   12.};  
//    evdev结构体在配对成功的时候生成，由handler->connect生成，对应设备文件为/class/input/event(n)，如触摸屏驱动的event0，这个设备是用户空间要访问的设备，可以理解它是一个虚拟设备，因为没有对应的硬件，但是通过handle->dev 就可以找到input_dev结构，而它对应着触摸屏，设备文件为/class/input/input0。这个设备结构生成之后保存在evdev_table中，
//    索引值是minor
//   （2） evdev用户端结构

 
1.struct evdev_client {  
2.    struct input_event buffer[EVDEV_BUFFER_SIZE];    3.        //这个是一个input_event数据结构的数组，input_event代表一个事件，基本成员：类型（type），编码（code），值（value）   4.    int head;              //针对buffer数组的索引   5.    int tail;              //针对buffer数组的索引，当head与tail相等的时候，说明没有事件   6.    spinlock_t buffer_lock; /* protects access to buffer, head and tail */  7.    struct fasync_struct *fasync;  //异步通知函数   8.    struct evdev *evdev;           //evdev设备   9.    struct list_head node;         // evdev_client 链表项   10.};  
//   这个结构在进程打开event0设备的时候调用evdev的open方法，在open中创建这个结构，并初始化。在关闭设备文件的时候释放这个结构。
//   3.主要函数
//   （1）evdev设备打开函数

 
1.static int evdev_open(struct inode *inode, struct file *file)  
2.{  
3.    struct evdev *evdev;  4.    struct evdev_client *client;  5.    int i = iminor(inode) - EVDEV_MINOR_BASE;  6.    int error;  7.  
8.  
9.    if (i >= EVDEV_MINORS)  10.        return -ENODEV;  11.  
12.  
13.    error = mutex_lock_interruptible(&evdev_table_mutex);  
14.    if (error)  15.        return error;  16.    evdev = evdev_table[i];  
17.        //得到evdev设备结构,每次调用evdev_connect配对成功后都会把分配的evdev结构以minor为索引，保存在evdev_table数组中   18.    if (evdev)  19.        get_device(&evdev->dev);  //增加device引用计数   20.    mutex_unlock(&evdev_table_mutex);  
21.  
22.  
23.    if (!evdev)  24.        return -ENODEV;  25.  
26.  
27.    client = kzalloc(sizeof(struct evdev_client), GFP_KERNEL);  //分配用户端结构   28.    if (!client) {  29.        error = -ENOMEM;  
30.        goto err_put_evdev;  31.    }  
32.  
33.  
34.    spin_lock_init(&client->buffer_lock);  
35.    client->evdev = evdev;    //使用户端与evdev设备结构联系起来   36.    evdev_attach_client(evdev, client);  
37.        //这个函数所做的就是把client连接到evdev的client链表中   38.    error = evdev_open_device(evdev);  
39.        //这个函数打开设备，有很多层调用，后面详细分析   40.    if (error)  41.        goto err_free_client;  42.  
43.  
44.    file->private_data = client;  
45.    return 0;  46.  
47.  
48. err_free_client:  
49.    evdev_detach_client(evdev, client);  
50.    kfree(client);  
51. err_put_evdev:  
52.    put_device(&evdev->dev);  
/53.    return error;  54.}   
//   （2）evdev设备打开函数evdev_open_device，由evdev_open调用。

 
1.static int evdev_open_device(struct evdev *evdev)  
2.{  
3.    int retval;  4.  
5.  
6.    retval = mutex_lock_interruptible(&evdev->mutex);  
7.    if (retval)  8.        return retval;  9.  
10.  
11.    if (!evdev->exist)  12.        retval = -ENODEV;  
13.        //判断设备结构是否存在，在evdev_connect中初始话此成员为1   14.    else if (!evdev->open++) {  15.        retval = input_open_device(&evdev->handle);  
16.        if (retval)  17.            evdev->open--;  
18.    }  
19.        //evdev->open分配结构的时候没有初始化，默认为0，也就是没有打开，每次打开都会加1   20.    mutex_unlock(&evdev->mutex);  
21.    return retval;  22.}  
 //   此函数在判断结构存在与否后，主要调用了input_open_device，这个函数是子系统核心函数，定义在input.c中，下面分析这个函数：

 
1.int input_open_device(struct input_handle *handle)  
2.{  
3.    struct input_dev *dev = handle->dev;  4.    int retval;  5.  
6.  
7.    retval = mutex_lock_interruptible(&dev->mutex);  
8.    if (retval)  9.        return retval;  10.  
11.  
12.    if (dev->going_away) {  13.        retval = -ENODEV;  
14.        goto out;  15.    }  
16.  
17.  
18.    handle->open++;  
19.        //将handle的打开计数加1，注意和evdev的open的区别   20.    if (!dev->users++ && dev->open)  21.        retval = dev->open(dev);  
22.        //如果此input_dev没有进程在引用，并且定义了open方法，就调用open方法   23.    if (retval) {    //retval = 1 说明没有打开成功   24.        dev->users--;    
25.        if (!--handle->open) {  //说明有其他的进程已经打开了这个handle   26.            /* 27.             * Make sure we are not delivering any more events 
28.             * through this handle 
29.             */  
30.            synchronize_rcu();  
31.        }  
32.    }  
33.  
34.  
35. out:  
36.    mutex_unlock(&dev->mutex);  
37.    return retval;  38.}  
   （3）读操作函数 evdev_read

 
1.static ssize_t evdev_read(struct file *file, char __user *buffer,  
2.              size_t count, loff_t *ppos)  3.{  
4.    struct evdev_client *client = file->private_data;    //这个客户端结构在打开的时候分配并保存在file->private_data中   5.    struct evdev *evdev = client->evdev;  6.    struct input_event event;  7.    int retval;  8.  
9.  
10.    if (count < input_event_size())  11.        return -EINVAL;  12.        //这条语句提示，用户进程每次读取设备的字节数，不要少于input_event结构的大小   13.    if (client->head == client->tail && evdev->exist &&  14.        (file->f_flags & O_NONBLOCK))  
15.        return -EAGAIN;  16.        //head等于tail说明目前还没有事件传回来，如果设置了非阻塞操作，则会立刻返回   17.    retval = wait_event_interruptible(evdev->wait,  
18.        client->head != client->tail || !evdev->exist);  
19.        //没有事件就会睡在evdev的等待队列上了，等待条件是有事件到来或者设备不存在了（设备关闭的时候，清这个标志）   20.    if (retval)  21.        return retval;  22.        //如果能执行上面这条语句说明有事件传来或者，设备被关闭了，或者内核发过来终止信号   23.    if (!evdev->exist)  24.        return -ENODEV;  25.  
26.  
27.    while (retval + input_event_size() <= count &&  28.           evdev_fetch_next_event(client, &event)) {  
29.        // evdev_fetch_next_event这个函数遍历client里面的input_event buffer数组   30.        if (input_event_to_user(buffer + retval, &event))  31.        //将事件复制到用户空间   32.            return -EFAULT;  33.  
34.  
35.        retval += input_event_size();  
36.    }  
37.  
38.    return retval;   //返回复制的数据字节数   39.}  




//三. 事件传递过程（以s3c2410_ts为例）
//   1. 事件产生
//    当按下触摸屏时，进入触摸屏按下中断，开始ad转换，ad转换完成进入ad完成中断，在这个终端中将事件发送出去，调用
//    input_report_abs(dev, ABS_X, xp); 
//
//    input_report_abs(dev, ABS_Y, yp); 这两个函数调用了 input_event(dev, EV_ABS, code, value)
//    所有的事件报告函数都调用这个函数。
//   2. 事件报告
//   （1） input_event 函数分析，这个函数定义在input.c中

 
1.void input_event(struct input_dev *dev,  
2.         unsigned int type, unsigned int code, int value)  3.{  
4.    unsigned long flags;  5.  
6.  
7.    if (is_event_supported(type, dev->evbit, EV_MAX)) {  8.        //判断是否支持此种事件类型和事件类型中的编码类型   9.        spin_lock_irqsave(&dev->event_lock, flags);  
10.        add_input_randomness(type, code, value);  
11.        //对系统随机熵池有贡献，因为这个也是一个随机过程   12.        input_handle_event(dev, type, code, value);  
13.        //这个函数是事件处理的关键函数，下面详细分析   14.        spin_unlock_irqrestore(&dev->event_lock, flags);  
15.    }  
16.}   
   （2） input_handle_event 函数分析，这个函数定义在input.c中

 
1.static void input_handle_event(struct input_dev *dev,  
2.                   unsigned int type, unsigned int code, int value)  3.{  
4.    int disposition = INPUT_IGNORE_EVENT;  5.  
6.  
7.    switch (type) {  8.        ......  
9.    case EV_KEY:  10.        if (is_event_supported(code, dev->keybit, KEY_MAX) &&  11.            !!test_bit(code, dev->key) != value) {  
12.  
13.  
14.            if (value != 2) {  15.                __change_bit(code, dev->key);  
16.                if (value)  17.                    input_start_autorepeat(dev, code);  
18.                else  19.                    input_stop_autorepeat(dev);  
20.            }  
21.            disposition = INPUT_PASS_TO_HANDLERS;  
22.        }  
23.        break;  24.        ......  
25.    if (disposition != INPUT_IGNORE_EVENT && type != EV_SYN)  26.        dev->sync = 0;  
27.  
28.  
29.    if ((disposition & INPUT_PASS_TO_DEVICE) && dev->event)  30.        dev->event(dev, type, code, value);  
31.  
32.  
33.    if (disposition & INPUT_PASS_TO_HANDLERS)  34.        input_pass_event(dev, type, code, value);  
35.}  
//   这个函数主要是根据事件类型的不同，做相应的处理。这里之关心EV_KEY类型，其他函数和事件传递关系不大，只要关心，disposition这个是事件处理的方式，默认的是INPUT_IGNORE_EVENT，忽略这个事件，如果是INPUT_PASS_TO_HANDLERS则是传递给事件处理器，如果是INPUT_PASS_TO_DEVICE，则是传递给设备处理，触摸屏驱动没有定义这个。下面分析input_pass_event函数。

 
1.static void input_pass_event(struct input_dev *dev,  
2.                 unsigned int type, unsigned int code, int value)  3.{  
4.    struct input_handle *handle;  5.  
6.  
7.    rcu_read_lock();  
8.  
9.  
10.    handle = rcu_dereference(dev->grab);  //如果是绑定的handle，则调用绑定的handler->event函数   11.    if (handle)  12.        handle->handler->event(handle, type, code, value);  
13.    else  14.        //如果没有绑定，则遍历dev的h_list链表，寻找handle，如果handle已经打开，说明有进程读取设备关联的evdev。   15.        list_for_each_entry_rcu(handle, &dev->h_list, d_node)  
16.            if (handle->open)  17.                handle->handler->event(handle,  
18.                            type, code, value);  
19.        // 调用相关的事件处理器的event函数，进行事件的处理   20.    rcu_read_unlock();  
21.}  
//下面分析 evdev事件处理器的event函数

 
1.static void evdev_event(struct input_handle *handle,  
2.            unsigned int type, unsigned int code, int value)  3.{  
4.    struct evdev *evdev = handle->private;  5.    struct evdev_client *client;  6.    struct input_event event;  7.  
8.  
9.    do_gettimeofday(&event.time);  
10.    event.type = type;  
11.    event.code = code;  
12.    event.value = value;  
13.        //将传过来的事件，赋值给input_event结构   14.    rcu_read_lock();  
15.  
16.  
17.    client = rcu_dereference(evdev->grab);  
18.        //如果evdev绑定了client那么，处理这个客户端，触摸屏驱动没有绑定   19.    if (client)  20.        evdev_pass_event(client, &event);  
21.    else  22.        //遍历client链表，调用evdev_pass_event函数   23.        list_for_each_entry_rcu(client, &evdev->client_list, node)  
24.            evdev_pass_event(client, &event);  
25.  
26.  
27.    rcu_read_unlock();  
28.  
29.  
30.    wake_up_interruptible(&evdev->wait); //唤醒等待的进程   31.}  
//下面分析 evdev_pass_event 函数

 
1.static void evdev_pass_event(struct evdev_client *client,  
2.                 struct input_event *event)  3.{  
4.    /* 5.     * Interrupts are disabled, just acquire the lock 
6.     */  
7.    spin_lock(&client->buffer_lock);  
8.    client->buffer[client->head++] = *event;   //将事件赋值给客户端的input_event 数组   9.    client->head &= EVDEV_BUFFER_SIZE - 1;  
10.    spin_unlock(&client->buffer_lock);  
11.  
12.  
13.    kill_fasync(&client->fasync, SIGIO, POLL_IN);  
14.}  
//可以看出， evdev_pass_event函数最终将事件传递给了用户端的client结构中的input_event数组中，只需将这个input_event数组复制给用户空间，进程就能收到触摸屏按下的信息了。具体处理由具体的应用程序来完成。
//本篇文章来源于 Linux公社网站(www.linuxidc.com)  原文链接：http://www.linuxidc.com/Linux/2011-09/43187p5.htm