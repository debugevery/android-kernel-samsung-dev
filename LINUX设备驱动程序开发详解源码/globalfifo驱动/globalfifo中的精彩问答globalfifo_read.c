//����Linux�豸������globalfifo�������ӵľ����ʴ�

/*globalfifo������*/
static ssize_t globalfifo_read(struct file *filp, char __user *buf, size_t count,
  loff_t *ppos)
{
  int ret;
  struct globalfifo_dev *dev = filp->private_data; //����豸�ṹ��ָ��

  DECLARE_WAITQUEUE(wait, current); //����ȴ�����


  down(&dev->sem); //�˺��������˽���˯�ߵĶ�����

  add_wait_queue(&dev->r_wait, &wait); //Ϊ��Ҫ�ڻ���ź����������ȴ�����ͷ��


  /* �ȴ�FIFO�ǿ� */
  while (dev->current_len == 0)
  {
    if (filp->f_flags &O_NONBLOCK) //?

    {
      ret = - EAGAIN; //?

      goto out;
    } 
    __set_current_state(TASK_INTERRUPTIBLE); //�ı����״̬Ϊ˯��

    up(&dev->sem);

    schedule(); //������������ִ��

    if (signal_pending(current)) //?

    //�������Ϊ�źŻ���

    {
      ret = - ERESTARTSYS;
      goto out2;
    }

    down(&dev->sem);
  }

  /* �������û��ռ� */
  if (count > dev->current_len)
    count = dev->current_len;

  if (copy_to_user(buf, dev->mem, count))
  {
    ret = - EFAULT;
    goto out;
  }
  else
  {
    memcpy(dev->mem, dev->mem + count, dev->current_len - count); //fifo����ǰ��

    dev->current_len -= count; //��Ч���ݳ��ȼ���

    printk(KERN_INFO "read %d bytes(s),current_len:%d\n", count, dev->current_len);
     
    wake_up_interruptible(&dev->w_wait); //����д�ȴ�����

    
    ret = count;
  }
  out: up(&dev->sem); //�ͷ��ź���

  out2:remove_wait_queue(&dev->w_wait, &wait); //�Ӹ����ĵȴ�����ͷ�Ƴ�

  set_current_state(TASK_RUNNING);
  return ret;
} 

 


Q:
//���˶������������ǲ��ܽ�����ʵ�����Ӽ�����⡣
//��ֻ����⣺�ӽ���˯��wait_event()��˯�߻���wake_up()
//������û��wait_event()��غ�����Ϊʲô��
//���⣬�����˯�ߡ��ȴ����У����ź�������ʲô��ϵ�������鶼�����ˣ���

//A:

//����Ӧ�������ϰ��ճ����˼�룬�ź���������漰�������������˴�������Ķ�����������һ����û�и�����д������globalfifo_write����
//globalfifo_dev �ṹ��ʾ�ײ㱻������Ӳ��(�˴�����ֻ�Ǳ�ʾ���ģ���һ������FIFO��������ṹ��Ȼ/��������������˯�߶��У�r_wait��w_wait��
//��һ�������ݵĽ���˯�߶��к�һ��д���ݽ��̵�˯�߶��С����ڶ�д���̲�������ͬһ�����������������ͳ�Ϊ����ͨ����˵�ġ��ٽ�������
//��д���̲���ͬʱ����������򣬷�����п��ܻ����ϵͳ״̬�Ĳ�һ�£���һ������Ӧ��������⣬��ôdev->sem�ź�����Ŀ�ľ��Ǵ���������ٽ�������
//���۶�д�����ڽ��뵽����������в���ʱ������д���������ȡ������ʵ�Ȩ�ޣ� 
//�������������Ŀ�ģ�down(&dev->sem);�˺��������˽���˯�ߵĶ�����
//���������ʵģ����down�������Խ���ǰ��������˯��״̬������һ��д�������ڲ�����鹲������ʱ����ʱ�����̣���down�����£��ᱻ���𣨼�����˯�ߣ���
//�ý��̵Ļ�����д���̸��������������globalfifo_read�������������䣺
//wake_up_interruptible(&dev->w_wait); 
//�����鿴��Ӧ��globalfifo_write��������ô��globalfifo_write�����н���������µ���䣺
//wake_up_interruptible(&dev->r_wait); 
//����һ��д����������ݵ�д����份�ѿ��ܵȴ���ȡ�Ľ��̣���ʱglobalfifo_read�������������������ִ�С�
//add_wait_queue(&dev->r_wait, &wait); //Ϊ��Ҫ�ڻ���ź����������ȴ�����ͷ��
//���������ʵģ�Ϊ�δ�ʱҪ����ǰ������ǰ���뵽r_wait���У���Ϊ����������Ҫ��ȷ����
//����������˯�ߣ��������ݿɶ�ȡʱ�����������down����ʱ���ں˽���ǰ��������˯��״̬����һ
///�µģ���ͬ���ǣ�����downʱ�����ں�����Դ������ʱ����������˯�ߣ����˴�����
//�������������������뽫��������˯��״̬����Ϊ�������ݶ�ȡʱ�����û���û������NON_BLOCK��־λ�����ǲ��ܼ���ռ��CPU����Ҫ�ó�CPU��
//�Ӷ���д�����п�������������д���ݣ�����һ������ῴ���������ý�������˯��ʱ��������Ҫ����up�����ͷ��ź������Ӷ�ʹ��д���̿��Խ��뵽���ٽ�����д���ݣ�
//��һ����ִ�����´��뽫������ȷ����˯�ߣ�
    __set_current_state(TASK_INTERRUPTIBLE); //�ı����״̬Ϊ���ж�˯��
    up(&dev->sem);

      schedule(); //������������ִ��
// ���嵽linux�ں˴��룬�������������ڻ��ѵ�try_to_wake_up����������˯�ߵ�schedule������ʵ���ϸú������ڴ���һ�ε��ȣ�
//�ڵ���ǰ������ֵ�ǰ����״̬����RUNNING�������Ƴ���ִ�ж��У����ǵ�ǰ���̾�˯���ˣ��� 
//[try_to_wake_up] 
///1.��ס�����ѽ��̶�Ӧ�Ŀ�ִ�ж��� 
///2.�������ѽ��̼���ö��� 
///3.�������ѽ���״̬��ΪRUNNING 
///4.�ͷ��� 
//[schedule] ִ��schedule������Ž���˯�ߣ�����ֻ�Ǹı����״̬
///1.��ס��ǰ���̶�Ӧ�Ŀ�ִ�ж��� 
///2.�������״̬��ΪRUNNING�������Ƴ����� 
///3.���н����л� 
///4.�ͷ��� 
///����schedule����֮ǰ����ǰ�����Ѿ�������Ϊ��RUNNING״̬��������ͨ�������Ʊ�֤�������������try_to_wake_up����������֮ǰ��
//��ô�����Կ�������ʹ��"�Ȼ��ѡ���˯��"��˯�ߵĽ���Ҳ�ܱ����ѡ���Ϊ"����"����������״̬��ΪRUNNING�ˣ�
//��"˯��"�������ֽ���״̬��RUNNING���򲢲�������˯�ߣ����Ὣ�����Ƴ���ִ�ж��У�����ִ�ж�������֤��"����"��"˯��"����������ԭ��
//�ģ����ύ��ִ�С�����"˯��"�����У���������˽����л�����ͷ�������������ɲ���sched.c:context_switch()������󲿷ֵ��õ�finish_task_switch()������

//schedule����������������ִ�У�ע�⵱ǰ���̱�����ΪTASK_INTERRUPTIBLE״̬�������ж�˯�ߣ�//���״̬�Ľ��̱��ų��ڽ��̵����ʸ�֮�⣬
//ֱ�������ѣ�������TASK_RUNNING״̬����ǰ���������������ѽ�ִ����globalfifo_write��������//��ĳ���жϺ������Ľ��̻��ѡ�
//���˱�globalfifo_write���������⣬��������һ�ֱ����ѵĿ��ܣ������̽��յ�һ���ⲿ�жϣ�
//���´��뼴���������������û��Ȳ����ˣ�ʹ��Ctrl+C�����ж϶����̲�������ô��Ctrl+C�Ĳ�׽����//�˴���ɣ�

if (signal_pending(current))   //�������жϻ��ѣ���Ctrl+C����ֱ������
    {
      ret =  - ERESTARTSYS;
      goto out2;
    }


//ע�⺯�����������䣺
remove_wait_queue(&dev->w_wait, &wait); //ԭ������
remove_wait_queue(&dev->r_wait, &wait);  //�������ȷ��д��

//�ں����˳�֮ǰ������ǰ���̴�r_wait������ɾ����������ǰ�����������γɶԳƣ�
add_wait_queue(&dev->r_wait, &wait); 

//����Ӧ�������֮�������ϴ�������������˯��֮����
1>Ϊ���롰�ٽ�������ȡ�ź���ʱ���ܽ���˯�ߣ�������down����ʱ�����˴���˯�߶������ں˸��𣨼�//down�����ĵײ�ʵ�֣���
2>���޿ɶ�����ʱ���Լ�����ʵ�ֶ�����˯�ߡ����µ���δ����ںܶ����������ж��ǱȽϵ��͵ģ�

  DECLARE_WAITQUEUE(wait, current); 
  down(&dev->sem); 
  add_wait_queue(&dev->r_wait, &wait);


  while (condition not meet)
  {
   
      __set_current_state(TASK_INTERRUPTIBLE); //�ı����״̬Ϊ˯��
    up(&dev->sem);

      schedule(); //������������ִ��
    if (signal_pending(current))  {
      ret =  - ERESTARTSYS;
      goto out2;
     }

     down(&dev->sem);
  }
Q:

//1.���Ĵ�������
//down�����е�˯�ߣ��������󣬽����Ƿ��Ǵ�down������ʼ�������£�
  __set_current_state(TASK_INTERRUPTIBLE)˯���������󣬽��̴����￪ʼ��

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

    down(&dev->sem);    Ϊ���������down�������������á�������
  }

//3.else
  {
    memcpy(dev->mem, dev->mem + count, dev->current_len - count); //fifo����ǰ��
    dev->current_len -= count; //��Ч���ݳ��ȼ���
    printk(KERN_INFO "read %d bytes(s),current_len:%d\n", count, dev->current_len);
     
    wake_up_interruptible(&dev->w_wait); //����д�ȴ�����
    
    ret = count;
  }
//����Ϊ��û��up������ǰ����down�����İ���

//A:

//.���̱����Ѷ����Ƚ�������ʱ����down������һ�����ִ�У���������������俪ʼִ�У
//add_wait_queue(&dev->r_wait, &wait);
//����ע��������´����������
//    __set_current_state(TASK_INTERRUPTIBLE); //�ı����״̬Ϊ˯��

//�������ֻ�Ǹı��˽��̵�״̬����û�н���������˯�ߣ���ʱ������Ȼռ��CPU���У�ֱ�����µ���//shedule���������̲ű���ȷ����˯�ߵȴ�״̬��
//��Ϊ˯�ߵ�Ŀ�����ڵȴ�д����д�����ݣ������ڵ���schedule����֮ǰ��Ҫ�ͷ��ź����������ԡ��ٽ�//�����ġ���ռ���������up���������á�
    up(&dev->sem);
      schedule(); //������������ִ��

//�ڵ���schedule�����˳�CPU���´λ��Ѻ��������ʱ����schedule������һ����俪ʼ����if //(signal_pending(current)) ��䡣

//ע�⵽dev->current_len Ҳ��һ�������������д���̿��ܻ�ͬʱ���ʸñ����������ڼ��ñ���ֵ//֮ǰҲҪ���롰�ٽ�������
//�ܶ�����н�down�����ڴ˴�whileѭ�������棬��99%��ʱ����򶼲�������쳣������ȴ�ǲ�����//����ȷ�ı��뷽ʽ��
//ǰһ�������У���˵�����´������;��������´��벻��������ô��������̵Ļ���Ӧ��
//��Ӧд���̵Ĺ��ͣ���ʱ��ʾ���п������пɶ������ˣ���ôΪ�˶�ȡ���ݣ�������롰�ٽ�����������Ϊ/�˱���������ٴζ�dev->current_len���м�飬�Ա�����������ͬʱ�ȴ�����ͬʱ�����ѵļ��������dev->current_len����һ�����������
//���Բ��д˴�down�����ã�����˵���˴��ĵ����Ƿǳ��ؼ��ģ�Ҳ�Ǽ�����ȷ�ı��뷽ʽ��
if (signal_pending(current))              
    {
      ret =  - ERESTARTSYS;
      goto out2;
    }

//3.�Ǻǣ����������ң�����out��ʶ��������ɶ��

