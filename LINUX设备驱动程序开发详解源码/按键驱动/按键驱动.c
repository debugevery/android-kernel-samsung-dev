//12.1.2  ���������е����ݽṹ
//�豸��������ҪҪ��Ƶ����ݽṹ���豸�ṹ�壬�������豸�ṹ����Ӧ����һ������������Ϊ��ΰ��������޷�����ʱ����
//�������øû��������水�������⣬�ڰ����豸�ṹ���У�����������״̬��־��һ��ʵ�ֹ�����Ҫ�����ĵȴ����С�cdev
//�ṹ�塣Ϊ��ʵ�������ʱ����ʱ��Ҳ�Ǳ�Ҫ�ģ������Բ��������豸�ṹ���С������嵥12.1�����˰����豸�ṹ�弰��
//ʱ����
//�����嵥12.1  �����������豸�ṹ�塢��ʱ��
#define MAX_KEY_BUF 16 //������������С
typedef unsigned char KEY_RET;
//�豸�ṹ�壺
 typedef struct keydev
{
    struct cdev cdev;     //cdev�ṹ��
    unsigned int keyStatus[KEY_NUM];// //4�������İ���״̬
    KEY_RET buf[MAX_KEY_BUF]; //����������
    unsigned int head, tail; //����������ͷ��β
    wait_queue_head_t wq; //�ȴ�����ͷ
 } KEY_DEV;
 static struct timer_list key_timer[KEY_NUM];//4//����ȥ����ʱ��
//�ڰ����豸�����У�����һ���ṹ���¼ÿ����������Ӧ���ж�/GPIO���ż���ֵ��������嵥12.2��ʾ��
//�����嵥12.2  ����Ӳ����Դ����ֵ��Ϣ�ṹ��
  static struct key_info
  {
    int irq_no;     //�жϺ�
    unsigned int gpio_port; //GPIO�˿�
    int key_no;    //��ֵ
  } key_info_tab[4] =
  {
     /*������ʹ�õ�CPU��Դ*/
    {
     IRQ_EINT10, GPIO_G2, 1
   }
 ��
   {
   IRQ_EINT13, GPIO_G5, 2
   }
   ,
   {
     IRQ_EINT14, GPIO_G6, 3
   }
   ,
   {
     IRQ_EINT15, GPIO_G7, 4
   }
   ,
 };
//�����豸�������ļ������ṹ��������嵥12.3��ʾ����Ҫʵ���˴򿪡��ͷźͶ���������Ϊ����ֻ��һ�������豸������
//������д������
//�����嵥12.3  �����豸�����ļ������ṹ��
static struct file_operations s3c2410_key_fops =
 {
  owner: THIS_MODULE, 
  open: s3c2410_key_open,  //�����豸
   release: s3c2410_key_release,  //�ر��豸
  read: s3c2410_key_read,  //��ȡ�����ļ�ֵ
};
//12.1.3  ����������ģ����غ�ж�غ���
//�����豸��Ϊһ���ַ��豸������ģ����غ�ж�غ����зֱ�������豸��������ͷš�cdev����Ӻ�ɾ����Ϊ����ģ���
//�غ����У����������жϡ���ʼ����ʱ���͵ȴ����еȣ�ģ��ж�غ�������෴����Ϊ�������嵥12.4��12.5�ֱ�����˰�
//���豸������ģ����غ�ж�غ����������嵥12.6��12.7�ֱ������ģ����غ�ж�������õ�������ͷ�4���жϵĺ�����
//�����嵥12.4  �����豸������ģ����غ���
  static int __init s3c2410_key_init(void)
 {
   ...//�����豸�ţ����cdev
  
    request_irqs(); //ע���жϺ���������request_irq����
   keydev.head = keydev.tail = 0; //��ʼ���ṹ��
   for (i = 0; i < KEY_NUM; i++)
     keydev.keyStatus[i] = KEYSTATUS_UP;
   init_waitqueue_head(&(keydev.wq)); //�ȴ�����ͷ

 //��ʼ����ʱ����ʵ�������ȥ����
   for (i = 0; i < KEY_NUM; i++)
     setup_timer(&key_timer[i], key_timer_handler, i);
   //�Ѱ����������Ϊ���붨ʱ���������Ĳ���
 }
//�����嵥12.5  �����豸������ģ��ж�غ���
static void __exit s3c2410_key_exit(void)
{ 
 free_irqs(); //ע���ж�
 ...//�ͷ��豸�ţ�ɾ��cdev 
}
//�����嵥12.6  �����豸�������ж����뺯��
/*����ϵͳ�жϣ��жϷ�ʽΪ�½��ش���*/
static int request_irqs(void)
{
  struct key_info *k;
  int i;
  for (i = 0; i < sizeof(key_info_tab) / sizeof(key_info_tab[1]); i++)//��װ�����жϺ���
  {
    k = key_info_tab + i;
    set_external_irq(k->irq_no, EXT_LOWLEVEL, GPIO_PULLUP_DIS);
                   //���õ͵�ƽ������û������������������������ʦд��
   if (request_irq(k->irq_no, &buttons_irq, SA_INTERRUPT, DEVICE_NAME, i))  
     {//�����жϣ������������Ϊ���������жϷ������
       return  - 1;
     }
   }
   return 0;
 }
//�����嵥12.7  �����豸�������ж��ͷź���
/*�ͷ��ж�*/
static void free_irqs(void)
{
  struct key_info *k;
  int i;
  for (i = 0; i < sizeof(key_info_tab) / sizeof(key_info_tab[1]); i++)
  {
    k = key_info_tab + i;
    free_irq(k->irq_no, buttons_irq); //�ͷ��ж�
   }
 }
//12.1.4  �����豸�����жϡ���ʱ���������
//�ڼ������º󣬽������жϣ����жϴ�������У�Ӧ�ùر��жϽ����ѯģʽ���ӳ�20ms��ʵ��ȥ������������嵥12.8��
//ʾ������жϴ������ֻ�������벿���޵װ벿�
�
//�����嵥12.8  �����豸�������жϴ������
 static void s3c2410_eint_key(int irq, void *dev_id, struct pt_regs *reg)
{
 int key = dev_id;
  disable_irq(key_info_tab[key].irq_no); //���жϣ�ת���ѯģʽ

 keydev.keyStatus[key] = KEYSTATUS_DOWNX;//״̬Ϊ����
 key_timer[key].expires == jiffies + KEY_TIMER_DELAY1;//�ӳ�
 add_timer(&key_timer[key]); //������ʱ��
}
//�ڶ�ʱ����������У���ѯ�����Ƿ���Ȼ�����£�����Ǳ����µ�״̬���򽫸ð�����¼�뻺������ͬʱ�����µĶ�ʱ���ӳ�
//���ӳ�һ�������ȥ��������ʱ�䣨��100ms����ÿ�ζ�ʱ�����ں󣬲�ѯ�����Ƿ���Ȼ���ڰ���״̬������ǣ�����������
//�µ�100ms�ӳ٣�����ѯ���Ѿ�û�а��£����϶�����̧�����ʱ��Ӧ�ÿ�����Ӧ�������жϣ��ȴ��µİ�����ÿ�μ�¼��
//�ļ�ֵʱ��Ӧ���ѵȴ����С���ʱ������������ͼ12.3��ʾ�������嵥��12.9��ʾ��

//�����嵥12.9  �����豸�����Ķ�ʱ��������
static void key_timer_handler(unsigned long data)
{
  int key = data;
  if (ISKEY_DOWN(key))
  {
    if (keydev.keyStatus[key] == KEYSTATUS_DOWNX)
    //���жϽ���
    {
      keydev.keyStatus[key] = KEYSTATUS_DOWN;
       key_timer[key].expires == jiffies + KEY_TIMER_DELAY; //�ӳ�
     keyEvent();   //��¼��ֵ�����ѵȴ�����
       add_timer(&key_timer[key]);
     }
     else
     {
       key_timer[key].expires == jiffies + KEY_TIMER_DELAY; //�ӳ�
       add_timer(&key_timer[key]);
     }
   }
   else       //����̧��
{
     keydev.keyStatus[key] = KEYSTATUS_UP;
     enable_irq(key_info_tab[key].irq_no);
  }
}

//ͼ12.3  ��ʱ������������
//12.1.5  �����豸�����Ĵ򿪡��ͷź���
//�����豸�����Ĵ򿪺��ͷź����Ƚϼ򵥣���Ҫ������keydev.head��keydev.tail�Ͱ����¼�����ָ��keyEvent��ֵ��������嵥12.10��ʾ��

///�����嵥12.10  �����豸�����Ĵ򿪡��ͷź���
static int s3c2410_key_open(struct inode *inode, struct file *filp)
{
  keydev.head = keydev.tail = 0; //��հ�������������
  keyEvent = keyEvent_raw; //����ָ��ָ�򰴼�������keyEvent_raw
  return 0;
}

static int s3c2410_key_release(struct inode *inode, struct file *filp)
{
   keyEvent = keyEvent_dummy; //����ָ��ָ��պ���
 return 0;
 }
//12.1.6  �����豸����������
//�����嵥12.11�����˰����豸�����Ķ������������豸�����Ķ�������Ҫ�ṩ�԰����豸�ṹ���л������Ķ������Ƶ��û�
//�ռ䡣��keydev.head ! = keydev.tailʱ����ζ�Ż����������ݣ�ʹ��copy_to_user()�������û��ռ䣬���򣬸����û��ռ�
//�����������Ƿ�����������Ϊ�������������
//l      �����÷�������������Ϊû�а������棬ֱ�ӷ���- EAGAIN��
//l      ������������������keydev.wq�ȴ�������˯�ߣ�ֱ���а�������¼�뻺�����󱻻��ѡ�

//�����嵥12.�����豸�����Ķ�����
static ssize_t s3c2410_key_read(struct file *filp, char *buf, ssize_t count,
  loff_t*ppos)
{
  retry: if (keydev.head != keydev.tail)  //��ǰѭ��������������
  		{
   			 key_ret = keyRead(); //��ȡ����
    			copy_to_user(..); //�����ݴ��ں˿ռ䴫�͵��û��ռ�
 		 }
 	   else
 		{
 			if (filp->f_flags &O_NONBLOCK) //���û����÷�������ʽ��ȡ
    			 {
       			return  - EAGAIN;
     			}
    			 interruptible_sleep_on(&(keydev.wq));
     			  //�û�����������ʽ��ȡ�����øú���ʹ����˯�ߣ���������������У���û��ʹ�ô˺���������ֱ���ֹ�����״̬�л���P178
    			 goto	retry;
  		 }
	return 0;
 }
//MODULE_AUTHOR("Song Baohua");
//MODULE_LICENSE("Dual BSD/GPL");
module_param(globalfifo_major, int, S_IRUGO);
//module_init(globalfifo_init);
//module_exit(globalfifo_exit);

//��󣬽���һ�´����嵥12.9��11�е�keyEvent()�����ʹ����嵥12.11��keyRead()���������豸�����Ĵ򿪺����У�
//keyEvent����ֵΪkeyEvent_raw�����������ɼ�¼��ֵ����ʹ��wait_up_interrupt(&(keydev.wq))��份��
//s3c2410_key_read()��17�����ڴ��ĵȴ����С���keyRead()������ֱ�ӴӰ����������ж�ȡ��ֵ��
