// Linux input��ϵͳ����
// ���������ݽṹ
// [���ڣ�2011-09-18] ��Դ��Linux����  ���ߣ�YAOZHENGUO2006 
// 
//  
// Input��ϵͳ�������������κ������豸���������򶼿���ͨ��Input������ϵͳ�ṩ�Ľӿ�ע�ᵽ�ںˣ�������ϵͳ�ṩ�Ĺ��������û��ռ佻���������豸һ��������̣���꣬�������ȣ����ں��ж����������豸���ֵġ��������input������ϵͳ�Ľṹ���Լ�����ʵ�֡�
// һ. Input��ϵͳ�ṹ�빦��ʵ��
//   1. Input��ϵͳ�Ƿֲ�ṹ�ģ��ܹ���Ϊ���㣺 Ӳ�������㣬��ϵͳ���Ĳ㣬�¼�����㡣  
// 
//     ��1������Ӳ�������㸺����������Ӳ���豸�����Ĵ�������Ծ������������ģ���Ҫ�����������������д��
//     ��2����ϵͳ���Ĳ�����������������֮���Ŧ���������������ṩ������Ľӿڣ������ṩ�¼������Ľӿڡ�
//     ��3���¼�����㸺�����û�����򽻵�����Ӳ�������㴫�����¼�������û�����
//   2. ����֮��ͨ�ŵĻ�����λ�����¼����κ�һ�������豸�Ķ��������Գ����һ���¼�������̵İ��£��������İ��£������ƶ��ȡ��¼����������ԣ����ͣ�type��������(code)��ֵ(value)��Input��ϵͳ֧�ֵ������¼���������input.h�У���������֧�ֵ����ͣ���������֧�ֵı���ȡ��¼����͵ķ����� Ӳ��������-->��ϵͳ����-->�¼������-->�û��ռ�
//   3. �Դ�����Ϊ��˵��������ϵͳ�Ĺ�������:
//      ע��mini2440�Ĵ��������������������Ӧ��ģ���ļ�Ϊ��s3c2410_ts.c���¼�������Ӧ��ģ���ļ�Ϊ evdev.c
//     ��1��s3c2410_tsģ���ʼ�������н�������ע�ᵽ��������ϵͳ�У��ڴ�ͬʱ��ע�ắ�����¼������������Ѱ���¼��������������ҵ�����evdev�����ҽ��������¼����������ء�������/dev/input�������豸�ļ�event0���Ժ����Ƿ�������ļ��ͻ��ҵ����ǵĴ�������������
//     ��2��Ӧ�ó�����豸�ļ�/dev/input/event0����ȡ�豸�ļ�������evdevģ����read,���û���¼����̾ͻ�˯�ߡ�  
//     ��3�������������£�������ͨ����ϵͳ���Ľ��¼�������X��Y���꣩,�����¼������Ҳ����evdev,evdev����˯�ߵĽ��̣����¼��������̴���
// 
// ��.��Ҫinputͨ�����ݽṹ
//   1.input_dev ����input�豸�������豸�ṹ��ÿ��input���������ж���������ʼ������һ���ṹ����Ա�Ƚ϶� 
//     ��1�������¼������飺
// 
1.unsigned long evbit[BITS_TO_LONGS(EV_CNT)];   //�¼�֧�ֵ�����   
2.        // ������ÿ������֧�ֵı���   3.    unsigned long keybit[BITS_TO_LONGS(KEY_CNT)];   //����     4.    unsigned long relbit[BITS_TO_LONGS(REL_CNT)];     5.    unsigned long absbit[BITS_TO_LONGS(ABS_CNT)];   //�������꣬���д���������ʹ�õľ������   6.    unsigned long mscbit[BITS_TO_LONGS(MSC_CNT)];  7.    unsigned long ledbit[BITS_TO_LONGS(LED_CNT)];  8.    unsigned long sndbit[BITS_TO_LONGS(SND_CNT)];  9.    unsigned long ffbit[BITS_TO_LONGS(FF_CNT)];  10.    unsigned long swbit[BITS_TO_LONGS(SW_CNT)];      evbit[BITS_TO_LONGS(EV_CNT)]; ���������λ�������ʽ������������豸֧�ֵ��¼������͡����÷�ʽ�磺
//    dev->evbit[0] = BIT(EV_SYN) | BIT(EV_KEY) | BIT(EV_ABS)
//    absbit[BITS_TO_LONGS(ABS_CNT)]; �������Ҳ����λ�������ʽ������������͵��¼�֧�ֵı���
//    ����������֧��EV_ABS,����Ҫ����������飬 ��һ��ר�������������ĺ���input_set_abs_params����������: 
1.static inline void input_set_abs_params(struct input_dev *dev, int axis, int min, int max, int fuzz, int flat)  
2.{  
3.    dev->absmin[axis] = min;  
4.    dev->absmax[axis] = max;  
5.    dev->absfuzz[axis] = fuzz;  
6.    dev->absflat[axis] = flat;  
7.  
8.    dev->absbit[BIT_WORD(axis)] |= BIT_MASK(axis);  //�����absbit�������   9.}  
//   ���������������������õ�
    input_set_abs_params(dev, ABS_X, 0, 0x3FF, 0, 0)��   //���������adת����x����
    input_set_abs_params(dev, ABS_Y, 0, 0x3FF, 0, 0);   //���������adת����y����
    input_set_abs_params(dev, ABS_PRESSURE, 0, 1, 0, 0); //��������ô������Ƿ��µı�־
//    ����ABS_X����ֵ��ΧΪ0-0x3ff����Ϊmini2440��ADת�������������Ϊ10λ�����Բ��ᳬ��0x3ff�� 
//
//  ��2�� struct input_id id ��Ա
//     ����Ǳ�ʶ�豸����������
//
1.struct input_id {  
2.    __u16 bustype;   //��������   3.    __u16 vendor;    //��������   4.    __u16 product;   //��Ʒ����   5.    __u16 version;   //�汾   6. };  
//   �����Ҫ�ض����¼�����������������豸�Ļ����⼸���ͷǳ���Ҫ����Ϊ��ϵͳ������ͨ�����ǣ����豸�������¼��������ϵ�����ġ�������Ϊ�������������õ��¼�������Ϊevdev��ƥ�����У����������ʼ��
//    Ҳ�޹ؽ�Ҫ��
//  ��3�� ��������һЩ��Ա��Ҳ�Ƚ���Ҫ����������������Բ��ùܣ���������ϵͳ����������ġ�
//  ��4�� ���Կ���input_dev �ṹ������ΪӲ�������㣬�Ժ����input_dev����ʾ�����豸��
//  2. input_handler �����¼������������ݽṹ������һ���¼�������
//   ��1��������������
    void (*event)(struct input_handle *handle, unsigned int type, unsigned int code, int value);
    int (*connect)(struct input_handler *handler, struct input_dev *dev, const struct input_device_id *id);
    void (*disconnect)(struct input_handle *handle);
    void (*start)(struct input_handle *handle);
//    event �����ǵ��¼����������յ�������input�豸�������¼�ʱ���õĴ��������������¼����ǳ���Ҫ�����¼����ݹ����л���ϸ������
//    connect �����ǵ�һ��input�豸ģ��ע�ᵽ�ں˵�ʱ����õģ����¼��������������豸��ϵ�����ĺ�����Ҳ���ǽ�input_dev��input_handler��Եĺ�����
//    disconnect ����ʵ��connect�෴�Ĺ��ܡ�
//    start ��ʱû�з�����ʲô���á�
//  ��2�� ����id
    const struct input_device_id *id_table; //������¼���������֧�ֵ�input�豸
//    const struct input_device_id *blacklist; //������¼�������Ӧ�ú��Ե�input�豸
//     ���������鶼������connect�����У�input_device_id�ṹ��input_id�ṹ���ƣ�����input_device_id��һ��flag�������ó���ѡ��Ƚ�����磺busytype,vendor����������
//   ��3�� ��������
    struct list_headh_list;  //�������������������֧�ֵ�input_handle�ṹ,input_dev��input_handler���֮��ͻ�����һ��input_handle�ṹ
    struct list_headnode;    //���ӵ�input_handler_list�������������������ע�ᵽ�ں˵��¼�������
//  3.  input_handle �ṹ�����һ���ɹ���Ե�input_dev��input_handler 
1.struct input_handle {  
2.    void *private;   //ÿ����Ե��¼��������������һ����Ӧ���豸�ṹ����evdev�¼���������evdev�ṹ��ע������ṹ���豸�������input_dev��ͬ����ʼ��handleʱ�����浽���   3.    int open;        //�򿪱�־��ÿ��input_handle �򿪺���ܲ��������һ��ͨ���¼���������open�����������   4.    const char *name;   5.    struct input_dev *dev;  //������input_dev�ṹ   6.    struct input_handler *handler; //������input_handler�ṹ   7.    struct list_head    d_node;  //input_handleͨ��d_node���ӵ���input_dev�ϵ�h_list������   8.    struct list_head    h_node;  //input_handleͨ��h_node���ӵ���input_handler��h_list������   9.};  
//  4. �������ݽṹ֮��Ĺ�ϵ
//     input_dev ��Ӳ�������㣬����һ��input�豸
//     input_handler ���¼�����㣬����һ���¼�������
//     input_handle ������Ϊ���ں��Ĳ㣬����һ����Ե�input�豸��input�¼�������
//     input_dev ͨ��ȫ�ֵ�input_dev_list������һ���豸ע���ʱ��ʵ�����������
//     input_handler ͨ��ȫ�ֵ�input_handler_list������һ���¼�������ע���ʱ��ʵ������������¼�������һ���ں��Դ���һ�㲻��Ҫ������д��
//
//     input_hande û��һ��ȫ�ֵ�������ע���ʱ���Լ��ֱ������input_dev �� input_handler ��h_list���ˡ�ͨ��input_dev ��input_handler�Ϳ����ҵ�input_handle ���豸ע����¼��������� ע���ʱ��Ҫ������Թ�������Ժ�ͻ�ʵ�����ӡ�ͨ��input_handleҲ�����ҵ�input_dev��input_handler��
//
//��ƪ������Դ�� Linux������վ(www.linuxidc.com)  ԭ�����ӣ�http://www.linuxidc.com/Linux/2011-09/43187.htm
//
//
//һ. ����ע�ắ�� 
//    ��Ϊ����һ������ÿ�����ݽṹ������һ���������ÿ�����ݽṹ�����Ӧһ��ע�ắ�������Ƕ���������ϵͳ���ĵ�input.c�ļ��С���Ҫ������ע�ắ��
//     input_register_device    ���ں�ע��һ��input�豸
//     input_register_handle    ���ں�ע��һ��handle�ṹ
// 
//
//     input_register_handler   ע��һ���¼�������
//  1. input_register_device ע��һ��input�����豸�����ע�ắ��������ע�ắ��������������Ψһ���õġ�����������������
//
//
 
1.int input_register_device(struct input_dev *dev)  
2.{  
3.    static atomic_t input_no = ATOMIC_INIT(0);    4.        //���ԭ�ӱ����������ܹ�ע���input�豸��ÿע��һ����1����Ϊ�Ǿ�̬����������ÿ�ε��ö����������   5.    struct input_handler *handler;  6.    const char *path;  7.    int error;  8.  
9.    __set_bit(EV_SYN, dev->evbit);  //EN_SYN ������豸��Ҫ֧�ֵ��¼����ͣ�����Ҫ����   10.  
11.    /* 12.     * If delay and period are pre-set by the driver, then autorepeating 
13.     * is handled by the driver itself and we don't do it in input.c. 
14.     */  
15.        // ����ں˶�ʱ����Ϊ���ظ����������õ�   16.    init_timer(&dev->timer);  
17.    if (!dev->rep[REP_DELAY] && !dev->rep[REP_PERIOD]) {  18.        dev->timer.data = (long) dev;  19.        dev->timer.function = input_repeat_key;  
20.        dev->rep[REP_DELAY] = 250;  
21.        dev->rep[REP_PERIOD] = 33;  
22.        //���û�ж����й��ظ����������ֵ�������ں�Ĭ�ϵ�   23.    }  
24.  
25.    if (!dev->getkeycode)  26.        dev->getkeycode = input_default_getkeycode;  
27.    if (!dev->setkeycode)  28.        dev->setkeycode = input_default_setkeycode;  
29.        //�������õ�Ĭ�Ϻ�����input�����ṩ   30.    dev_set_name(&dev->dev, "input%ld",  31.             (unsigned long) atomic_inc_return(&input_no) - 1);  32.        //����input_dev��device�����֣�������ֻ���/class/input�г���   33.    error = device_add(&dev->dev);  
34.        //��device���뵽linux�豸ģ����ȥ   35.    if (error)  36.        return error;  37.  
38.    path = kobject_get_path(&dev->dev.kobj, GFP_KERNEL);  
39.    printk(KERN_INFO "input: %s as %s\n",  40.        dev->name ? dev->name : "Unspecified device", path ? path : "N/A");  41.    kfree(path);  
42.        //����õ�·�����ƣ�����ӡ����   43.    error = mutex_lock_interruptible(&input_mutex);  
44.    if (error) {  45.        device_del(&dev->dev);  
46.        return error;  47.    }  
48.  
49.    list_add_tail(&dev->node, &input_dev_list);  
50.        // ���·����input�豸���ӵ�input_dev_list������   51.    list_for_each_entry(handler, &input_handler_list, node)  
52.        input_attach_handler(dev, handler);  
53.        //����input_handler_list������� input_dev �� input_handler   54.        //input_attach_handler �����������ԵĹؼ������潫��ϸ����   55.    input_wakeup_procfs_readers();  
56.        // ��proc�ļ�ϵͳ�йأ���ʱ������   57.    mutex_unlock(&input_mutex);  
58.  
59.    return 0;  60.   }  
//   input_register_device��ɵ���Ҫ���ܾ��ǣ���ʼ��һЩĬ�ϵ�ֵ�����Լ���device�ṹ��ӵ�linux�豸ģ�͵��У���input_dev��ӵ�input_dev_list�����У�Ȼ��Ѱ�Һ��ʵ�handler��input_handler���,��Եĺ��ĺ�����input_attach_handler���������input_attach_handler������
//
 
1.static int input_attach_handler(struct input_dev *dev, struct input_handler *handler)  
2.{  
3.    const struct input_device_id *id;  4.    int error;  5.  
6.    if (handler->blacklist && input_match_device(handler->blacklist, dev))  7.        return -ENODEV;  8.        //blacklist��handler��ú��Ե�input�豸���ͣ����Ӧ�ú��Ե�input�豸Ҳ������ˣ��Ǿͳ�����   9.    id = input_match_device(handler->id_table, dev);  
10.        //�������Ҫ����Ժ�������Ҫ�Ƚ�id�еĸ��������ϸ����   11.    if (!id)  12.        return -ENODEV;  13.  
14.    error = handler->connect(handler, dev, id);  
15.        //��Գɹ�����handler��connect����������������¼��������ж��壬��Ҫ����һ��input_handle�ṹ������ʼ����������һ���¼���������ص��豸�ṹ��������ϸ����   16.    if (error && error != -ENODEV)  17.        printk(KERN_ERR  
18.            "input: failed to attach handler %s to device %s, "  19.            "error: %d\n",  20.            handler->name, kobject_name(&dev->dev.kobj), error);  
21.        //������   22.    return error;  23. }  
//    input_attach_handler����Ҫ���ܾ��ǵ���������������һ��input_match_device������ԣ�һ��connect������Գɹ�����������
//   �������input_match_device������

 
1.static const struct input_device_id *input_match_device(const struct input_device_id *id,  
2.                            struct input_dev *dev)  3.{  
4.    int i;  5.        //��������Ĳ�������Ҫ���handler��id_table������������id_tableѰ�Һ��ʵ�id�������   6.    for (; id->flags || id->driver_info; id++) {  7.        if (id->flags & INPUT_DEVICE_ID_MATCH_BUS)  8.            if (id->bustype != dev->id.bustype)  9.                continue;  10.                ......  
11.                //���handler->id->flag���Ƚϲ�ͬ������   12.                //����Ƚϳɹ���������ĺ꣬���������һ��id   13.                MATCH_BIT(evbit,  EV_MAX);  
14.            ......    
15.        MATCH_BIT(swbit,  SW_MAX);  
16.  
17.  
18.        return id;  19.    }  
2/0. }  
//    �˺�����Ҫ�ǱȽ�input_dev�е�id��handler֧�ֵ�id,��������handler��id_table�С����ȿ�id->driver_info��û�����ã����������˵����ƥ�����е�id��evdev�����������handler
//    Ȼ������id->flag���Ƚ����ݣ�������Ƚϳɹ�����MATCH_BIT���������������λ���бȽϵģ������ǱȽ���֧���¼������ͣ�ֻ�����е�λ��ƥ��ųɹ����أ����������һ��id�ıȽϡ�
//
// 
// 1.#define MATCH_BIT(bit, max) \   
// 2.for (i = 0; i < BITS_TO_LONGS(max); i++) \  3.    if ((id->bit[i] & dev->bit[i]) != id->bit[i]) \  4.        break; \  5.if (i != BITS_TO_LONGS(max)) \  6.    continue;      ��������ÿ���¼����ͣ��Լ�ÿ���¼�����֧�ֵı������е�λ���Ƚ�һ�Σ���handler��id�Ƿ�֧�֣������һ����֧�־Ͳ���Ƚϳɹ���������һ��id���бȽϡ�
//    ����connect������ÿ���¼���������ʵ�ֶ��в��죬��ԭ����ͬ����Ϊ�������õ��¼�������Ϊevdev���������evdev��connect����evdev_connect

 
1.static int evdev_connect(struct input_handler *handler, struct input_dev *dev,  
2.             const struct input_device_id *id)  3.{  
4.        //�˺������������������ֱ��ǣ�handler��dev,id   5.    struct evdev *evdev;  6.    int minor;  7.    int error;  8.  
9.  
10.    for (minor = 0; minor < EVDEV_MINORS; minor++)  11.        if (!evdev_table[minor])  12.            break;  13.        //EVDEV_MINORSΪ32��˵��evdev���handler����ͬʱ��32�������豸������ԣ�evdev_table����minor���Ǵ��豸�ţ�������һ�������ϵ�����evdev�ṹ�壬����Ҫ��ϸ��������ṹ��   14.    if (minor == EVDEV_MINORS) {  15.        printk(KERN_ERR "evdev: no more free evdev devices\n");  16.        return -ENFILE;  17.    }  
18.        //���˵��32��λ��ȫ����ռ���ˣ�����ʧ��   19.    evdev = kzalloc(sizeof(struct evdev), GFP_KERNEL);  20.        //����һ��evdev�ṹ�壬����ṹ����evdev�¼����������еģ��������ϸ����   21.    if (!evdev)  22.        return -ENOMEM;  23.  
24.  
25.    INIT_LIST_HEAD(&evdev->client_list);  
26.    spin_lock_init(&evdev->client_lock);  
27.    mutex_init(&evdev->mutex);  
28.    init_waitqueue_head(&evdev->wait);  
29.        //��ʼ���ṹ���һЩ��Ա   30.    dev_set_name(&evdev->dev, "event%d", minor);  31.        //���������evdev��device�����֣�����������/class/input�С�   32.        //ǰ��Ҳ��һ��device��input_dev�ģ�������input��n����ע�������Ĳ�ͬ   33.        //����ṹ����Ժ�������豸�ṹ��û�ж�Ӧ��Ӳ��������ͨ���������ҵ���ص�Ӳ��   34.    evdev->exist = 1;  
35.    evdev->minor = minor;  
36.  
37.  
38.    evdev->handle.dev = input_get_device(dev);  
39.    evdev->handle.name = dev_name(&evdev->dev);  
40.    evdev->handle.handler = handler;  
41.    evdev->handle.private = evdev;  42.        //��Ϊevdev�а���handle�ˣ����Գ�ʼ�����Ϳ����ˣ�������������input_handler��input_dev   43.    evdev->dev.devt = MKDEV(INPUT_MAJOR, EVDEV_MINOR_BASE + minor); //ע�⣺���minor���������Ĵ��豸�ţ���Ҫ����EVDEV_MINOR_BASE   44.    evdev->dev.class = &input_class;  45.    evdev->dev.parent = &dev->dev;  
46.        //������ɵ�device�����豸�������������input_dev   47.    evdev->dev.release = evdev_free;  
48.    device_initialize(&evdev->dev);  
49.  
50.  
51.    error = input_register_handle(&evdev->handle);  
52.        //ע��handle�ṹ��,�������������ϸ����   53.    if (error)  54.        goto err_free_evdev;  55.  
56.  
57.    error = evdev_install_chrdev(evdev);  
58.        //�������ֻ����һ���£����ǰ�evdev�ṹ���浽evdev_table�У��������ҲminorΪ����   59.    if (error)  60.        goto err_unregister_handle;  61.  
62.  
63.    error = device_add(&evdev->dev);  
64.        //ע�ᵽlinux�豸ģ����   65.    if (error)  66.        goto err_cleanup_evdev;  67.  
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
//    evdev_connect��������Ժ���ƺ���������һ��evdev�ṹ�壬����ʼ����س�Ա��evdev�ṹ������input_handle�ṹ����ʼ����ע��֮��
// 2. input_register_handle ע��һ��input_handle�ṹ�壬�Ƚϼ�

 
1.int input_register_handle(struct input_handle *handle)  
2.{  
3.    struct input_handler *handler = handle->handler;  4.    struct input_dev *dev = handle->dev;  5.    int error;  6.  
7.  
8.    /* 9.     * We take dev->mutex here to prevent race with 
10.     * input_release_device(). 
11.     */  
12.    error = mutex_lock_interruptible(&dev->mutex);  
13.    if (error)  14.        return error;  15.    list_add_tail_rcu(&handle->d_node, &dev->h_list);  
16.        //��handle��d_node�����ӵ�����ص�input_dev��h_list������   17.    mutex_unlock(&dev->mutex);  
18.  
19.  
20.    list_add_tail(&handle->h_node, &handler->h_list);  
21.        //��handle��h_node�����ӵ�����ص�input_handler��h_list������   22.    if (handler->start)  23.        handler->start(handle);  
24.  
25.  
26.    return 0;  27.}  
//   �����������û��ʲô�£����ǰ�һ��handle�ṹ��ͨ��d_node������ֱ����ӵ�input_dev��h_list,input_handler��h_list�ϡ��Ժ�ͨ�����h_list�Ϳ��Ա�����ص�input_handle�ˡ�
//3. input_register_handler ע��һ��input_handler�ṹ��

 
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
22.        //input_table��ÿ��ע���handler���Ὣ�Լ����浽�������ֵΪhandler->minor����5Ϊ��Ҳ���ǳ���32   23.        //Ϊʲô�������أ���Ϊÿ��handler���ᴦ�����32��input_dev������Ҫ��minor��32Ϊ��������,���minor�Ǵ�������handler��MINOR_BASE   24.        //ÿһ��handler����һ����һ��MINOR_BASE����evdevΪ��,EVDEV_MINOR_BASE = 64,���Կ���ϵͳ�ܹ�����ע��8��handler   25.    list_add_tail(&handler->node, &input_handler_list);  
26.        //���ӵ�input_handler_list������   27.    list_for_each_entry(dev, &input_dev_list, node)  
28.        input_attach_handler(dev, handler);  
29.        //������ԣ�������α���input_dev����ע��input_dev����һ����   30.    input_wakeup_procfs_readers();  
31.  
32.  
33. out:  
34.    mutex_unlock(&input_mutex);  
35.    return retval;  36.}  
//    ���������ʵ��input_register_device��ͬС�죬����ע�ᣬ��Ҫ��ԡ�
//��ƪ������Դ�� Linux������վ(www.linuxidc.com)  ԭ�����ӣ�http://www.linuxidc.com/Linux/2011-09/43187p2.htm
//
//
//һ.  ������ϵͳ���ķ�����
//
//    1.������ϵͳ���Ķ�Ӧ��/drivers/input/input.c�ļ�,���Ҳ����Ϊһ��ģ��ע�ᵽ�ں˵ġ��������ȷ���ģ���ʼ��������
//
 
 
1.static int __init input_init(void)  
2.{  
3.    int err;  4.  
5.    input_init_abs_bypass();  
6.        //�����ʱû�з�������ʲô��   7.    err = class_register(&input_class);  
8.        //���ں�ע��һ���࣬����linux�豸ģ�͡�ע������/sys/class�������inputĿ¼   9.    if (err) {  10.        printk(KERN_ERR "input: unable to register input_dev class\n");  11.        return err;  12.    }  
13.  
14.    err = input_proc_init();  
15.        //��proc�ļ�ϵͳ�йأ���ʱ����   16.    if (err)  17.        goto fail1;  18.  
19.  
20.    err = register_chrdev(INPUT_MAJOR, "input", &input_fops);  21.        //ע���ַ��豸���ӿ���2.4�ں˵ġ������豸��INPUT_MAJOR,���豸��0-255,ע��266���豸��˵��input�豸���ֻ����255��   22.    if (err) {  23.        printk(KERN_ERR "input: unable to register char major %d", INPUT_MAJOR);  24.        goto fail2;  25.    }  
26.  
27.    return 0;  28.  
29. fail2: input_proc_exit();  
30. fail1: class_unregister(&input_class);  
3/1.    return err;  32.}    
//    ���������Ҫ��ע�����ַ��豸������������豸��ԭ����һ��������input�豸Ҳ��һ���ַ��豸��ֻ������������������������ϵͳ����������Կ�������linux�豸��������жิ�ӣ����Ƕ�����һЩ������������ɵģ�����ldd3�����Ļ�����������ģ�͡� 
//    2. ������ϵͳ�ĺ����������ֶ����ṩ�Ľӿڣ����������¼�����㣬�������������㡣
//    ���¶�������Ľӿ���Ҫ�У�
//    input_allocate_device    ���������Ҫ�Ƿ���һ��input_dev�ӿڣ�����ʼ��һЩ�����ĳ�Ա����������ǲ��ܼ���kmalloc����input_dev�ṹ��ԭ����Ϊȱ����һЩ��ʼ����
//    input_unregister_device  ע��һ��input�豸
//    input_event              �����������Ҫ������������input��ϵͳ���ı����¼��ĺ��������¼����ݹ������ٷ�����
//    input_allocate_device    ���䲢��ʼ��һ��input_dev�ṹ
//    ���϶��¼������ӿ���Ҫ�У�
//    input_register_handler   ע��һ���¼�������
//    input_register_handle    ע��һ��input_handle�ṹ
//��ƪ������Դ�� Linux������վ(www.linuxidc.com)  ԭ�����ӣ�http://www.linuxidc.com/Linux/2011-09/43187p3.htm
//
//
//��.  �¼�������������evdev�¼�������Ϊ����
//    1.�¼���������û������������ϵͳ���Ĵ򽻵��������������������һ���ں��кü����¼�����������evdev mousedev jotdev��evdev�¼����������Դ������е��¼������������������õ���������������������¼���������ʵ�֡���Ҳ����Ϊģ��ע�ᵽ�ں��еģ����ȷ�������ģ���ʼ�������� 
//
/
 
1.static int __init evdev_init(void)  
2.{  
3.    return input_register_handler(&evdev_handler);  4.}  
//   ģ���ʼ�������͵���һ��ע��handler��������evdev_handlerע�ᵽϵͳ�С�
//    2.��Ҫ���ݽṹ
//    ��1�� evdev�豸�ṹ
//
 
1.struct evdev {  
2.    int exist;  3.    int open;           //�򿪱�־   4.    int minor;          //���豸��   5.    struct input_handle handle;  //������input_handle   6.    wait_queue_head_t wait;      //�ȴ����У������̶�ȡ�豸����û���¼�������ʱ�򣬽��̾ͻ�˯��������   7.    struct evdev_client *grab;   //ǿ�ư󶨵�evdev_client�ṹ������ṹ�����ٷ���   8.    struct list_head client_list;  //evdev_client ������˵��һ��evdev�豸���Դ�����evdev_client�������ж�����̷���evdev�豸   9.    spinlock_t client_lock; /* protects client_list */  10.    struct mutex mutex;  11.    struct device dev;       //device�ṹ��˵������һ���豸�ṹ   12.};  
//    evdev�ṹ������Գɹ���ʱ�����ɣ���handler->connect���ɣ���Ӧ�豸�ļ�Ϊ/class/input/event(n)���紥����������event0������豸���û��ռ�Ҫ���ʵ��豸�������������һ�������豸����Ϊû�ж�Ӧ��Ӳ��������ͨ��handle->dev �Ϳ����ҵ�input_dev�ṹ��������Ӧ�Ŵ��������豸�ļ�Ϊ/class/input/input0������豸�ṹ����֮�󱣴���evdev_table�У�
//    ����ֵ��minor
//   ��2�� evdev�û��˽ṹ

 
1.struct evdev_client {  
2.    struct input_event buffer[EVDEV_BUFFER_SIZE];    3.        //�����һ��input_event���ݽṹ�����飬input_event����һ���¼���������Ա�����ͣ�type�������루code����ֵ��value��   4.    int head;              //���buffer���������   5.    int tail;              //���buffer�������������head��tail��ȵ�ʱ��˵��û���¼�   6.    spinlock_t buffer_lock; /* protects access to buffer, head and tail */  7.    struct fasync_struct *fasync;  //�첽֪ͨ����   8.    struct evdev *evdev;           //evdev�豸   9.    struct list_head node;         // evdev_client ������   10.};  
//   ����ṹ�ڽ��̴�event0�豸��ʱ�����evdev��open��������open�д�������ṹ������ʼ�����ڹر��豸�ļ���ʱ���ͷ�����ṹ��
//   3.��Ҫ����
//   ��1��evdev�豸�򿪺���

 
1.static int evdev_open(struct inode *inode, struct file *file)  
2.{  
3.    struct evdev *evdev;  4.    struct evdev_client *client;  5.    int i = iminor(inode) - EVDEV_MINOR_BASE;  6.    int error;  7.  
8.  
9.    if (i >= EVDEV_MINORS)  10.        return -ENODEV;  11.  
12.  
13.    error = mutex_lock_interruptible(&evdev_table_mutex);  
14.    if (error)  15.        return error;  16.    evdev = evdev_table[i];  
17.        //�õ�evdev�豸�ṹ,ÿ�ε���evdev_connect��Գɹ��󶼻�ѷ����evdev�ṹ��minorΪ������������evdev_table������   18.    if (evdev)  19.        get_device(&evdev->dev);  //����device���ü���   20.    mutex_unlock(&evdev_table_mutex);  
21.  
22.  
23.    if (!evdev)  24.        return -ENODEV;  25.  
26.  
27.    client = kzalloc(sizeof(struct evdev_client), GFP_KERNEL);  //�����û��˽ṹ   28.    if (!client) {  29.        error = -ENOMEM;  
30.        goto err_put_evdev;  31.    }  
32.  
33.  
34.    spin_lock_init(&client->buffer_lock);  
35.    client->evdev = evdev;    //ʹ�û�����evdev�豸�ṹ��ϵ����   36.    evdev_attach_client(evdev, client);  
37.        //������������ľ��ǰ�client���ӵ�evdev��client������   38.    error = evdev_open_device(evdev);  
39.        //����������豸���кܶ����ã�������ϸ����   40.    if (error)  41.        goto err_free_client;  42.  
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
//   ��2��evdev�豸�򿪺���evdev_open_device����evdev_open���á�

 
1.static int evdev_open_device(struct evdev *evdev)  
2.{  
3.    int retval;  4.  
5.  
6.    retval = mutex_lock_interruptible(&evdev->mutex);  
7.    if (retval)  8.        return retval;  9.  
10.  
11.    if (!evdev->exist)  12.        retval = -ENODEV;  
13.        //�ж��豸�ṹ�Ƿ���ڣ���evdev_connect�г�ʼ���˳�ԱΪ1   14.    else if (!evdev->open++) {  15.        retval = input_open_device(&evdev->handle);  
16.        if (retval)  17.            evdev->open--;  
18.    }  
19.        //evdev->open����ṹ��ʱ��û�г�ʼ����Ĭ��Ϊ0��Ҳ����û�д򿪣�ÿ�δ򿪶����1   20.    mutex_unlock(&evdev->mutex);  
21.    return retval;  22.}  
 //   �˺������жϽṹ����������Ҫ������input_open_device�������������ϵͳ���ĺ�����������input.c�У�����������������

 
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
19.        //��handle�Ĵ򿪼�����1��ע���evdev��open������   20.    if (!dev->users++ && dev->open)  21.        retval = dev->open(dev);  
22.        //�����input_devû�н��������ã����Ҷ�����open�������͵���open����   23.    if (retval) {    //retval = 1 ˵��û�д򿪳ɹ�   24.        dev->users--;    
25.        if (!--handle->open) {  //˵���������Ľ����Ѿ��������handle   26.            /* 27.             * Make sure we are not delivering any more events 
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
   ��3������������ evdev_read

 
1.static ssize_t evdev_read(struct file *file, char __user *buffer,  
2.              size_t count, loff_t *ppos)  3.{  
4.    struct evdev_client *client = file->private_data;    //����ͻ��˽ṹ�ڴ򿪵�ʱ����䲢������file->private_data��   5.    struct evdev *evdev = client->evdev;  6.    struct input_event event;  7.    int retval;  8.  
9.  
10.    if (count < input_event_size())  11.        return -EINVAL;  12.        //���������ʾ���û�����ÿ�ζ�ȡ�豸���ֽ�������Ҫ����input_event�ṹ�Ĵ�С   13.    if (client->head == client->tail && evdev->exist &&  14.        (file->f_flags & O_NONBLOCK))  
15.        return -EAGAIN;  16.        //head����tail˵��Ŀǰ��û���¼�����������������˷�����������������̷���   17.    retval = wait_event_interruptible(evdev->wait,  
18.        client->head != client->tail || !evdev->exist);  
19.        //û���¼��ͻ�˯��evdev�ĵȴ��������ˣ��ȴ����������¼����������豸�������ˣ��豸�رյ�ʱ���������־��   20.    if (retval)  21.        return retval;  22.        //�����ִ�������������˵�����¼��������ߣ��豸���ر��ˣ������ں˷�������ֹ�ź�   23.    if (!evdev->exist)  24.        return -ENODEV;  25.  
26.  
27.    while (retval + input_event_size() <= count &&  28.           evdev_fetch_next_event(client, &event)) {  
29.        // evdev_fetch_next_event�����������client�����input_event buffer����   30.        if (input_event_to_user(buffer + retval, &event))  31.        //���¼����Ƶ��û��ռ�   32.            return -EFAULT;  33.  
34.  
35.        retval += input_event_size();  
36.    }  
37.  
38.    return retval;   //���ظ��Ƶ������ֽ���   39.}  




//��. �¼����ݹ��̣���s3c2410_tsΪ����
//   1. �¼�����
//    �����´�����ʱ�����봥���������жϣ���ʼadת����adת����ɽ���ad����жϣ�������ն��н��¼����ͳ�ȥ������
//    input_report_abs(dev, ABS_X, xp); 
//
//    input_report_abs(dev, ABS_Y, yp); ���������������� input_event(dev, EV_ABS, code, value)
//    ���е��¼����溯�����������������
//   2. �¼�����
//   ��1�� input_event �����������������������input.c��

 
1.void input_event(struct input_dev *dev,  
2.         unsigned int type, unsigned int code, int value)  3.{  
4.    unsigned long flags;  5.  
6.  
7.    if (is_event_supported(type, dev->evbit, EV_MAX)) {  8.        //�ж��Ƿ�֧�ִ����¼����ͺ��¼������еı�������   9.        spin_lock_irqsave(&dev->event_lock, flags);  
10.        add_input_randomness(type, code, value);  
11.        //��ϵͳ����س��й��ף���Ϊ���Ҳ��һ���������   12.        input_handle_event(dev, type, code, value);  
13.        //����������¼�����Ĺؼ�������������ϸ����   14.        spin_unlock_irqrestore(&dev->event_lock, flags);  
15.    }  
16.}   
   ��2�� input_handle_event �����������������������input.c��

 
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
//   ���������Ҫ�Ǹ����¼����͵Ĳ�ͬ������Ӧ�Ĵ�������֮����EV_KEY���ͣ������������¼����ݹ�ϵ����ֻҪ���ģ�disposition������¼�����ķ�ʽ��Ĭ�ϵ���INPUT_IGNORE_EVENT����������¼��������INPUT_PASS_TO_HANDLERS���Ǵ��ݸ��¼��������������INPUT_PASS_TO_DEVICE�����Ǵ��ݸ��豸��������������û�ж���������������input_pass_event������

 
1.static void input_pass_event(struct input_dev *dev,  
2.                 unsigned int type, unsigned int code, int value)  3.{  
4.    struct input_handle *handle;  5.  
6.  
7.    rcu_read_lock();  
8.  
9.  
10.    handle = rcu_dereference(dev->grab);  //����ǰ󶨵�handle������ð󶨵�handler->event����   11.    if (handle)  12.        handle->handler->event(handle, type, code, value);  
13.    else  14.        //���û�а󶨣������dev��h_list����Ѱ��handle�����handle�Ѿ��򿪣�˵���н��̶�ȡ�豸������evdev��   15.        list_for_each_entry_rcu(handle, &dev->h_list, d_node)  
16.            if (handle->open)  17.                handle->handler->event(handle,  
18.                            type, code, value);  
19.        // ������ص��¼���������event�����������¼��Ĵ���   20.    rcu_read_unlock();  
21.}  
//������� evdev�¼���������event����

 
1.static void evdev_event(struct input_handle *handle,  
2.            unsigned int type, unsigned int code, int value)  3.{  
4.    struct evdev *evdev = handle->private;  5.    struct evdev_client *client;  6.    struct input_event event;  7.  
8.  
9.    do_gettimeofday(&event.time);  
10.    event.type = type;  
11.    event.code = code;  
12.    event.value = value;  
13.        //�����������¼�����ֵ��input_event�ṹ   14.    rcu_read_lock();  
15.  
16.  
17.    client = rcu_dereference(evdev->grab);  
18.        //���evdev����client��ô����������ͻ��ˣ�����������û�а�   19.    if (client)  20.        evdev_pass_event(client, &event);  
21.    else  22.        //����client��������evdev_pass_event����   23.        list_for_each_entry_rcu(client, &evdev->client_list, node)  
24.            evdev_pass_event(client, &event);  
25.  
26.  
27.    rcu_read_unlock();  
28.  
29.  
30.    wake_up_interruptible(&evdev->wait); //���ѵȴ��Ľ���   31.}  
//������� evdev_pass_event ����

 
1.static void evdev_pass_event(struct evdev_client *client,  
2.                 struct input_event *event)  3.{  
4.    /* 5.     * Interrupts are disabled, just acquire the lock 
6.     */  
7.    spin_lock(&client->buffer_lock);  
8.    client->buffer[client->head++] = *event;   //���¼���ֵ���ͻ��˵�input_event ����   9.    client->head &= EVDEV_BUFFER_SIZE - 1;  
10.    spin_unlock(&client->buffer_lock);  
11.  
12.  
13.    kill_fasync(&client->fasync, SIGIO, POLL_IN);  
14.}  
//���Կ����� evdev_pass_event�������ս��¼����ݸ����û��˵�client�ṹ�е�input_event�����У�ֻ�轫���input_event���鸴�Ƹ��û��ռ䣬���̾����յ����������µ���Ϣ�ˡ����崦���ɾ����Ӧ�ó�������ɡ�
//��ƪ������Դ�� Linux������վ(www.linuxidc.com)  ԭ�����ӣ�http://www.linuxidc.com/Linux/2011-09/43187p5.htm