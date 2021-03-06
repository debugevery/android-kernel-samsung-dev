//关于Linux设备驱动中globalfifo驱动例子的精彩问答

/*globalfifo读函数*/
static ssize_t globalfifo_read(struct file *filp, char __user *buf, size_t count,
  loff_t *ppos)
{
  int ret;
  struct globalfifo_dev *dev = filp->private_data; //获得设备结构体指针

  DECLARE_WAITQUEUE(wait, current); //定义等待队列


  down(&dev->sem); //此函数包含了进入睡眠的动作吗？

  add_wait_queue(&dev->r_wait, &wait); //为何要在获得信号量后进入读等待队列头？


  /* 等待FIFO非空 */
  while (dev->current_len == 0)
  {
    if (filp->f_flags &O_NONBLOCK) //?

    {
      ret = - EAGAIN; //?

      goto out;
    } 
    __set_current_state(TASK_INTERRUPTIBLE); //改变进程状态为睡眠

    up(&dev->sem);

    schedule(); //调度其他进程执行

    if (signal_pending(current)) //?

    //如果是因为信号唤醒

    {
      ret = - ERESTARTSYS;
      goto out2;
    }

    down(&dev->sem);
  }

  /* 拷贝到用户空间 */
  if (count > dev->current_len)
    count = dev->current_len;

  if (copy_to_user(buf, dev->mem, count))
  {
    ret = - EFAULT;
    goto out;
  }
  else
  {
    memcpy(dev->mem, dev->mem + count, dev->current_len - count); //fifo数据前移

    dev->current_len -= count; //有效数据长度减少

    printk(KERN_INFO "read %d bytes(s),current_len:%d\n", count, dev->current_len);
     
    wake_up_interruptible(&dev->w_wait); //唤醒写等待队列

    
    ret = count;
  }
  out: up(&dev->sem); //释放信号量

  out2:remove_wait_queue(&dev->w_wait, &wait); //从附属的等待队列头移除

  set_current_state(TASK_RUNNING);
  return ret;
} 

 


Q:
//本人对阻塞操作还是不能结合这个实际例子加以理解。
//我只能理解：从进入睡眠wait_event()到睡眠唤醒wake_up()
//可这里没有wait_event()相关函数，为什么？
//另外，这里的睡眠、等待队列，和信号量又有什么关系？？看书都看晕了！！

//A:

//首先应从总体上把握程序的思想，信号量在这儿涉及到两个函数：此处你给出的读函数，还有一个你没有给出的写函数（globalfifo_write）。
//globalfifo_dev 结构表示底层被驱动的硬件(此处可能只是表示软件模拟的一个环形FIFO），这个结构显然/定义了两个进程睡眠队列：r_wait，w_wait，
//即一个读数据的进程睡眠队列和一个写数据进程的睡眠队列。由于读写进程操作的是同一块区域，所以这块区域就成为我们通常所说的“临界区”，
//读写进程不可同时访问这块区域，否则很有可能会造成系统状态的不一致，这一点我想应该容易理解，那么dev->sem信号量的目的就是创建这个“临界区”，
//无论读写进程在进入到共享区域进行操作时（读或写），必须获取独享访问的权限， 
//这就是如下语句的目的：down(&dev->sem);此函数包含了进入睡眠的动作吗？
//正如你所问的，这个down函数可以将当前进程置于睡眠状态，当有一个写进程正在操作这块共享区域时，此时读进程（在down调用下）会被挂起（即进入睡眠）。
//该进程的唤醒由写进程负责，正如你给出的globalfifo_read函数后的如下语句：
//wake_up_interruptible(&dev->w_wait); 
//如果你查看对应的globalfifo_write函数，那么在globalfifo_write函数中将会存在如下的语句：
//wake_up_interruptible(&dev->r_wait); 
//即当一个写进程完成数据的写入后，其唤醒可能等待读取的进程，此时globalfifo_read函数将继续从如下语句执行。
//add_wait_queue(&dev->r_wait, &wait); //为何要在获得信号量后进入读等待队列头？
//正如你所问的，为何此时要将当前进程提前挂入到r_wait队列，因为后面我们需要明确编码
//将进程置于睡眠（当无数据可读取时），这与调用down函数时由内核将当前进程置于睡眠状态基本一
///致的，不同的是，调用down时是由内核在资源不可用时将进程置于睡眠，而此处我们
//根据有无数据主动编码将进程置于睡眠状态，因为当无数据读取时，而用户又没有设置NON_BLOCK标志位，我们不能继续占用CPU，需要让出CPU，
//从而让写进程有可能向共享区域中写数据，所以一方面你会看出在主动让进程置于睡眠时，还必须要调用up函数释放信号量，从而使得写进程可以进入到“临界区”写数据；
//另一方面执行如下代码将进程明确置于睡眠：
    __set_current_state(TASK_INTERRUPTIBLE); //改变进程状态为可中断睡眠
    up(&dev->sem);

      schedule(); //调度其他进程执行
// 具体到linux内核代码，我们来看看用于唤醒的try_to_wake_up函数和用于睡眠的schedule函数（实际上该函数用于触发一次调度，
//在调度前如果发现当前进程状态不是RUNNING，则将其移出可执行队列，于是当前进程就睡眠了）。 
//[try_to_wake_up] 
///1.锁住被唤醒进程对应的可执行队列 
///2.将被唤醒进程加入该队列 
///3.将被唤醒进程状态设为RUNNING 
///4.释放锁 
//[schedule] 执行schedule函数后才进人睡眠，其它只是改变进程状态
///1.锁住当前进程对应的可执行队列 
///2.如果进程状态不为RUNNING，则将其移出队列 
///3.进行进程切换 
///4.释放锁 
///调用schedule函数之前，当前进程已经被设置为非RUNNING状态，很容易通过锁机制保证这个动作发生在try_to_wake_up函数被调用之前。
//那么，可以看到，即使是"先唤醒、后睡眠"，睡眠的进程也能被唤醒。因为"唤醒"动作将进程状态设为RUNNING了，
//而"睡眠"动作发现进程状态是RUNNING，则并不会真正睡眠（不会将进程移出可执行队列）。可执行队列锁保证了"唤醒"和"睡眠"两个动作是原子
//的，不会交叉执行。而在"睡眠"过程中，是在完成了进程切换后才释放锁。这个动作可参阅sched.c:context_switch()函数最后部分调用的finish_task_switch()函数。

//schedule函数调度其他进程执行，注意当前进程被设置为TASK_INTERRUPTIBLE状态，即可中断睡眠，//这个状态的进程被排除在进程调度资格之外，
//直到被唤醒（即进入TASK_RUNNING状态），前面已提出，这个唤醒将执行由globalfifo_write函数（或//者某个中断函数）的进程唤醒。
//除了被globalfifo_write函数唤醒外，还有另外一种被唤醒的可能，即进程接收到一个外部中断，
//如下代码即检查这种情况，如用户等不及了，使用Ctrl+C进行中断读进程操作，那么对Ctrl+C的捕捉就在//此处完成：

if (signal_pending(current))   //被其他中断唤醒，如Ctrl+C，则直接跳出
    {
      ret =  - ERESTARTSYS;
      goto out2;
    }


//注意函数最后如下语句：
remove_wait_queue(&dev->w_wait, &wait); //原文有误
remove_wait_queue(&dev->r_wait, &wait);  //这才是正确的写法

//在函数退出之前，将当前进程从r_wait队列中删除，这正如前面的如下语句形成对称：
add_wait_queue(&dev->r_wait, &wait); 

//其他应无难理解之处，以上代码有两处进程睡眠之处：
1>为进入“临界区”获取信号量时可能进入睡眠（即调用down函数时），此处的睡眠动作由内核负责（即//down函数的底层实现）。
2>在无可读数据时，自己编码实现读进程睡眠。如下的这段代码在很多驱动程序中都是比较典型的：

  DECLARE_WAITQUEUE(wait, current); 
  down(&dev->sem); 
  add_wait_queue(&dev->r_wait, &wait);


  while (condition not meet)
  {
   
      __set_current_state(TASK_INTERRUPTIBLE); //改变进程状态为睡眠
    up(&dev->sem);

      schedule(); //调度其他进程执行
    if (signal_pending(current))  {
      ret =  - ERESTARTSYS;
      goto out2;
     }

     down(&dev->sem);
  }
Q:

//1.从哪处醒来？
//down函数中的睡眠，在醒来后，进程是否还是从down函数开始继续往下？
  __set_current_state(TASK_INTERRUPTIBLE)睡眠在醒来后，进程从哪里开始？

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

    down(&dev->sem);    为何这里会有down函数？它的作用。。。。
  }

//3.else
  {
    memcpy(dev->mem, dev->mem + count, dev->current_len - count); //fifo数据前移
    dev->current_len -= count; //有效数据长度减少
    printk(KERN_INFO "read %d bytes(s),current_len:%d\n", count, dev->current_len);
     
    wake_up_interruptible(&dev->w_wait); //唤醒写等待队列
    
    ret = count;
  }
//这里为何没有up函数？前面有down函数的啊。

//A:

//.进程被唤醒而调度进入运行时，从down语句的下一条语句执行：即代码中如下语句开始执行�
//add_wait_queue(&dev->r_wait, &wait);
//另外注意你对如下代码理解有误：
//    __set_current_state(TASK_INTERRUPTIBLE); //改变进程状态为睡眠

//这条语句只是改变了进程的状态，并没有将进程置于睡眠，此时进程仍然占用CPU运行，直到如下调用//shedule函数，进程才被明确置入睡眠等待状态，
//因为睡眠的目的在于等待写进程写入数据，所以在调度schedule函数之前需要释放信号量，放弃对“临界//区”的“霸占”，这就是up函数的作用。
    up(&dev->sem);
      schedule(); //调度其他进程执行

//在调用schedule函数退出CPU后，下次唤醒后进入运行时将从schedule语句的下一条语句开始，即if //(signal_pending(current)) 语句。

//注意到dev->current_len 也是一个共享变量，读写进程可能会同时访问该变量，所以在检查该变量值//之前也要进入“临界区”。
//很多代码中将down语句放在此处while循环的外面，在99%的时候程序都不会出现异常，但是却是不规则//不正确的编码方式。
//前一个帖子中，我说到如下代码的用途，如果如下代码不成立，那么这个读进程的唤醒应是
//对应写进程的功劳，此时表示极有可能又有可读数据了，那么为了读取数据，必须进入“临界区”，程序为/了保险起见，再次对dev->current_len进行检查，以避免多个读进程同时等待，而同时被唤醒的极端情况。dev->current_len又是一个共享变量，
//所以才有此处down语句调用，可以说，此处的调用是非常关键的，也是极其正确的编码方式。
if (signal_pending(current))              
    {
      ret =  - ERESTARTSYS;
      goto out2;
    }

//3.呵呵，继续往下找，看看out标识符后面是啥。

