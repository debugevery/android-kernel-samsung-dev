// Linux������ϵͳ(Input Subsystem)
// 
// 
// 1.1.input��ϵͳ����
// 
// 
// �����豸(�簴��,���̣�������������)�ǵ��͵��ַ��豸����һ��Ĺ��������ǵͲ��ڰ����������ȶ�������ʱ����һ���ж�(������ͨ��timer��ʱ��ѯ)��Ȼ��cpuͨ��SPI��I2C�����ⲿ�洢�����߶�ȡ��ֵ����������ݣ���һ�����������ַ��豸��������û���������������read()�ӿ����û����Զ�ȡ��ֵ����������ݡ�
// 
// 
// ��Linux�У�������ϵͳ����������ϵͳ�豸�����㡢������ϵͳ���Ĳ�(Input Core)��������ϵͳ�¼������(Event Handler)��ɡ������豸�������ṩ��Ӳ�����Ĵ����Ķ�д���ʺͽ��ײ�Ӳ�����û�������ʵ���Ӧת��Ϊ��׼�������¼�����ͨ�����Ĳ��ύ���¼�����㣻�����Ĳ�����ṩ���豸������ı�̽ӿڣ��������ṩ���¼������ı�̽ӿڣ����¼�������Ϊ�����û��ռ��Ӧ�ó����ṩ��ͳһ�����豸�Ľӿں��������ύ�����¼�����������ʹ�����������豸���������ֲ����ù��Ķ��豸�ļ��Ĳ���������Ҫ���ĶԸ�Ӳ���Ĵ����Ĳ������ύ�������¼���
// 
// 1.2. input��ϵͳ�ṹͼ
// 
// 
// input��ϵͳ�ṹͼ����ͼ1��ʾ��
// 
// 
// 
// ͼ1 ������ϵͳ�ṹͼ
// 
// 
// 1.3.linux�������豸�����ķֲ�
// 
// 
// linux�������豸�����ķֲ�����ͼ2��ʾ��
// 
// 
//  
// 
// ͼ2 linux�������豸�ķֲ�
// 
// 
// 1.4. ������ϵͳ�豸������ʵ��ԭ��
// 
// 
// ��Linux�У�Input�豸��input_dev�ṹ��������������input.h�С��豸������ֻ�谴�����²���Ϳ�ʵ���ˡ� 
// 1).������ģ����غ���������Input�豸֧��input��ϵͳ����Щ�¼��� 
// 2).��Input�豸ע�ᵽinput��ϵͳ�У� 
// 3).��Input�豸�����������ʱ(�磺���̱�����/̧�𡢴�����������/̧��/�ƶ�����걻�ƶ�/����/̧��ʱ��)���ύ���������¼�����Ӧ�ļ�ֵ/�����״̬��
// 
// 1.5.����������
// 
// 
// ��������������ͼ3��ʾ
// 
// 
// 
// ͼ 3 input��ϵͳ����������
// 
// 
// 1.6.���������йص�API����
// 
// 
// 
// 
// 1.6.1.����һ�������豸
// 
// 
// Struct input_dev *input_allocate_device*(void); 
// 
// 
// 1.6.2.ע��һ�������豸
// 
// 
// Int input_register_device(struct input_dev *dev);
// 
// 
// 1.6.3.����ʵ��-�¼�֧��
// 
// 
// Set_bit����inout��ϵͳ��֧����Щ�¼� 
// Set_bit(EV_KEY,button_dev.evbit) 
// Struct input_dev����������Ա��һ����evbit;һ����keybit.�ֱ�������ʾ�豸��֧�ֵ��¼����ͺͰ������͡�
// 
// 
// 1.6.3.1�¼�����
// 
// 
// Linux�������豸���¼�������(����ֻ�г��˳��õ�һЩ�������뿴linux/input.h��)��EV_SYN 0x00 ͬ���¼� 
// EV_KEY 0x01 �����¼� 
// EV_REL 0x02 ������� 
// EV_ABS 0x03 �������� 
// EV_MSC 0x04 ���� 
// EV_LED 0x11 LED 
// EV_SND 0x12 ���� 
// EV_REP 0x14 Repeat 
// EV_FF 0x15 ������
// 
// 
// 1.6.4.����ʵ��-�����¼�
// 
// 
// Void input_event(struct input_dev *dev,unsigned int type,unsigned int code,int value);//����ָ��type,code�������¼� 
// Void input_report_key(struct input_dev *dev,unsigned int code,int value);//�����ֵ 
// Void input_report_rel(struct input_dev *dev,unsigned int code,int value);//����������� 
// Void input_report_abs(struct input_dev *dev,unsigned int code,int value);//����������� 
// Void input_sync(struct input_dev *dev);//����ͬ���¼� 
// �ڴ�������������У�һ�����꼰����״̬����������������£� 
// Input_report_abs(input_dev,ABS_X,x);//X���� 
// Input_report_abs(input_dev,ABS_Y,y);//Y���� 
// Input_report_abs(input_dev,ABS_PRESSURE,pres);//ѹ�� 
// input_sync(struct input_dev *dev);//ͬ�� 
// 
// 
// 1.6.5�ͷ���ע���豸
// 
// 
// Void input_free_device(struct input_dev *dev); 
// Void input_unregister_device(struct input_dev *); 
// 
// ===============================================================================
// 
// linux�ں�input��ϵͳ���� .
// 2010-06-18 22:58 12720���Ķ� ����(18) �ղ� �ٱ� 
// ���ߣ�������,����Զ��Ƕ��ʽѧԺ��ʦ��    
// 
//     Android��X windows��qt���ڶ�Ӧ�ö���linuxϵͳ�м��̡���ꡢ�������������豸��֧�ֶ�ͨ������Խ��Խ�����ڱ�׼��input������ϵͳ��
// 
//     ��Ϊinput��ϵͳ�Ѿ�������ַ��������ļ������ӿڣ����Ա�д�����ĺ��Ĺ��������inputϵͳ�����Ľӿڣ����������󡣵�������������Ӧ����������Ҫ�úõķ�����input��ϵͳ�ˡ�
// 
// һ��input������ϵͳ���
// 
//     ��ͼ��input������ϵͳ��ܣ�������ϵͳ��������ϵͳ���Ĳ㣨 Input Core ������������¼�����㣨Event Handler����������ɡ�һ�������¼���������ƶ������̰������£�joystick���ƶ��ȵ�ͨ�� input driver -> Input core -> Event handler -> userspace �����û��ռ䴫��Ӧ�ó���
// 
//  
// 
//  
// 
// ע�⣺keyboard.c������/dev/input�²����ڵ㣬������Ϊttyn�նˣ������������նˣ������롣
// 
//  
// 
// ����Input driver��дҪ��
// 
// 1�����䡢ע�ᡢע��input�豸

struct input_dev *input_allocate_device(void)

int input_register_device(struct input_dev *dev)

void input_unregister_device(struct input_dev *dev)

 

// 2������input�豸֧�ֵ��¼����͡��¼��롢�¼�ֵ�ķ�Χ��input_id����Ϣ
// 
// �μ�usb����������usbkbd.c
// 
usb_to_input_id(dev, &input_dev->id);//����bustype��vendo��product��

input_dev->evbit[0] = BIT(EV_KEY) | BIT(EV_LED) | BIT(EV_REP);//֧�ֵ��¼�����

input_dev->ledbit[0] = BIT(LED_NUML) | BIT(LED_CAPSL) | BIT(LED_SCROLLL) | BIT(LED_COMPOSE) | BIT(LED_KANA);// EV_LED�¼�֧�ֵ��¼���

for (i = 0; i < 255; i++)

    set_bit(usb_kbd_keycode[i], input_dev->keybit); //EV_KEY�¼�֧�ֵ��¼���

// include/linux/input.h�ж�����֧�ֵ����ͣ������г�����2.6.22�ں˵������
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
// һ���豸����֧��һ�������¼����͡�ÿ���¼��������滹��Ҫ���þ���Ĵ����¼��롣���磺EV_KEY�¼�����Ҫ������֧����Щ�����¼��롣
// 
//  
// 
//  
// 
// 3�������Ҫ������input�豸�Ĵ򿪡��رա�д������ʱ�Ĵ�����
// 
// �μ�usb����������usbkbd.c

    input_dev->open = usb_kbd_open;

    input_dev->close = usb_kbd_close;

    input_dev->event = usb_kbd_event;
 /
//4���ڷ��������¼�ʱ������ϵͳ�����¼�
//
//���ڱ���EV_KEY��EV_REL��EV_ABS���¼��ĺ����У�
/
void input_report_key(struct input_dev *dev, unsigned int code, int value)

    void input_report_rel(struct input_dev *dev, unsigned int code, int value)

    void input_report_abs(struct input_dev *dev, unsigned int code, int value)
 /
//    ���������鷳����Ҳ����ֻ��ס1����������Ϊ������������ͨ����ʵ�ֵģ�
/
void input_event(struct input_dev *dev, unsigned int type, unsigned int code, int value)

 

 

//����Event Handler�����
//
// 1��Input������ϵͳ���ݽṹ��ϵͼ



 

 

// 2��input_handler�ṹ��

��evdev.c�е�evdev_handlerΪ����

static struct input_handler evdev_handler = {

    .event =    evdev_event, //��ϵͳ����input�¼���ϵͳͨ��read������ȡ

    .connect =  evdev_connect, //��input_devƥ������connect����

    .disconnect =   evdev_disconnect,

    .fops =     &evdev_fops,  //event�豸�ļ��Ĳ�������

    .minor =    EVDEV_MINOR_BASE,  //���豸�Ż�׼ֵ

    .name =     "evdev",

    .id_table = evdev_ids,  //ƥ�����

};

 

// 3��input�ַ��豸ע�����

drivers/input/input.c�У�

static int __init input_init(void)

{

    int err;

    err = class_register(&input_class);

����

    err = register_chrdev(INPUT_MAJOR, "input", &input_fops);

    ����

}

input_fops���壺

static const struct file_operations input_fops = {

    .owner = THIS_MODULE,

    .open = input_open_file,

};

 

Input_dev��input_handlerƥ������input_handler��connect����evdev_handlerΪ����

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

 

    evdev = kzalloc(sizeof(struct evdev), GFP_KERNEL);//Ϊÿ��ƥ��evdev_handler���豸����һ��evdev��

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

 

    evdev_table[minor] = evdev;//��¼evdev��λ�ã��ַ��豸/dev/input/evnetx����ʱ���ݴ��豸�ż�EVDEV_MINOR_BASE������evdev_open���ҵ���Ӧ��evdev

    devt = MKDEV(INPUT_MAJOR, EVDEV_MINOR_BASE + minor),

    cdev = class_device_create(&input_class, &dev->cdev, devt,

                 dev->cdev.dev, evdev->name);//������event�ַ��豸�ڵ�

    ����

}

 

// 4��input�ַ��豸�Ĵ򿪹���

static int input_open_file(struct inode *inode, struct file *file)

{

struct input_handler *handler = input_table[iminor(inode) >> 5];

//�õ���Ӧ��input_handler

    const struct file_operations *old_fops, *new_fops = NULL;

    int err;

    if (!handler || !(new_fops = fops_get(handler->fops)))

//ȡ����Ӧinput_handler��file_operations

        return -ENODEV;

    if (!new_fops->open) {

        fops_put(new_fops);

        return -ENODEV;

    }

    old_fops = file->f_op;

    file->f_op = new_fops;//�ض�λ�򿪵��豸�ļ��Ĳ�������

    err = new_fops->open(inode, file);

    if (err) {

        fops_put(file->f_op);

        file->f_op = fops_get(old_fops);

    }

    fops_put(old_fops);

    return err;

}

//5��input�ַ��豸����������

//    ������open�׶��Ѿ����豸�ļ��Ĳ������������ض�λ�˵��˾����input_handler�����������ӿڲ�����read��write��ioctl�ȣ����ɸ���input_handler��fops������������evdev.c�еģ�evdev_fops


==================================================================================================

 /
//Linux����(input)��ϵͳ (2009-01-06 23:38) 
//���ࣺ linux���� 
//
//
//
//###############################################################################################
//��ǰ���о���һ��������ϵͳ��ԭ��,���˵ĸо���������ϵͳ�ܸ���.����ʵ�ں˿��������ⷽ���Ѿ����ú�������,
//������ϵͳ��Ȼ���۸���,����ֻҪ���������������ϵͳ��һЩ���˼���,����Ҫʹ������������.
//
//�������ں��Դ���gpio_keys����Ϊ��,����������ϵͳ��ʹ��.
//��Ҫ��ԭ����gpio_keys�����Ƚϼ��׶�,���ⲻ��û���˶��д�����,�����̵Ļ�����ÿһ�鿪�����϶����а�^_^
//
//������ǰ��ϰ��,�ȴ��µ��ϵ��о��ײ�����������ύ�����¼���:
//###############################################################################################
/
drivers/input/keyboard/gpio_keys.c:

static int __devinit gpio_keys_probe(struct platform_device *pdev)
{
    struct gpio_keys_platform_data *pdata = pdev->dev.platform_data;
    struct input_dev *input;
    int i, error;

    input = input_allocate_device();//����input_dev�ṹ
    if (!input)
        return -ENOMEM;

    platform_set_drvdata(pdev, input);//��input_dev�ṹ�ź�(�Ժ󷽱����)

    input->evbit[0] = BIT(EV_KEY);//Ŀǰevent�����Ͳ�����32,������ῴ������evbit����Ĳ������Ƕ�evbit[0]�е�λ�����в���.

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

        /* �����û���ָ����gpio_keys�������жϺ�ע���жϴ�����*/
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

    error = input_register_device(input);//ע�������豸,���Ͷ�Ӧ��handler�������ҹ�
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


//�ᵽinput_dev�ṹ,����̸һ���Ҷ����������:
struct input_dev {

    void *private;

    const char *name;
    const char *phys;
    const char *uniq;
    struct input_id id;

    /*
     * ���ݸ��������źŵ���������������Ϊunsigned long ������,
     * �����ÿ1bit����һ���ź�����,
     * �ں��л���������λ����λ��������ʾʱ��ķ����ͱ�����.
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

/* ��¼���豸������Щ�¼�����Ȥ(������д���)*/
void input_set_capability(struct input_dev *dev, unsigned int type, unsigned int code)
{
    switch (type) {
    case EV_KEY:
        __set_bit(code, dev->keybit);//���簴��,Ӧ�ö���Щ��ֵ�İ������д���(�������������������)
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

    __set_bit(type, dev->evbit);//�о���ǰ���ظ���(ǰ��һ�����ù�һ����)
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

                if (irq == gpio_to_irq(gpio)) {//�ж��ĸ���������?
                        unsigned int type = button->type ?: EV_KEY;
                        int state = (gpio_get_value(gpio) ? 1 : 0) ^ button->active_low;//��¼����״̬

                        input_event(input, type, button->code, !!state);//�㱨�����¼�
                        input_sync(input);//�ȴ������¼��������
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

    if (type > EV_MAX || !test_bit(type, dev->evbit))//�����жϸ��¼������Ƿ���Ч��Ϊ���豸������
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
             * ������Ҫ���㼸������:
             * 1: ��ֵ��Ч(����������ļ�ֵ����Ч��Χ)
             * 2: ��ֵΪ�豸���ܽ���(���ڸ��豸��ӵ�еļ�ֵ��Χ)
             * 3: ����״̬�ı���
             */

            if (code > KEY_MAX || !test_bit(code, dev->keybit) || !!test_bit(code, dev->key) == value)
                return;

            if (value == 2)
                break;

            change_bit(code, dev->key);//�ı��Ӧ������״̬

            /* �����ϣ������δ�ͷŵ�ʱ�򲻶ϻ㱨�����¼��Ļ���Ҫ�������(�ڼ򵥵�gpio_keys�����в���Ҫ���,��ʱ��ȥ����) */
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
         * ѭ���������д�����豸��handle(event,mouse,ts,joy��),
         * ����н��̴�����Щhandle(���ж�д),��������Ӧ��event�ӿ������㱨�������¼�.
         */
        list_for_each_entry(handle, &dev->h_list, d_node)
            if (handle->open)
                handle->handler->event(handle, type, code, value);
}
//EXPORT_SYMBOL(input_event);
 /
//
//#########################################################################
//����,���������о�һ��event�����input�㱨���������������¼�������������.
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
                  /* ����client_list�����е�client�ṹ(����Щ��evdev�Ľ���(�������^_^)) */
                list_for_each_entry(client, &evdev->client_list, node) {
                            /* ������������źŵ�struct input_event�ṹ(�¼�,����,����,��ֵ) */
                        do_gettimeofday(&client->buffer[client->head].time);
                        client->buffer[client->head].type = type;
                        client->buffer[client->head].code = code;
                        client->buffer[client->head].value = value;
                            /* ����дָ�� */
                        client->head = (client->head + 1) & (EVDEV_BUFFER_SIZE - 1);

                        kill_fasync(&client->fasync, SIGIO, POLL_IN);//֪ͨ����input_sync�Ľ���:�����¼����Ѵ������(֪ͨ�ײ�).
                }

        wake_up_interruptible(&evdev->wait);//����˯����evdev->wait�ȴ����еȴ�������Ϣ�Ľ���(֪ͨ�ϲ�).
}
 /
//###################################################################################
//����,����һ�������������¼��������,�����������ϵ��ϵ��������û�����λ�ȡ��������¼���.
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
         /* ���evdev_client�ṹ������evdev->client_list��(���������¼�������ʱ����д�ýṹ�����ѽ��̶�ȡ) */
        list_add_tail(&client->node, &evdev->client_list);

        if (!evdev->open++ && evdev->exist) {
                error = input_open_device(&evdev->handle);
                if (error) {
                        list_del(&client->node);
                        kfree(client);
                        return error;
                }
        }

        file->private_data = client;//��ź�evdev_client�ṹ�����Ժ�ʹ��
        return 0;
}


static ssize_t evdev_read(struct file *file, char __user *buffer, size_t count, loff_t *ppos)
{
        struct evdev_client *client = file->private_data;
        struct evdev *evdev = client->evdev;
        int retval;

        if (count < evdev_event_size())//����ÿ�ζ�ȡ�����ݴ�С����һ����Ҫ��.
                return -EINVAL;

        if (client->head == client->tail && evdev->exist && (file->f_flags & O_NONBLOCK))//������û�����ݿɶ����豸�Ǵ��ڵ�,
                                                      //�������ΪNONBLOCK��ʽ����,��������.
                return -EAGAIN;

        retval = wait_event_interruptible(evdev->wait,
                client->head != client->tail || !evdev->exist);//����ȴ����������ݿɶ����豸������(����ȥ)
        if (retval)
                return retval;

        if (!evdev->exist)
                return -ENODEV;

        while (client->head != client->tail && retval + evdev_event_size() <= count) {//���濪ʼ��ȡ����

                struct input_event *event = (struct input_event *) client->buffer + client->tail;//��ȡ�����еĶ�ָ��

                if (evdev_event_to_user(buffer + retval, event))//�������ݸ��û�
                        return -EFAULT;

                client->tail = (client->tail + 1) & (EVDEV_BUFFER_SIZE - 1);//���¶�ָ��
                retval += evdev_event_size();
        }

        return retval;
}
 /
//�Ǻ�,�����˰�,Ӧ�ó������������ȡ�����¼���^_^
//
//##########################################################################################################
//��������gpio_keys��������������,ֻҪ�����������¼���ʱ�����ϲ�Ӧ�ó���㱨��ֵ����.
//����,����һЩ������豸(����led��)�������豸��˵(�������),�ϲ�Ӧ�ó���ͬ����������event������ȡ��ı���״̬.
//�뿴���´���:
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

                if (evdev_event_from_user(buffer + retval, &event))//���û�����ȡ�¼��ṹ
                        return -EFAULT;
                input_inject_event(&evdev->handle, event.type, event.code, event.value);//���ײ㷢���¼�
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

    if (type > EV_MAX || !test_bit(type, dev->evbit))//�����жϸ��¼������Ƿ���Ч��Ϊ���豸������
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
         * ѭ���������д�����豸��handle(event,mouse,ts,joy��),
         * ����н��̴�����Щhandle(���ж�д),��������Ӧ��event�ӿ������㱨�������¼�.
         */
        list_for_each_entry(handle, &dev->h_list, d_node)
            if (handle->open)
                handle->handler->event(handle, type, code, value);
}
///EXPORT_SYMBOL(input_event);
//
//ע:
//    ���ڼ򵥵�gpio_keys������û��ע���Լ���event�ӿ�,��ȻҲû�ж���LED�ƵĴ���,��event��ֻ�Ǽ򵥵����ϲ�㱨�����¼�(event��Ҳ�����ܰ��㴦�����led�豸,�԰�),�������ͨ��������ϵͳ����LED�Ĳ�����ʱ��ȥ�о�.
//    (����豸LED�Ʋ�������������豸gpio_key��һ����.��Ȼ,�������ͨ�����gpio_keys�豸������led�ƵĻ�,�����޸����gpio_keys����,��ϸ�ɲο�driver/input/keyboardĿ¼�µ�����)
//
//
// 
// 
//
//======================================================================================================================