// Linux输入子系统(Input Subsystem)
// 
// 
// 1.1.input子系统概述
// 
// 
// 输入设备(如按键,键盘，触摸屏，鼠标等)是典型的字符设备，其一般的工作机制是低层在按键，触摸等动作发生时产生一个中断(或驱动通过timer定时查询)，然后cpu通过SPI，I2C或者外部存储器总线读取键值，坐标等数据，放一个缓冲区，字符设备驱动管理该缓冲区，而驱动的read()接口让用户可以读取键值，坐标等数据。
// 
// 
// 在Linux中，输入子系统是由输入子系统设备驱动层、输入子系统核心层(Input Core)和输入子系统事件处理层(Event Handler)组成。其中设备驱动层提供对硬件各寄存器的读写访问和将底层硬件对用户输入访问的响应转换为标准的输入事件，再通过核心层提交给事件处理层；而核心层对下提供了设备驱动层的编程接口，对上又提供了事件处理层的编程接口；而事件处理层就为我们用户空间的应用程序提供了统一访问设备的接口和驱动层提交来的事件处理。所以这使得我们输入设备的驱动部分不在用关心对设备文件的操作，而是要关心对各硬件寄存器的操作和提交的输入事件。
// 
// 1.2. input子系统结构图
// 
// 
// input子系统结构图如下图1所示：
// 
// 
// 
// 图1 输入子系统结构图
// 
// 
// 1.3.linux中输入设备驱动的分层
// 
// 
// linux中输入设备驱动的分层如下图2所示：
// 
// 
//  
// 
// 图2 linux中输入设备的分层
// 
// 
// 1.4. 输入子系统设备驱动层实现原理
// 
// 
// 在Linux中，Input设备用input_dev结构体描述，定义在input.h中。设备的驱动只需按照如下步骤就可实现了。 
// 1).在驱动模块加载函数中设置Input设备支持input子系统的哪些事件； 
// 2).将Input设备注册到input子系统中； 
// 3).在Input设备发生输入操作时(如：键盘被按下/抬起、触摸屏被触摸/抬起/移动、鼠标被移动/单击/抬起时等)，提交所发生的事件及对应的键值/坐标等状态。
// 
// 1.5.软件设计流程
// 
// 
// 软件设计流程如下图3所示
// 
// 
// 
// 图 3 input子系统软件设计流程
// 
// 
// 1.6.与软件设计有关的API函数
// 
// 
// 
// 
// 1.6.1.分配一个输入设备
// 
// 
// Struct input_dev *input_allocate_device*(void); 
// 
// 
// 1.6.2.注册一个输入设备
// 
// 
// Int input_register_device(struct input_dev *dev);
// 
// 
// 1.6.3.驱动实现-事件支持
// 
// 
// Set_bit告诉inout子系统它支持哪些事件 
// Set_bit(EV_KEY,button_dev.evbit) 
// Struct input_dev中有两个成员，一个是evbit;一个是keybit.分别用来表示设备所支持的事件类型和按键类型。
// 
// 
// 1.6.3.1事件类型
// 
// 
// Linux中输入设备的事件类型有(这里只列出了常用的一些，更多请看linux/input.h中)：EV_SYN 0x00 同步事件 
// EV_KEY 0x01 按键事件 
// EV_REL 0x02 相对坐标 
// EV_ABS 0x03 绝对坐标 
// EV_MSC 0x04 其它 
// EV_LED 0x11 LED 
// EV_SND 0x12 声音 
// EV_REP 0x14 Repeat 
// EV_FF 0x15 力反馈
// 
// 
// 1.6.4.驱动实现-报告事件
// 
// 
// Void input_event(struct input_dev *dev,unsigned int type,unsigned int code,int value);//报告指定type,code的输入事件 
// Void input_report_key(struct input_dev *dev,unsigned int code,int value);//报告键值 
// Void input_report_rel(struct input_dev *dev,unsigned int code,int value);//报告相对坐标 
// Void input_report_abs(struct input_dev *dev,unsigned int code,int value);//报告绝对坐标 
// Void input_sync(struct input_dev *dev);//报告同步事件 
// 在触摸屏驱动设计中，一次坐标及按下状态的整个报告过程如下： 
// Input_report_abs(input_dev,ABS_X,x);//X坐标 
// Input_report_abs(input_dev,ABS_Y,y);//Y坐标 
// Input_report_abs(input_dev,ABS_PRESSURE,pres);//压力 
// input_sync(struct input_dev *dev);//同步 
// 
// 
// 1.6.5释放与注销设备
// 
// 
// Void input_free_device(struct input_dev *dev); 
// Void input_unregister_device(struct input_dev *); 
// 
// ===============================================================================
// 
// linux内核input子系统解析 .
// 2010-06-18 22:58 12720人阅读 评论(18) 收藏 举报 
// 作者：刘洪涛,华清远见嵌入式学院讲师。    
// 
//     Android、X windows、qt等众多应用对于linux系统中键盘、鼠标、触摸屏等输入设备的支持都通过、或越来越倾向于标准的input输入子系统。
// 
//     因为input子系统已经完成了字符驱动的文件操作接口，所以编写驱动的核心工作是完成input系统留出的接口，工作量不大。但如果你想更灵活的应用它，就需要好好的分析下input子系统了。
// 
// 一、input输入子系统框架
// 
//     下图是input输入子系统框架，输入子系统由输入子系统核心层（ Input Core ），驱动层和事件处理层（Event Handler）三部份组成。一个输入事件，如鼠标移动，键盘按键按下，joystick的移动等等通过 input driver -> Input core -> Event handler -> userspace 到达用户空间传给应用程序。
// 
//  
// 
//  
// 
// 注意：keyboard.c不会在/dev/input下产生节点，而是作为ttyn终端（不包括串口终端）的输入。
// 
//  
// 
// 二、Input driver编写要点
// 
// 1、分配、注册、注销input设备

struct input_dev *input_allocate_device(void)

int input_register_device(struct input_dev *dev)

void input_unregister_device(struct input_dev *dev)

 

// 2、设置input设备支持的事件类型、事件码、事件值的范围、input_id等信息
// 
// 参见usb键盘驱动：usbkbd.c
// 
usb_to_input_id(dev, &input_dev->id);//设置bustype、vendo、product等

input_dev->evbit[0] = BIT(EV_KEY) | BIT(EV_LED) | BIT(EV_REP);//支持的事件类型

input_dev->ledbit[0] = BIT(LED_NUML) | BIT(LED_CAPSL) | BIT(LED_SCROLLL) | BIT(LED_COMPOSE) | BIT(LED_KANA);// EV_LED事件支持的事件码

for (i = 0; i < 255; i++)

    set_bit(usb_kbd_keycode[i], input_dev->keybit); //EV_KEY事件支持的事件码

// include/linux/input.h中定义了支持的类型（下面列出的是2.6.22内核的情况）
// 
#define EV_SYN          0x00

#define EV_KEY          0x01

#define EV_REL          0x02

#define EV_ABS          0x03

#define EV_MSC          0x04

#define EV_SW           0x05

#define EV_LED          0x11

#define EV_SND          0x12

#define EV_REP          0x14

#define EV_FF           0x15

#define EV_PWR          0x16

#define EV_FF_STATUS        0x17

#define EV_MAX          0x1f
// 
// 一个设备可以支持一个或多个事件类型。每个事件类型下面还需要设置具体的触发事件码。比如：EV_KEY事件，需要定义其支持哪些按键事件码。
// 
//  
// 
//  
// 
// 3、如果需要，设置input设备的打开、关闭、写入数据时的处理方法
// 
// 参见usb键盘驱动：usbkbd.c

    input_dev->open = usb_kbd_open;

    input_dev->close = usb_kbd_close;

    input_dev->event = usb_kbd_event;
 /
//4、在发生输入事件时，向子系统报告事件
//
//用于报告EV_KEY、EV_REL、EV_ABS等事件的函数有：
/
void input_report_key(struct input_dev *dev, unsigned int code, int value)

    void input_report_rel(struct input_dev *dev, unsigned int code, int value)

    void input_report_abs(struct input_dev *dev, unsigned int code, int value)
 /
//    如果你觉得麻烦，你也可以只记住1个函数（因为上述函数都是通过它实现的）
/
void input_event(struct input_dev *dev, unsigned int type, unsigned int code, int value)

 

 

//三、Event Handler层解析
//
// 1、Input输入子系统数据结构关系图



 

 

// 2、input_handler结构体

以evdev.c中的evdev_handler为例：

static struct input_handler evdev_handler = {

    .event =    evdev_event, //向系统报告input事件，系统通过read方法读取

    .connect =  evdev_connect, //和input_dev匹配后调用connect构建

    .disconnect =   evdev_disconnect,

    .fops =     &evdev_fops,  //event设备文件的操作方法

    .minor =    EVDEV_MINOR_BASE,  //次设备号基准值

    .name =     "evdev",

    .id_table = evdev_ids,  //匹配规则

};

 

// 3、input字符设备注册过程

drivers/input/input.c中：

static int __init input_init(void)

{

    int err;

    err = class_register(&input_class);

……

    err = register_chrdev(INPUT_MAJOR, "input", &input_fops);

    ……

}

input_fops定义：

static const struct file_operations input_fops = {

    .owner = THIS_MODULE,

    .open = input_open_file,

};

 

Input_dev和input_handler匹配后调用input_handler的connect。以evdev_handler为例：

static int evdev_connect(struct input_handler *handler, struct input_dev *dev,

             const struct input_device_id *id)

{

    struct evdev *evdev;  

    struct class_device *cdev;

    dev_t devt;

    int minor;

    int error;

 

    for (minor = 0; minor < EVDEV_MINORS && evdev_table[minor]; minor++);

    if (minor == EVDEV_MINORS) {

        printk(KERN_ERR "evdev: no more free evdev devices/n");

        return -ENFILE;

    }

 

    evdev = kzalloc(sizeof(struct evdev), GFP_KERNEL);//为每个匹配evdev_handler的设备创建一个evdev。

    if (!evdev)

        return -ENOMEM;

 

    INIT_LIST_HEAD(&evdev->client_list);

    init_waitqueue_head(&evdev->wait); 

 

    evdev->exist = 1;

    evdev->minor = minor;

    evdev->handle.dev = dev;

    evdev->handle.name = evdev->name;

    evdev->handle.handler = handler;

    evdev->handle.private = evdev;

    sprintf(evdev->name, "event%d", minor);

 

    evdev_table[minor] = evdev;//记录evdev的位置，字符设备/dev/input/evnetx访问时根据次设备号及EVDEV_MINOR_BASE最终在evdev_open中找到对应的evdev

    devt = MKDEV(INPUT_MAJOR, EVDEV_MINOR_BASE + minor),

    cdev = class_device_create(&input_class, &dev->cdev, devt,

                 dev->cdev.dev, evdev->name);//创建了event字符设备节点

    ……

}

 

// 4、input字符设备的打开过程

static int input_open_file(struct inode *inode, struct file *file)

{

struct input_handler *handler = input_table[iminor(inode) >> 5];

//得到对应的input_handler

    const struct file_operations *old_fops, *new_fops = NULL;

    int err;

    if (!handler || !(new_fops = fops_get(handler->fops)))

//取出对应input_handler的file_operations

        return -ENODEV;

    if (!new_fops->open) {

        fops_put(new_fops);

        return -ENODEV;

    }

    old_fops = file->f_op;

    file->f_op = new_fops;//重定位打开的设备文件的操作方法

    err = new_fops->open(inode, file);

    if (err) {

        fops_put(file->f_op);

        file->f_op = fops_get(old_fops);

    }

    fops_put(old_fops);

    return err;

}

//5、input字符设备的其它操作

//    由于在open阶段已经把设备文件的操作操作方法重定位了到了具体的input_handler，所以其它接口操作（read、write、ioctl等），由各个input_handler的fops方法决定。如evdev.c中的：evdev_fops


==================================================================================================

 /
//Linux输入(input)子系统 (2009-01-06 23:38) 
//分类： linux驱动 
//
//
//
//###############################################################################################
//早前曾研究了一下输入子系统的原理,给人的感觉是输入子系统很复杂.但其实内核开发者在这方面已经做得很完善了,
//输入子系统虽然错综复杂,但是只要我们领会了输入子系统的一些设计思想后,我们要使用它并非难事.
//
//以下以内核自带的gpio_keys驱动为例,介绍输入子系统的使用.
//主要的原因是gpio_keys驱动比较简单易懂,另外不是没个人都有触摸屏,但键盘的话相信每一块开发板上都配有吧^_^
//
//按照以前的习惯,先从下到上的研究底层驱动是如何提交输入事件的:
//###############################################################################################
/
drivers/input/keyboard/gpio_keys.c:

static int __devinit gpio_keys_probe(struct platform_device *pdev)
{
    struct gpio_keys_platform_data *pdata = pdev->dev.platform_data;
    struct input_dev *input;
    int i, error;

    input = input_allocate_device();//申请input_dev结构
    if (!input)
        return -ENOMEM;

    platform_set_drvdata(pdev, input);//把input_dev结构放好(以后方便调用)

    input->evbit[0] = BIT(EV_KEY);//目前event的类型不操作32,所以你会看到对于evbit数组的操作都是对evbit[0]中的位来进行操作.

    input->name = pdev->name;
    input->phys = "gpio-keys/input0";
    input->dev.parent = &pdev->dev;

    input->id.bustype = BUS_HOST;
    input->id.vendor = 0x0001;
    input->id.product = 0x0001;
    input->id.version = 0x0100;

    for (i = 0; i < pdata->nbuttons; i++) {
        struct gpio_keys_button *button = &pdata->buttons[i];
        int irq = gpio_to_irq(button->gpio);
        unsigned int type = button->type ?: EV_KEY;

        set_irq_type(irq, IRQ_TYPE_EDGE_BOTH);

        /* 根据用户所指定的gpio_keys来申请中断和注册中断处理函数*/
        error = request_irq(irq, gpio_keys_isr, IRQF_SAMPLE_RANDOM,
                     button->desc ? button->desc : "gpio_keys",
                     pdev);
        if (error) {
            printk(KERN_ERR "gpio-keys: unable to claim irq %d; error %d\n",
                irq, error);
            goto fail;
        }

        input_set_capability(input, type, button->code);
    }

    error = input_register_device(input);//注册输入设备,并和对应的handler处理函数挂钩
    if (error) {
        printk(KERN_ERR "Unable to register gpio-keys input device\n");
        goto fail;
    }

    return 0;

 fail:
    for (i = i - 1; i >= 0; i--)
        free_irq(gpio_to_irq(pdata->buttons[i].gpio), pdev);

    input_free_device(input);

    return error;
}


//提到input_dev结构,以下谈一下我对于它的理解:
struct input_dev {

    void *private;

    const char *name;
    const char *phys;
    const char *uniq;
    struct input_id id;

    /*
     * 根据各种输入信号的类型来建立类型为unsigned long 的数组,
     * 数组的每1bit代表一种信号类型,
     * 内核中会对其进行置位或清位操作来表示时间的发生和被处理.
     */

    unsigned long evbit[NBITS(EV_MAX)];
    unsigned long keybit[NBITS(KEY_MAX)];
    unsigned long relbit[NBITS(REL_MAX)];
    unsigned long absbit[NBITS(ABS_MAX)];
    unsigned long mscbit[NBITS(MSC_MAX)];
    unsigned long ledbit[NBITS(LED_MAX)];
    unsigned long sndbit[NBITS(SND_MAX)];
    unsigned long ffbit[NBITS(FF_MAX)];
    unsigned long swbit[NBITS(SW_MAX)];

    .........................................
};

/**
 * input_set_capability - mark device as capable of a certain event
 * @dev: device that is capable of emitting or accepting event
 * @type: type of the event (EV_KEY, EV_REL, etc...)
 * @code: event code
 *
 * In addition to setting up corresponding bit in appropriate capability
 * bitmap the function also adjusts dev->evbit.
 */

/* 记录本设备对于哪些事件感兴趣(对其进行处理)*/
void input_set_capability(struct input_dev *dev, unsigned int type, unsigned int code)
{
    switch (type) {
    case EV_KEY:
        __set_bit(code, dev->keybit);//比如按键,应该对哪些键值的按键进行处理(对于其它按键不予理睬)
        break;

    case EV_REL:
        __set_bit(code, dev->relbit);
        break;

    case EV_ABS:
        __set_bit(code, dev->absbit);
        break;

    case EV_MSC:
        __set_bit(code, dev->mscbit);
        break;

    case EV_SW:
        __set_bit(code, dev->swbit);
        break;

    case EV_LED:
        __set_bit(code, dev->ledbit);
        break;

    case EV_SND:
        __set_bit(code, dev->sndbit);
        break;

    case EV_FF:
        __set_bit(code, dev->ffbit);
        break;

    default:
        printk(KERN_ERR
            "input_set_capability: unknown type %u (code %u)\n",
            type, code);
        dump_stack();
        return;
    }

    __set_bit(type, dev->evbit);//感觉和前面重复了(前面一经配置过一次了)
}
//EXPORT_SYMBOL(input_set_capability);


static irqreturn_t gpio_keys_isr(int irq, void *dev_id)
{
        int i;
        struct platform_device *pdev = dev_id;
        struct gpio_keys_platform_data *pdata = pdev->dev.platform_data;
        struct input_dev *input = platform_get_drvdata(pdev);

        for (i = 0; i < pdata->nbuttons; i++) {
                struct gpio_keys_button *button = &pdata->buttons[i];
                int gpio = button->gpio;

                if (irq == gpio_to_irq(gpio)) {//判断哪个键被按了?
                        unsigned int type = button->type ?: EV_KEY;
                        int state = (gpio_get_value(gpio) ? 1 : 0) ^ button->active_low;//记录按键状态

                        input_event(input, type, button->code, !!state);//汇报输入事件
                        input_sync(input);//等待输入事件处理完成
                }
        }

        return IRQ_HANDLED;
}


/*
 * input_event() - report new input event
 * @dev: device that generated the event
 * @type: type of the event
 * @code: event code
 * @value: value of the event
 *
 * This function should be used by drivers implementing various input devices
 * See also input_inject_event()
 */
void input_event(struct input_dev *dev, unsigned int type, unsigned int code, int value)
{
    struct input_handle *handle;

    if (type > EV_MAX || !test_bit(type, dev->evbit))//首先判断该事件类型是否有效且为该设备所接受
        return;

    add_input_randomness(type, code, value);

    switch (type) {

        case EV_SYN:
            switch (code) {
                case SYN_CONFIG:
                    if (dev->event)
                        dev->event(dev, type, code, value);
                    break;

                case SYN_REPORT:
                    if (dev->sync)
                        return;
                    dev->sync = 1;
                    break;
            }
            break;

        case EV_KEY:
            /*
             * 这里需要满足几个条件:
             * 1: 键值有效(不超出定义的键值的有效范围)
             * 2: 键值为设备所能接受(属于该设备所拥有的键值范围)
             * 3: 按键状态改变了
             */

            if (code > KEY_MAX || !test_bit(code, dev->keybit) || !!test_bit(code, dev->key) == value)
                return;

            if (value == 2)
                break;

            change_bit(code, dev->key);//改变对应按键的状态

            /* 如果你希望按键未释放的时候不断汇报按键事件的话需要以下这个(在简单的gpio_keys驱动中不需要这个,暂时不去分析) */
            if (test_bit(EV_REP, dev->evbit) && dev->rep[REP_PERIOD] && dev->rep[REP_DELAY] && dev->timer.data && value) {
                dev->repeat_key = code;
                mod_timer(&dev->timer, jiffies + msecs_to_jiffies(dev->rep[REP_DELAY]));
            }

            break;
........................................................

    if (type != EV_SYN)
        dev->sync = 0;

    if (dev->grab)
        dev->grab->handler->event(dev->grab, type, code, value);
    else
        /*
         * 循环调用所有处理该设备的handle(event,mouse,ts,joy等),
         * 如果有进程打开了这些handle(进行读写),则调用其对应的event接口向气汇报该输入事件.
         */
        list_for_each_entry(handle, &dev->h_list, d_node)
            if (handle->open)
                handle->handler->event(handle, type, code, value);
}
//EXPORT_SYMBOL(input_event);
 /
//
//#########################################################################
//好了,下面再来研究一下event层对于input层报告的这个键盘输入事件是如何来处理的.
//#########################################################################
/
drivers/input/evdev.c:

static struct input_handler evdev_handler = {
        .event =        evdev_event,
        .connect =      evdev_connect,
        .disconnect =   evdev_disconnect,
        .fops =         &evdev_fops,
        .minor =        EVDEV_MINOR_BASE,
        .name =         "evdev",
        .id_table =     evdev_ids,
};

static void evdev_event(struct input_handle *handle, unsigned int type, unsigned int code, int value)
{
        struct evdev *evdev = handle->private;
        struct evdev_client *client;

        if (evdev->grab) {
                client = evdev->grab;

                do_gettimeofday(&client->buffer[client->head].time);
                client->buffer[client->head].type = type;
                client->buffer[client->head].code = code;
                client->buffer[client->head].value = value;
                client->head = (client->head + 1) & (EVDEV_BUFFER_SIZE - 1);

                kill_fasync(&client->fasync, SIGIO, POLL_IN);
        } else
                  /* 遍厉client_list链表中的client结构(代表些打开evdev的进程(个人理解^_^)) */
                list_for_each_entry(client, &evdev->client_list, node) {
                            /* 填充代表该输入信号的struct input_event结构(事件,类型,键码,键值) */
                        do_gettimeofday(&client->buffer[client->head].time);
                        client->buffer[client->head].type = type;
                        client->buffer[client->head].code = code;
                        client->buffer[client->head].value = value;
                            /* 更新写指针 */
                        client->head = (client->head + 1) & (EVDEV_BUFFER_SIZE - 1);

                        kill_fasync(&client->fasync, SIGIO, POLL_IN);//通知调用input_sync的进程:输入事件经已处理完毕(通知底层).
                }

        wake_up_interruptible(&evdev->wait);//唤醒睡眠在evdev->wait等待队列等待输入信息的进程(通知上层).
}
 /
//###################################################################################
//好了,至此一个按键的输入事件处理完毕,现在再来从上到上的来看看用户是如何获取这个输入事件的.
//###################################################################################
/

static const struct file_operations evdev_fops = {
        .owner =        THIS_MODULE,
        .read =         evdev_read,
        .write =        evdev_write,
        .poll =         evdev_poll,
        .open =         evdev_open,
        .release =      evdev_release,
        .unlocked_ioctl = evdev_ioctl,
#ifdef CONFIG_COMPAT
        .compat_ioctl = evdev_ioctl_compat,
#endif
        .fasync =       evdev_fasync,
        .flush =        evdev_flush
};


static int evdev_open(struct inode *inode, struct file *file)
{
        struct evdev_client *client;
        struct evdev *evdev;
        int i = iminor(inode) - EVDEV_MINOR_BASE;
        int error;

        if (i >= EVDEV_MINORS)
                return -ENODEV;

        evdev = evdev_table[i];

        if (!evdev || !evdev->exist)
                return -ENODEV;

        client = kzalloc(sizeof(struct evdev_client), GFP_KERNEL);
        if (!client)
                return -ENOMEM;

        client->evdev = evdev;
         /* 添加evdev_client结构到链表evdev->client_list中(好让输入事件到来的时候填写该结构并唤醒进程读取) */
        list_add_tail(&client->node, &evdev->client_list);

        if (!evdev->open++ && evdev->exist) {
                error = input_open_device(&evdev->handle);
                if (error) {
                        list_del(&client->node);
                        kfree(client);
                        return error;
                }
        }

        file->private_data = client;//存放好evdev_client结构方便以后使用
        return 0;
}


static ssize_t evdev_read(struct file *file, char __user *buffer, size_t count, loff_t *ppos)
{
        struct evdev_client *client = file->private_data;
        struct evdev *evdev = client->evdev;
        int retval;

        if (count < evdev_event_size())//对于每次读取的数据大小是有一定的要求.
                return -EINVAL;

        if (client->head == client->tail && evdev->exist && (file->f_flags & O_NONBLOCK))//缓存中没有数据可读且设备是存在的,
                                                      //如果设置为NONBLOCK方式来读,立即返回.
                return -EAGAIN;

        retval = wait_event_interruptible(evdev->wait,
                client->head != client->tail || !evdev->exist);//否则等待缓存有数据可读或设备不存在(被移去)
        if (retval)
                return retval;

        if (!evdev->exist)
                return -ENODEV;

        while (client->head != client->tail && retval + evdev_event_size() <= count) {//下面开始读取数据

                struct input_event *event = (struct input_event *) client->buffer + client->tail;//获取缓存中的读指针

                if (evdev_event_to_user(buffer + retval, event))//返回数据给用户
                        return -EFAULT;

                client->tail = (client->tail + 1) & (EVDEV_BUFFER_SIZE - 1);//更新读指针
                retval += evdev_event_size();
        }

        return retval;
}
 /
//呵呵,看到了吧,应用程序就是这样获取输入事件的^_^
//
//##########################################################################################################
//本来对于gpio_keys这样的驱动程序,只要当发生按键事件的时候向上层应用程序汇报键值即可.
//不过,对于一些带输出设备(例如led灯)的输入设备来说(例如键盘),上层应用程序同样可以利用event层来读取或改变其状态.
//请看以下代码:
//##########################################################################################################
/
static ssize_t evdev_write(struct file *file, const char __user *buffer, size_t count, loff_t *ppos)
{
        struct evdev_client *client = file->private_data;
        struct evdev *evdev = client->evdev;
        struct input_event event;
        int retval = 0;

        if (!evdev->exist)
                return -ENODEV;

        while (retval < count) {

                if (evdev_event_from_user(buffer + retval, &event))//从用户处获取事件结构
                        return -EFAULT;
                input_inject_event(&evdev->handle, event.type, event.code, event.value);//往底层发送事件
                retval += evdev_event_size();
        }

        return retval;
}


/**
 * input_inject_event() - send input event from input handler
 * @handle: input handle to send event through
 * @type: type of the event
 * @code: event code
 * @value: value of the event
 *
 * Similar to input_event() but will ignore event if device is "grabbed" and handle
 * injecting event is not the one that owns the device.
 */
void input_inject_event(struct input_handle *handle, unsigned int type, unsigned int code, int value)
{
        if (!handle->dev->grab || handle->dev->grab == handle)
                input_event(handle->dev, type, code, value);
}
//EXPORT_SYMBOL(input_inject_event);

/*
 * input_event() - report new input event
 * @dev: device that generated the event
 * @type: type of the event
 * @code: event code
 * @value: value of the event
 *
 * This function should be used by drivers implementing various input devices
 * See also input_inject_event()
 */
void input_event(struct input_dev *dev, unsigned int type, unsigned int code, int value)
{
    struct input_handle *handle;

    if (type > EV_MAX || !test_bit(type, dev->evbit))//首先判断该事件类型是否有效且为该设备所接受
        return;

    add_input_randomness(type, code, value);

    switch (type) {

        case EV_SYN:
            switch (code) {
                case SYN_CONFIG:
                    if (dev->event)
                        dev->event(dev, type, code, value);
                    break;

                case SYN_REPORT:
                    if (dev->sync)
                        return;
                    dev->sync = 1;
                    break;
            }
            break;

.............................................................
        case EV_LED:

            if (code > LED_MAX || !test_bit(code, dev->ledbit) || !!test_bit(code, dev->led) == value)
                return;

            change_bit(code, dev->led);

            if (dev->event)
                dev->event(dev, type, code, value);

            break;


    if (type != EV_SYN)
        dev->sync = 0;

    if (dev->grab)
        dev->grab->handler->event(dev->grab, type, code, value);
    else
        /*
         * 循环调用所有处理该设备的handle(event,mouse,ts,joy等),
         * 如果有进程打开了这些handle(进行读写),则调用其对应的event接口向气汇报该输入事件.
         */
        list_for_each_entry(handle, &dev->h_list, d_node)
            if (handle->open)
                handle->handler->event(handle, type, code, value);
}
///EXPORT_SYMBOL(input_event);
//
//注:
//    鉴于简单的gpio_keys驱动中没有注册自己的event接口,当然也没有对于LED灯的处理,而event层只是简单的向上层汇报输入事件(event层也不可能帮你处理你的led设备,对吧),所以这个通过输入子系统控制LED的部分暂时不去研究.
//    (输出设备LED灯不属于这个输入设备gpio_key的一部分.当然,如果你想通过这个gpio_keys设备来控制led灯的话,可以修改这个gpio_keys驱动,详细可参考driver/input/keyboard目录下的驱动)
//
//
// 
// 
//
//======================================================================================================================