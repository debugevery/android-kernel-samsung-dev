//¹ØÓÚLinuxÉè±¸Çý¶¯ÖÐglobalfifoÇý¶¯Àý×ÓµÄ¾«²ÊÎÊ´ð

/*globalfifo¶Áº¯Êý*/
static ssize_t globalfifo_read(struct file *filp, char __user *buf, size_t count,
  loff_t *ppos)
{
  int ret;
  struct globalfifo_dev *dev = filp->private_data; //»ñµÃÉè±¸½á¹¹ÌåÖ¸Õë

  DECLARE_WAITQUEUE(wait, current); //¶¨ÒåµÈ´ý¶ÓÁÐ


  down(&dev->sem); //´Ëº¯Êý°üº¬ÁË½øÈëË¯ÃßµÄ¶¯×÷Âð£¿

  add_wait_queue(&dev->r_wait, &wait); //ÎªºÎÒªÔÚ»ñµÃÐÅºÅÁ¿ºó½øÈë¶ÁµÈ´ý¶ÓÁÐÍ·£¿


  /* µÈ´ýFIFO·Ç¿Õ */
  while (dev->current_len == 0)
  {
    if (filp->f_flags &O_NONBLOCK) //?

    {
      ret = - EAGAIN; //?

      goto out;
    } 
    __set_current_state(TASK_INTERRUPTIBLE); //¸Ä±ä½ø³Ì×´Ì¬ÎªË¯Ãß

    up(&dev->sem);

    schedule(); //µ÷¶ÈÆäËû½ø³ÌÖ´ÐÐ

    if (signal_pending(current)) //?

    //Èç¹ûÊÇÒòÎªÐÅºÅ»½ÐÑ

    {
      ret = - ERESTARTSYS;
      goto out2;
    }

    down(&dev->sem);
  }

  /* ¿½±´µ½ÓÃ»§¿Õ¼ä */
  if (count > dev->current_len)
    count = dev->current_len;

  if (copy_to_user(buf, dev->mem, count))
  {
    ret = - EFAULT;
    goto out;
  }
  else
  {
    memcpy(dev->mem, dev->mem + count, dev->current_len - count); //fifoÊý¾ÝÇ°ÒÆ

    dev->current_len -= count; //ÓÐÐ§Êý¾Ý³¤¶È¼õÉÙ

    printk(KERN_INFO "read %d bytes(s),current_len:%d\n", count, dev->current_len);
     
    wake_up_interruptible(&dev->w_wait); //»½ÐÑÐ´µÈ´ý¶ÓÁÐ

    
    ret = count;
  }
  out: up(&dev->sem); //ÊÍ·ÅÐÅºÅÁ¿

  out2:remove_wait_queue(&dev->w_wait, &wait); //´Ó¸½ÊôµÄµÈ´ý¶ÓÁÐÍ·ÒÆ³ý

  set_current_state(TASK_RUNNING);
  return ret;
} 

 


Q:
//±¾ÈË¶Ô×èÈû²Ù×÷»¹ÊÇ²»ÄÜ½áºÏÕâ¸öÊµ¼ÊÀý×Ó¼ÓÒÔÀí½â¡£
//ÎÒÖ»ÄÜÀí½â£º´Ó½øÈëË¯Ãßwait_event()µ½Ë¯Ãß»½ÐÑwake_up()
//¿ÉÕâÀïÃ»ÓÐwait_event()Ïà¹Øº¯Êý£¬ÎªÊ²Ã´£¿
//ÁíÍâ£¬ÕâÀïµÄË¯Ãß¡¢µÈ´ý¶ÓÁÐ£¬ºÍÐÅºÅÁ¿ÓÖÓÐÊ²Ã´¹ØÏµ£¿£¿¿´Êé¶¼¿´ÔÎÁË£¡£¡

//A:

//Ê×ÏÈÓ¦´Ó×ÜÌåÉÏ°ÑÎÕ³ÌÐòµÄË¼Ïë£¬ÐÅºÅÁ¿ÔÚÕâ¶ùÉæ¼°µ½Á½¸öº¯Êý£º´Ë´¦Äã¸ø³öµÄ¶Áº¯Êý£¬»¹ÓÐÒ»¸öÄãÃ»ÓÐ¸ø³öµÄÐ´º¯Êý£¨globalfifo_write£©¡£
//globalfifo_dev ½á¹¹±íÊ¾µ×²ã±»Çý¶¯µÄÓ²¼þ(´Ë´¦¿ÉÄÜÖ»ÊÇ±íÊ¾Èí¼þÄ£ÄâµÄÒ»¸ö»·ÐÎFIFO£©£¬Õâ¸ö½á¹¹ÏÔÈ»/¶¨ÒåÁËÁ½¸ö½ø³ÌË¯Ãß¶ÓÁÐ£ºr_wait£¬w_wait£¬
//¼´Ò»¸ö¶ÁÊý¾ÝµÄ½ø³ÌË¯Ãß¶ÓÁÐºÍÒ»¸öÐ´Êý¾Ý½ø³ÌµÄË¯Ãß¶ÓÁÐ¡£ÓÉÓÚ¶ÁÐ´½ø³Ì²Ù×÷µÄÊÇÍ¬Ò»¿éÇøÓò£¬ËùÒÔÕâ¿éÇøÓò¾Í³ÉÎªÎÒÃÇÍ¨³£ËùËµµÄ¡°ÁÙ½çÇø¡±£¬
//¶ÁÐ´½ø³Ì²»¿ÉÍ¬Ê±·ÃÎÊÕâ¿éÇøÓò£¬·ñÔòºÜÓÐ¿ÉÄÜ»áÔì³ÉÏµÍ³×´Ì¬µÄ²»Ò»ÖÂ£¬ÕâÒ»µãÎÒÏëÓ¦¸ÃÈÝÒ×Àí½â£¬ÄÇÃ´dev->semÐÅºÅÁ¿µÄÄ¿µÄ¾ÍÊÇ´´½¨Õâ¸ö¡°ÁÙ½çÇø¡±£¬
//ÎÞÂÛ¶ÁÐ´½ø³ÌÔÚ½øÈëµ½¹²ÏíÇøÓò½øÐÐ²Ù×÷Ê±£¨¶Á»òÐ´£©£¬±ØÐë»ñÈ¡¶ÀÏí·ÃÎÊµÄÈ¨ÏÞ£¬ 
//Õâ¾ÍÊÇÈçÏÂÓï¾äµÄÄ¿µÄ£ºdown(&dev->sem);´Ëº¯Êý°üº¬ÁË½øÈëË¯ÃßµÄ¶¯×÷Âð£¿
//ÕýÈçÄãËùÎÊµÄ£¬Õâ¸ödownº¯Êý¿ÉÒÔ½«µ±Ç°½ø³ÌÖÃÓÚË¯Ãß×´Ì¬£¬µ±ÓÐÒ»¸öÐ´½ø³ÌÕýÔÚ²Ù×÷Õâ¿é¹²ÏíÇøÓòÊ±£¬´ËÊ±¶Á½ø³Ì£¨ÔÚdownµ÷ÓÃÏÂ£©»á±»¹ÒÆð£¨¼´½øÈëË¯Ãß£©¡£
//¸Ã½ø³ÌµÄ»½ÐÑÓÉÐ´½ø³Ì¸ºÔð£¬ÕýÈçÄã¸ø³öµÄglobalfifo_readº¯ÊýºóµÄÈçÏÂÓï¾ä£º
//wake_up_interruptible(&dev->w_wait); 
//Èç¹ûÄã²é¿´¶ÔÓ¦µÄglobalfifo_writeº¯Êý£¬ÄÇÃ´ÔÚglobalfifo_writeº¯ÊýÖÐ½«»á´æÔÚÈçÏÂµÄÓï¾ä£º
//wake_up_interruptible(&dev->r_wait); 
//¼´µ±Ò»¸öÐ´½ø³ÌÍê³ÉÊý¾ÝµÄÐ´Èëºó£¬Æä»½ÐÑ¿ÉÄÜµÈ´ý¶ÁÈ¡µÄ½ø³Ì£¬´ËÊ±globalfifo_readº¯Êý½«¼ÌÐø´ÓÈçÏÂÓï¾äÖ´ÐÐ¡£
//add_wait_queue(&dev->r_wait, &wait); //ÎªºÎÒªÔÚ»ñµÃÐÅºÅÁ¿ºó½øÈë¶ÁµÈ´ý¶ÓÁÐÍ·£¿
//ÕýÈçÄãËùÎÊµÄ£¬ÎªºÎ´ËÊ±Òª½«µ±Ç°½ø³ÌÌáÇ°¹ÒÈëµ½r_wait¶ÓÁÐ£¬ÒòÎªºóÃæÎÒÃÇÐèÒªÃ÷È·±àÂë
//½«½ø³ÌÖÃÓÚË¯Ãß£¨µ±ÎÞÊý¾Ý¿É¶ÁÈ¡Ê±£©£¬ÕâÓëµ÷ÓÃdownº¯ÊýÊ±ÓÉÄÚºË½«µ±Ç°½ø³ÌÖÃÓÚË¯Ãß×´Ì¬»ù±¾Ò»
///ÖÂµÄ£¬²»Í¬µÄÊÇ£¬µ÷ÓÃdownÊ±ÊÇÓÉÄÚºËÔÚ×ÊÔ´²»¿ÉÓÃÊ±½«½ø³ÌÖÃÓÚË¯Ãß£¬¶ø´Ë´¦ÎÒÃÇ
//¸ù¾ÝÓÐÎÞÊý¾ÝÖ÷¶¯±àÂë½«½ø³ÌÖÃÓÚË¯Ãß×´Ì¬£¬ÒòÎªµ±ÎÞÊý¾Ý¶ÁÈ¡Ê±£¬¶øÓÃ»§ÓÖÃ»ÓÐÉèÖÃNON_BLOCK±êÖ¾Î»£¬ÎÒÃÇ²»ÄÜ¼ÌÐøÕ¼ÓÃCPU£¬ÐèÒªÈÃ³öCPU£¬
//´Ó¶øÈÃÐ´½ø³ÌÓÐ¿ÉÄÜÏò¹²ÏíÇøÓòÖÐÐ´Êý¾Ý£¬ËùÒÔÒ»·½ÃæÄã»á¿´³öÔÚÖ÷¶¯ÈÃ½ø³ÌÖÃÓÚË¯ÃßÊ±£¬»¹±ØÐëÒªµ÷ÓÃupº¯ÊýÊÍ·ÅÐÅºÅÁ¿£¬´Ó¶øÊ¹µÃÐ´½ø³Ì¿ÉÒÔ½øÈëµ½¡°ÁÙ½çÇø¡±Ð´Êý¾Ý£»
//ÁíÒ»·½ÃæÖ´ÐÐÈçÏÂ´úÂë½«½ø³ÌÃ÷È·ÖÃÓÚË¯Ãß£º
    __set_current_state(TASK_INTERRUPTIBLE); //¸Ä±ä½ø³Ì×´Ì¬Îª¿ÉÖÐ¶ÏË¯Ãß
    up(&dev->sem);

      schedule(); //µ÷¶ÈÆäËû½ø³ÌÖ´ÐÐ
// ¾ßÌåµ½linuxÄÚºË´úÂë£¬ÎÒÃÇÀ´¿´¿´ÓÃÓÚ»½ÐÑµÄtry_to_wake_upº¯ÊýºÍÓÃÓÚË¯ÃßµÄscheduleº¯Êý£¨Êµ¼ÊÉÏ¸Ãº¯ÊýÓÃÓÚ´¥·¢Ò»´Îµ÷¶È£¬
//ÔÚµ÷¶ÈÇ°Èç¹û·¢ÏÖµ±Ç°½ø³Ì×´Ì¬²»ÊÇRUNNING£¬Ôò½«ÆäÒÆ³ö¿ÉÖ´ÐÐ¶ÓÁÐ£¬ÓÚÊÇµ±Ç°½ø³Ì¾ÍË¯ÃßÁË£©¡£ 
//[try_to_wake_up] 
///1.Ëø×¡±»»½ÐÑ½ø³Ì¶ÔÓ¦µÄ¿ÉÖ´ÐÐ¶ÓÁÐ 
///2.½«±»»½ÐÑ½ø³Ì¼ÓÈë¸Ã¶ÓÁÐ 
///3.½«±»»½ÐÑ½ø³Ì×´Ì¬ÉèÎªRUNNING 
///4.ÊÍ·ÅËø 
//[schedule] Ö´ÐÐscheduleº¯Êýºó²Å½øÈËË¯Ãß£¬ÆäËüÖ»ÊÇ¸Ä±ä½ø³Ì×´Ì¬
///1.Ëø×¡µ±Ç°½ø³Ì¶ÔÓ¦µÄ¿ÉÖ´ÐÐ¶ÓÁÐ 
///2.Èç¹û½ø³Ì×´Ì¬²»ÎªRUNNING£¬Ôò½«ÆäÒÆ³ö¶ÓÁÐ 
///3.½øÐÐ½ø³ÌÇÐ»» 
///4.ÊÍ·ÅËø 
///µ÷ÓÃscheduleº¯ÊýÖ®Ç°£¬µ±Ç°½ø³ÌÒÑ¾­±»ÉèÖÃÎª·ÇRUNNING×´Ì¬£¬ºÜÈÝÒ×Í¨¹ýËø»úÖÆ±£Ö¤Õâ¸ö¶¯×÷·¢ÉúÔÚtry_to_wake_upº¯Êý±»µ÷ÓÃÖ®Ç°¡£
//ÄÇÃ´£¬¿ÉÒÔ¿´µ½£¬¼´Ê¹ÊÇ"ÏÈ»½ÐÑ¡¢ºóË¯Ãß"£¬Ë¯ÃßµÄ½ø³ÌÒ²ÄÜ±»»½ÐÑ¡£ÒòÎª"»½ÐÑ"¶¯×÷½«½ø³Ì×´Ì¬ÉèÎªRUNNINGÁË£¬
//¶ø"Ë¯Ãß"¶¯×÷·¢ÏÖ½ø³Ì×´Ì¬ÊÇRUNNING£¬Ôò²¢²»»áÕæÕýË¯Ãß£¨²»»á½«½ø³ÌÒÆ³ö¿ÉÖ´ÐÐ¶ÓÁÐ£©¡£¿ÉÖ´ÐÐ¶ÓÁÐËø±£Ö¤ÁË"»½ÐÑ"ºÍ"Ë¯Ãß"Á½¸ö¶¯×÷ÊÇÔ­×Ó
//µÄ£¬²»»á½»²æÖ´ÐÐ¡£¶øÔÚ"Ë¯Ãß"¹ý³ÌÖÐ£¬ÊÇÔÚÍê³ÉÁË½ø³ÌÇÐ»»ºó²ÅÊÍ·ÅËø¡£Õâ¸ö¶¯×÷¿É²ÎÔÄsched.c:context_switch()º¯Êý×îºó²¿·Öµ÷ÓÃµÄfinish_task_switch()º¯Êý¡£

//scheduleº¯Êýµ÷¶ÈÆäËû½ø³ÌÖ´ÐÐ£¬×¢Òâµ±Ç°½ø³Ì±»ÉèÖÃÎªTASK_INTERRUPTIBLE×´Ì¬£¬¼´¿ÉÖÐ¶ÏË¯Ãß£¬//Õâ¸ö×´Ì¬µÄ½ø³Ì±»ÅÅ³ýÔÚ½ø³Ìµ÷¶È×Ê¸ñÖ®Íâ£¬
//Ö±µ½±»»½ÐÑ£¨¼´½øÈëTASK_RUNNING×´Ì¬£©£¬Ç°ÃæÒÑÌá³ö£¬Õâ¸ö»½ÐÑ½«Ö´ÐÐÓÉglobalfifo_writeº¯Êý£¨»ò//ÕßÄ³¸öÖÐ¶Ïº¯Êý£©µÄ½ø³Ì»½ÐÑ¡£
//³ýÁË±»globalfifo_writeº¯Êý»½ÐÑÍâ£¬»¹ÓÐÁíÍâÒ»ÖÖ±»»½ÐÑµÄ¿ÉÄÜ£¬¼´½ø³Ì½ÓÊÕµ½Ò»¸öÍâ²¿ÖÐ¶Ï£¬
//ÈçÏÂ´úÂë¼´¼ì²éÕâÖÖÇé¿ö£¬ÈçÓÃ»§µÈ²»¼°ÁË£¬Ê¹ÓÃCtrl+C½øÐÐÖÐ¶Ï¶Á½ø³Ì²Ù×÷£¬ÄÇÃ´¶ÔCtrl+CµÄ²¶×½¾ÍÔÚ//´Ë´¦Íê³É£º

if (signal_pending(current))   //±»ÆäËûÖÐ¶Ï»½ÐÑ£¬ÈçCtrl+C£¬ÔòÖ±½ÓÌø³ö
    {
      ret =  - ERESTARTSYS;
      goto out2;
    }


//×¢Òâº¯Êý×îºóÈçÏÂÓï¾ä£º
remove_wait_queue(&dev->w_wait, &wait); //Ô­ÎÄÓÐÎó
remove_wait_queue(&dev->r_wait, &wait);  //Õâ²ÅÊÇÕýÈ·µÄÐ´·¨

//ÔÚº¯ÊýÍË³öÖ®Ç°£¬½«µ±Ç°½ø³Ì´Ór_wait¶ÓÁÐÖÐÉ¾³ý£¬ÕâÕýÈçÇ°ÃæµÄÈçÏÂÓï¾äÐÎ³É¶Ô³Æ£º
add_wait_queue(&dev->r_wait, &wait); 

//ÆäËûÓ¦ÎÞÄÑÀí½âÖ®´¦£¬ÒÔÉÏ´úÂëÓÐÁ½´¦½ø³ÌË¯ÃßÖ®´¦£º
1>Îª½øÈë¡°ÁÙ½çÇø¡±»ñÈ¡ÐÅºÅÁ¿Ê±¿ÉÄÜ½øÈëË¯Ãß£¨¼´µ÷ÓÃdownº¯ÊýÊ±£©£¬´Ë´¦µÄË¯Ãß¶¯×÷ÓÉÄÚºË¸ºÔð£¨¼´//downº¯ÊýµÄµ×²ãÊµÏÖ£©¡£
2>ÔÚÎÞ¿É¶ÁÊý¾ÝÊ±£¬×Ô¼º±àÂëÊµÏÖ¶Á½ø³ÌË¯Ãß¡£ÈçÏÂµÄÕâ¶Î´úÂëÔÚºÜ¶àÇý¶¯³ÌÐòÖÐ¶¼ÊÇ±È½ÏµäÐÍµÄ£º

  DECLARE_WAITQUEUE(wait, current); 
  down(&dev->sem); 
  add_wait_queue(&dev->r_wait, &wait);


  while (condition not meet)
  {
   
      __set_current_state(TASK_INTERRUPTIBLE); //¸Ä±ä½ø³Ì×´Ì¬ÎªË¯Ãß
    up(&dev->sem);

      schedule(); //µ÷¶ÈÆäËû½ø³ÌÖ´ÐÐ
    if (signal_pending(current))  {
      ret =  - ERESTARTSYS;
      goto out2;
     }

     down(&dev->sem);
  }
Q:

//1.´ÓÄÄ´¦ÐÑÀ´£¿
//downº¯ÊýÖÐµÄË¯Ãß£¬ÔÚÐÑÀ´ºó£¬½ø³ÌÊÇ·ñ»¹ÊÇ´Ódownº¯Êý¿ªÊ¼¼ÌÐøÍùÏÂ£¿
  __set_current_state(TASK_INTERRUPTIBLE)Ë¯ÃßÔÚÐÑÀ´ºó£¬½ø³Ì´ÓÄÄÀï¿ªÊ¼£¿

//2.while (dev->current_len == 0)
  {
    if (filp->f_flags &O_NONBLOCK)     
    {
      ret =  - EAGAIN;                      
      goto out;
    } 
    __set_current_state(TASK_INTERRUPTIBLE); 
    up(&dev->sem);

    schedule(); 
    if (signal_pending(current))              
    {
      ret =  - ERESTARTSYS;
      goto out2;
    }

    down(&dev->sem);    ÎªºÎÕâÀï»áÓÐdownº¯Êý£¿ËüµÄ×÷ÓÃ¡£¡£¡£¡£
  }

//3.else
  {
    memcpy(dev->mem, dev->mem + count, dev->current_len - count); //fifoÊý¾ÝÇ°ÒÆ
    dev->current_len -= count; //ÓÐÐ§Êý¾Ý³¤¶È¼õÉÙ
    printk(KERN_INFO "read %d bytes(s),current_len:%d\n", count, dev->current_len);
     
    wake_up_interruptible(&dev->w_wait); //»½ÐÑÐ´µÈ´ý¶ÓÁÐ
    
    ret = count;
  }
//ÕâÀïÎªºÎÃ»ÓÐupº¯Êý£¿Ç°ÃæÓÐdownº¯ÊýµÄ°¡¡£

//A:

//.½ø³Ì±»»½ÐÑ¶øµ÷¶È½øÈëÔËÐÐÊ±£¬´ÓdownÓï¾äµÄÏÂÒ»ÌõÓï¾äÖ´ÐÐ£º¼´´úÂëÖÐÈçÏÂÓï¾ä¿ªÊ¼Ö´ÐÐ£
//add_wait_queue(&dev->r_wait, &wait);
//ÁíÍâ×¢ÒâÄã¶ÔÈçÏÂ´úÂëÀí½âÓÐÎó£º
//    __set_current_state(TASK_INTERRUPTIBLE); //¸Ä±ä½ø³Ì×´Ì¬ÎªË¯Ãß

//ÕâÌõÓï¾äÖ»ÊÇ¸Ä±äÁË½ø³ÌµÄ×´Ì¬£¬²¢Ã»ÓÐ½«½ø³ÌÖÃÓÚË¯Ãß£¬´ËÊ±½ø³ÌÈÔÈ»Õ¼ÓÃCPUÔËÐÐ£¬Ö±µ½ÈçÏÂµ÷ÓÃ//sheduleº¯Êý£¬½ø³Ì²Å±»Ã÷È·ÖÃÈëË¯ÃßµÈ´ý×´Ì¬£¬
//ÒòÎªË¯ÃßµÄÄ¿µÄÔÚÓÚµÈ´ýÐ´½ø³ÌÐ´ÈëÊý¾Ý£¬ËùÒÔÔÚµ÷¶Èscheduleº¯ÊýÖ®Ç°ÐèÒªÊÍ·ÅÐÅºÅÁ¿£¬·ÅÆú¶Ô¡°ÁÙ½ç//Çø¡±µÄ¡°°ÔÕ¼¡±£¬Õâ¾ÍÊÇupº¯ÊýµÄ×÷ÓÃ¡£
    up(&dev->sem);
      schedule(); //µ÷¶ÈÆäËû½ø³ÌÖ´ÐÐ

//ÔÚµ÷ÓÃscheduleº¯ÊýÍË³öCPUºó£¬ÏÂ´Î»½ÐÑºó½øÈëÔËÐÐÊ±½«´ÓscheduleÓï¾äµÄÏÂÒ»ÌõÓï¾ä¿ªÊ¼£¬¼´if //(signal_pending(current)) Óï¾ä¡£

//×¢Òâµ½dev->current_len Ò²ÊÇÒ»¸ö¹²Ïí±äÁ¿£¬¶ÁÐ´½ø³Ì¿ÉÄÜ»áÍ¬Ê±·ÃÎÊ¸Ã±äÁ¿£¬ËùÒÔÔÚ¼ì²é¸Ã±äÁ¿Öµ//Ö®Ç°Ò²Òª½øÈë¡°ÁÙ½çÇø¡±¡£
//ºÜ¶à´úÂëÖÐ½«downÓï¾ä·ÅÔÚ´Ë´¦whileÑ­»·µÄÍâÃæ£¬ÔÚ99%µÄÊ±ºò³ÌÐò¶¼²»»á³öÏÖÒì³££¬µ«ÊÇÈ´ÊÇ²»¹æÔò//²»ÕýÈ·µÄ±àÂë·½Ê½¡£
//Ç°Ò»¸öÌû×ÓÖÐ£¬ÎÒËµµ½ÈçÏÂ´úÂëµÄÓÃÍ¾£¬Èç¹ûÈçÏÂ´úÂë²»³ÉÁ¢£¬ÄÇÃ´Õâ¸ö¶Á½ø³ÌµÄ»½ÐÑÓ¦ÊÇ
//¶ÔÓ¦Ð´½ø³ÌµÄ¹¦ÀÍ£¬´ËÊ±±íÊ¾¼«ÓÐ¿ÉÄÜÓÖÓÐ¿É¶ÁÊý¾ÝÁË£¬ÄÇÃ´ÎªÁË¶ÁÈ¡Êý¾Ý£¬±ØÐë½øÈë¡°ÁÙ½çÇø¡±£¬³ÌÐòÎª/ÁË±£ÏÕÆð¼û£¬ÔÙ´Î¶Ôdev->current_len½øÐÐ¼ì²é£¬ÒÔ±ÜÃâ¶à¸ö¶Á½ø³ÌÍ¬Ê±µÈ´ý£¬¶øÍ¬Ê±±»»½ÐÑµÄ¼«¶ËÇé¿ö¡£dev->current_lenÓÖÊÇÒ»¸ö¹²Ïí±äÁ¿£¬
//ËùÒÔ²ÅÓÐ´Ë´¦downÓï¾äµ÷ÓÃ£¬¿ÉÒÔËµ£¬´Ë´¦µÄµ÷ÓÃÊÇ·Ç³£¹Ø¼üµÄ£¬Ò²ÊÇ¼«ÆäÕýÈ·µÄ±àÂë·½Ê½¡£
if (signal_pending(current))              
    {
      ret =  - ERESTARTSYS;
      goto out2;
    }

//3.ºÇºÇ£¬¼ÌÐøÍùÏÂÕÒ£¬¿´¿´out±êÊ¶·ûºóÃæÊÇÉ¶¡£

