//12.1.2  °´¼üÇı¶¯ÖĞµÄÊı¾İ½á¹¹
//Éè±¸Çı¶¯ÖĞÖ÷ÒªÒªÉè¼ÆµÄÊı¾İ½á¹¹ÊÇÉè±¸½á¹¹Ìå£¬°´¼üµÄÉè±¸½á¹¹ÌåÖĞÓ¦°üº¬Ò»¸ö»º³åÇø£¬ÒòÎª¶à´Î°´¼ü¿ÉÄÜÎŞ·¨±»¼°Ê±´¦Àí
//£¬¿ÉÒÔÓÃ¸Ã»º³åÇø»º´æ°´¼ü¡£´ËÍâ£¬ÔÚ°´¼üÉè±¸½á¹¹ÌåÖĞ£¬»¹°üº¬°´¼ü×´Ì¬±êÖ¾ºÍÒ»¸öÊµÏÖ¹ı³ÌÖĞÒª½èÖúµÄµÈ´ı¶ÓÁĞ¡¢cdev
//½á¹¹Ìå¡£ÎªÁËÊµÏÖÈí¼şÑÓÊ±£¬¶¨Ê±Æ÷Ò²ÊÇ±ØÒªµÄ£¬µ«¿ÉÒÔ²»°üº¬ÔÚÉè±¸½á¹¹ÌåÖĞ¡£´úÂëÇåµ¥12.1¸ø³öÁË°´¼üÉè±¸½á¹¹Ìå¼°¶¨
//Ê±Æ÷¡£
//´úÂëÇåµ¥12.1  °´¼üÇı¶¯µÄÉè±¸½á¹¹Ìå¡¢¶¨Ê±Æ÷
#define MAX_KEY_BUF 16 //°´¼ü»º³åÇø´óĞ¡
typedef unsigned char KEY_RET;
//Éè±¸½á¹¹Ìå£º
 typedef struct keydev
{
    struct cdev cdev;     //cdev½á¹¹Ìå
    unsigned int keyStatus[KEY_NUM];// //4¸ö°´¼üµÄ°´¼ü×´Ì¬
    KEY_RET buf[MAX_KEY_BUF]; //°´¼ü»º³åÇø
    unsigned int head, tail; //°´¼ü»º³åÇøÍ·ºÍÎ²
    wait_queue_head_t wq; //µÈ´ı¶ÓÁĞÍ·
 } KEY_DEV;
 static struct timer_list key_timer[KEY_NUM];//4//°´¼üÈ¥¶¶¶¨Ê±Æ÷
//ÔÚ°´¼üÉè±¸Çı¶¯ÖĞ£¬¿ÉÓÃÒ»¸ö½á¹¹Ìå¼ÇÂ¼Ã¿¸ö°´¼üËù¶ÔÓ¦µÄÖĞ¶Ï/GPIOÒı½Å¼°¼üÖµ£¬Èç´úÂëÇåµ¥12.2ËùÊ¾¡£
//´úÂëÇåµ¥12.2  °´¼üÓ²¼ş×ÊÔ´¡¢¼üÖµĞÅÏ¢½á¹¹Ìå
  static struct key_info
  {
    int irq_no;     //ÖĞ¶ÏºÅ
    unsigned int gpio_port; //GPIO¶Ë¿Ú
    int key_no;    //¼üÖµ
  } key_info_tab[4] =
  {
     /*°´¼üËùÊ¹ÓÃµÄCPU×ÊÔ´*/
    {
     IRQ_EINT10, GPIO_G2, 1
   }
 £¬
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
//°´¼üÉè±¸Çı¶¯µÄÎÄ¼ş²Ù×÷½á¹¹ÌåÈç´úÂëÇåµ¥12.3ËùÊ¾£¬Ö÷ÒªÊµÏÖÁË´ò¿ª¡¢ÊÍ·ÅºÍ¶Áº¯Êı£¬ÒòÎª°´¼üÖ»ÊÇÒ»¸öÊäÈëÉè±¸£¬ËùÒÔ
//²»´æÔÚĞ´º¯Êı¡£
//´úÂëÇåµ¥12.3  °´¼üÉè±¸Çı¶¯ÎÄ¼ş²Ù×÷½á¹¹Ìå
static struct file_operations s3c2410_key_fops =
 {
  owner: THIS_MODULE, 
  open: s3c2410_key_open,  //Æô¶¯Éè±¸
   release: s3c2410_key_release,  //¹Ø±ÕÉè±¸
  read: s3c2410_key_read,  //¶ÁÈ¡°´¼üµÄ¼üÖµ
};
//12.1.3  °´¼üÇı¶¯µÄÄ£¿é¼ÓÔØºÍĞ¶ÔØº¯Êı
//°´¼üÉè±¸×÷ÎªÒ»ÖÖ×Ö·ûÉè±¸£¬ÔÚÆäÄ£¿é¼ÓÔØºÍĞ¶ÔØº¯ÊıÖĞ·Ö±ğ°üº¬ÁËÉè±¸ºÅÉêÇëºÍÊÍ·Å¡¢cdevµÄÌí¼ÓºÍÉ¾³ıĞĞÎª£¬ÔÚÄ£¿é¼Ó
//ÔØº¯ÊıÖĞ£¬»¹ĞèÉêÇëÖĞ¶Ï¡¢³õÊ¼»¯¶¨Ê±Æ÷ºÍµÈ´ı¶ÓÁĞµÈ£¬Ä£¿éĞ¶ÔØº¯ÊıÍê³ÉÏà·´µÄĞĞÎª£¬´úÂëÇåµ¥12.4ºÍ12.5·Ö±ğ¸ø³öÁË°´
//¼üÉè±¸Çı¶¯µÄÄ£¿é¼ÓÔØºÍĞ¶ÔØº¯Êı£¬´úÂëÇåµ¥12.6ºÍ12.7·Ö±ğ¸ø³öÁËÄ£¿é¼ÓÔØºÍĞ¶ÔØËùµ÷ÓÃµÄÉêÇëºÍÊÍ·Å4¸öÖĞ¶ÏµÄº¯Êı¡£
//´úÂëÇåµ¥12.4  °´¼üÉè±¸Çı¶¯µÄÄ£¿é¼ÓÔØº¯Êı
  static int __init s3c2410_key_init(void)
 {
   ...//ÉêÇëÉè±¸ºÅ£¬Ìí¼Ócdev
  
    request_irqs(); //×¢²áÖĞ¶Ïº¯Êı£¬²»ÊÇrequest_irqº¯Êı
   keydev.head = keydev.tail = 0; //³õÊ¼»¯½á¹¹Ìå
   for (i = 0; i < KEY_NUM; i++)
     keydev.keyStatus[i] = KEYSTATUS_UP;
   init_waitqueue_head(&(keydev.wq)); //µÈ´ı¶ÓÁĞÍ·

 //³õÊ¼»¯¶¨Ê±Æ÷£¬ÊµÏÖÈí¼şµÄÈ¥¶¶¶¯
   for (i = 0; i < KEY_NUM; i++)
     setup_timer(&key_timer[i], key_timer_handler, i);
   //°Ñ°´¼üµÄĞòºÅ×÷Îª´«Èë¶¨Ê±Æ÷´¦Àíº¯ÊıµÄ²ÎÊı
 }
//´úÂëÇåµ¥12.5  °´¼üÉè±¸Çı¶¯µÄÄ£¿éĞ¶ÔØº¯Êı
static void __exit s3c2410_key_exit(void)
{ 
 free_irqs(); //×¢ÏúÖĞ¶Ï
 ...//ÊÍ·ÅÉè±¸ºÅ£¬É¾³ıcdev 
}
//´úÂëÇåµ¥12.6  °´¼üÉè±¸Çı¶¯µÄÖĞ¶ÏÉêÇëº¯Êı
/*ÉêÇëÏµÍ³ÖĞ¶Ï£¬ÖĞ¶Ï·½Ê½ÎªÏÂ½µÑØ´¥·¢*/
static int request_irqs(void)
{
  struct key_info *k;
  int i;
  for (i = 0; i < sizeof(key_info_tab) / sizeof(key_info_tab[1]); i++)//°²×°ËùÓĞÖĞ¶Ïº¯Êı
  {
    k = key_info_tab + i;
    set_external_irq(k->irq_no, EXT_LOWLEVEL, GPIO_PULLUP_DIS);
                   //ÉèÖÃµÍµçÆ½´¥·¢£¬Ã»ÓĞÕâ¸öº¯ÊıÊÇÓÉÇı¶¯Èí¼ş¹¤³ÌÊ¦Ğ´Âğ£¿
   if (request_irq(k->irq_no, &buttons_irq, SA_INTERRUPT, DEVICE_NAME, i))  
     {//ÉêÇëÖĞ¶Ï£¬½«°´¼üĞòºÅ×÷Îª²ÎÊı´«ÈëÖĞ¶Ï·şÎñ³ÌĞò
       return  - 1;
     }
   }
   return 0;
 }
//´úÂëÇåµ¥12.7  °´¼üÉè±¸Çı¶¯µÄÖĞ¶ÏÊÍ·Åº¯Êı
/*ÊÍ·ÅÖĞ¶Ï*/
static void free_irqs(void)
{
  struct key_info *k;
  int i;
  for (i = 0; i < sizeof(key_info_tab) / sizeof(key_info_tab[1]); i++)
  {
    k = key_info_tab + i;
    free_irq(k->irq_no, buttons_irq); //ÊÍ·ÅÖĞ¶Ï
   }
 }
//12.1.4  °´¼üÉè±¸Çı¶¯ÖĞ¶Ï¡¢¶¨Ê±Æ÷´¦Àí³ÌĞò
//ÔÚ¼ü±»°´ÏÂºó£¬½«·¢ÉúÖĞ¶Ï£¬ÔÚÖĞ¶Ï´¦Àí³ÌĞòÖĞ£¬Ó¦¸Ã¹Ø±ÕÖĞ¶Ï½øÈë²éÑ¯Ä£Ê½£¬ÑÓ³Ù20msÒÔÊµÏÖÈ¥¶¶¶¯£¬Èç´úÂëÇåµ¥12.8Ëù
//Ê¾£¬Õâ¸öÖĞ¶Ï´¦Àí¹ı³ÌÖ»°üº¬¶¥°ë²¿£¬ÎŞµ×°ë²¿¡
£
//´úÂëÇåµ¥12.8  °´¼üÉè±¸Çı¶¯µÄÖĞ¶Ï´¦Àí³ÌĞò
 static void s3c2410_eint_key(int irq, void *dev_id, struct pt_regs *reg)
{
 int key = dev_id;
  disable_irq(key_info_tab[key].irq_no); //¹ØÖĞ¶Ï£¬×ªÈë²éÑ¯Ä£Ê½

 keydev.keyStatus[key] = KEYSTATUS_DOWNX;//×´Ì¬Îª°´ÏÂ
 key_timer[key].expires == jiffies + KEY_TIMER_DELAY1;//ÑÓ³Ù
 add_timer(&key_timer[key]); //Æô¶¯¶¨Ê±Æ÷
}
//ÔÚ¶¨Ê±Æ÷´¦Àí³ÌĞòÖĞ£¬²éÑ¯°´¼üÊÇ·ñÈÔÈ»±»°´ÏÂ£¬Èç¹ûÊÇ±»°´ÏÂµÄ×´Ì¬£¬Ôò½«¸Ã°´¼ü¼ÇÂ¼Èë»º³åÇø¡£Í¬Ê±Æô¶¯ĞÂµÄ¶¨Ê±Æ÷ÑÓ³Ù
//£¬ÑÓ³ÙÒ»¸öÏà¶ÔÓÚÈ¥¶¶¸ü³¤µÄÊ±¼ä£¨Èç100ms£©£¬Ã¿´Î¶¨Ê±Æ÷µ½ÆÚºó£¬²éÑ¯°´¼üÊÇ·ñÈÔÈ»´¦ÓÚ°´ÏÂ×´Ì¬£¬Èç¹ûÊÇ£¬ÔòÖØĞÂÆôÓÃ
//ĞÂµÄ100msÑÓ³Ù£»Èô²éÑ¯µ½ÒÑ¾­Ã»ÓĞ°´ÏÂ£¬ÔòÈÏ¶¨¼üÒÑÌ§Æğ£¬Õâ¸öÊ±ºòÓ¦¸Ã¿ªÆô¶ÔÓ¦°´¼üµÄÖĞ¶Ï£¬µÈ´ıĞÂµÄ°´¼ü¡£Ã¿´Î¼ÇÂ¼ĞÂ
//µÄ¼üÖµÊ±£¬Ó¦»½ĞÑµÈ´ı¶ÓÁĞ¡£¶¨Ê±Æ÷´¦ÀíÁ÷³ÌÈçÍ¼12.3ËùÊ¾£¬´úÂëÇåµ¥Èç12.9ËùÊ¾¡£

//´úÂëÇåµ¥12.9  °´¼üÉè±¸Çı¶¯µÄ¶¨Ê±Æ÷´¦Àíº¯Êı
static void key_timer_handler(unsigned long data)
{
  int key = data;
  if (ISKEY_DOWN(key))
  {
    if (keydev.keyStatus[key] == KEYSTATUS_DOWNX)
    //´ÓÖĞ¶Ï½øÈë
    {
      keydev.keyStatus[key] = KEYSTATUS_DOWN;
       key_timer[key].expires == jiffies + KEY_TIMER_DELAY; //ÑÓ³Ù
     keyEvent();   //¼ÇÂ¼¼üÖµ£¬»½ĞÑµÈ´ı¶ÓÁĞ
       add_timer(&key_timer[key]);
     }
     else
     {
       key_timer[key].expires == jiffies + KEY_TIMER_DELAY; //ÑÓ³Ù
       add_timer(&key_timer[key]);
     }
   }
   else       //¼üÒÑÌ§Æğ
{
     keydev.keyStatus[key] = KEYSTATUS_UP;
     enable_irq(key_info_tab[key].irq_no);
  }
}

//Í¼12.3  ¶¨Ê±Æ÷´¦Àíº¯ÊıÁ÷³Ì
//12.1.5  °´¼üÉè±¸Çı¶¯µÄ´ò¿ª¡¢ÊÍ·Åº¯Êı
//°´¼üÉè±¸Çı¶¯µÄ´ò¿ªºÍÊÍ·Åº¯Êı±È½Ï¼òµ¥£¬Ö÷ÒªÊÇÉèÖÃkeydev.head¡¢keydev.tailºÍ°´¼üÊÂ¼şº¯ÊıÖ¸ÕëkeyEventµÄÖµ£¬Èç´úÂëÇåµ¥12.10ËùÊ¾¡£

///´úÂëÇåµ¥12.10  °´¼üÉè±¸Çı¶¯µÄ´ò¿ª¡¢ÊÍ·Åº¯Êı
static int s3c2410_key_open(struct inode *inode, struct file *filp)
{
  keydev.head = keydev.tail = 0; //Çå¿Õ°´¼ü¶¯×÷»º³åÇø
  keyEvent = keyEvent_raw; //º¯ÊıÖ¸ÕëÖ¸Ïò°´¼ü´¦Àíº¯ÊıkeyEvent_raw
  return 0;
}

static int s3c2410_key_release(struct inode *inode, struct file *filp)
{
   keyEvent = keyEvent_dummy; //º¯ÊıÖ¸ÕëÖ¸Ïò¿Õº¯Êı
 return 0;
 }
//12.1.6  °´¼üÉè±¸Çı¶¯¶Áº¯Êı
//´úÂëÇåµ¥12.11¸ø³öÁË°´¼üÉè±¸Çı¶¯µÄ¶Áº¯Êı£¬°´¼üÉè±¸Çı¶¯µÄ¶Áº¯ÊıÖ÷ÒªÌá¹©¶Ô°´¼üÉè±¸½á¹¹ÌåÖĞ»º³åÇøµÄ¶Á²¢¸´ÖÆµ½ÓÃ»§
//¿Õ¼ä¡£µ±keydev.head ! = keydev.tailÊ±£¬ÒâÎ¶×Å»º³åÇøÓĞÊı¾İ£¬Ê¹ÓÃcopy_to_user()¿½±´µ½ÓÃ»§¿Õ¼ä£¬·ñÔò£¬¸ù¾İÓÃ»§¿Õ¼ä
//ÊÇ×èÈû¶Á»¹ÊÇ·Ç×èÈû¶Á£¬·ÖÎªÈçÏÂÁ½ÖÖÇé¿ö¡£
//l      Èô²ÉÓÃ·Ç×èÈû¶Á£¬ÔòÒòÎªÃ»ÓĞ°´¼ü»º´æ£¬Ö±½Ó·µ»Ø- EAGAIN£»
//l      Èô²ÉÓÃ×èÈû¶Á£¬ÔòÔÚkeydev.wqµÈ´ı¶ÓÁĞÉÏË¯Ãß£¬Ö±µ½ÓĞ°´¼ü±»¼ÇÂ¼Èë»º³åÇøºó±»»½ĞÑ¡£

//´úÂëÇåµ¥12.°´¼üÉè±¸Çı¶¯µÄ¶Áº¯Êı
static ssize_t s3c2410_key_read(struct file *filp, char *buf, ssize_t count,
  loff_t*ppos)
{
  retry: if (keydev.head != keydev.tail)  //µ±Ç°Ñ­»·¶ÓÁĞÖĞÓĞÊı¾İ
  		{
   			 key_ret = keyRead(); //¶ÁÈ¡°´¼ü
    			copy_to_user(..); //°ÑÊı¾İ´ÓÄÚºË¿Õ¼ä´«ËÍµ½ÓÃ»§¿Õ¼ä
 		 }
 	   else
 		{
 			if (filp->f_flags &O_NONBLOCK) //ÈôÓÃ»§²ÉÓÃ·Ç×èÈû·½Ê½¶ÁÈ¡
    			 {
       			return  - EAGAIN;
     			}
    			 interruptible_sleep_on(&(keydev.wq));
     			  //ÓÃ»§²ÉÓÃ×èÈû·½Ê½¶ÁÈ¡£¬µ÷ÓÃ¸Ãº¯ÊıÊ¹½ø³ÌË¯Ãß£¬ÔÚĞí¶àÇı¶¯³ÌĞòÖĞ£¬²¢Ã»ÓĞÊ¹ÓÃ´Ëº¯Êı£¬¶øÊÇÖ±½ÓÊÖ¹¤½ø³Ì×´Ì¬ÇĞ»»¼ûP178
    			 goto	retry;
  		 }
	return 0;
 }
//MODULE_AUTHOR("Song Baohua");
//MODULE_LICENSE("Dual BSD/GPL");
module_param(globalfifo_major, int, S_IRUGO);
//module_init(globalfifo_init);
//module_exit(globalfifo_exit);

//×îºó£¬½âÊÍÒ»ÏÂ´úÂëÇåµ¥12.9µÚ11ĞĞµÄkeyEvent()º¯ÊıºÍ´úÂëÇåµ¥12.11µÄkeyRead()º¯Êı¡£ÔÚÉè±¸Çı¶¯µÄ´ò¿ªº¯ÊıÖĞ£¬
//keyEvent±»¸³ÖµÎªkeyEvent_raw£¬Õâ¸öº¯ÊıÍê³É¼ÇÂ¼¼üÖµ£¬²¢Ê¹ÓÃwait_up_interrupt(&(keydev.wq))Óï¾ä»½ĞÑ
//s3c2410_key_read()µÚ17ĞĞËùÆÚ´ıµÄµÈ´ı¶ÓÁĞ¡£¶økeyRead()º¯ÊıÔòÖ±½Ó´Ó°´¼ü»º³åÇøÖĞ¶ÁÈ¡¼üÖµ¡£
