//(源码中没有设备驱动，如I2C总线上挂载的EEPROM设备的驱动)
/*
I2C 设备驱动要使用 i2c_driver 和 i2c_client 数据结构并填充其中的成员函数。
i2c_client一般被包含在设备的私有信息结构体 yyy_data 中，而 i2c_driver 则适合被定
义为全局变量并初始化，代码清单15.13 所示为已被初始化的 i2c_driver。 
代码清单15.13  已被初始化的i2c_driver  
1  static struct i2c_driver yyy_driver = 
2  { 
3    .driver = 
4    { 
5      .name = "yyy", 
6    } , 
7    .attach_adapter = yyy_attach_adapter, 
8    .detach_client =  yyy_detach_client, 
9    .command = yyy_command, 
10 }; 


15.4.1   Linux I2C设备驱动的模块加载与卸载 
I2C 设备驱动的模块加载函数通用的方法是在 I2C 设备驱动的模块加载函数中完
成两件事。 
（1）通过register_chrdev()函数将I2C设备注册为一个字符设备。 
（2）通过I2C核心的i2c_add_driver()函数添加 i2c_driver。 
在模块卸载函数中需要做相反的两件事。 
（1）通过I2C核心的i2c_del_driver()函数删除 i2c_driver。 
（2）通过unregister_chrdev()函数注销字符设备。 

15.4.2   Linux I2C设备驱动的i2c_driver成员函数 
i2c_add_driver （&yyy_driver） 的执行会引发i2c_driver结构体中yyy_attach_adapter()
函数的执行，我们可以在 yyy_attach_adapter()函数里探测物理设备。为了实现探测，
yyy_attach_adapter()函数里面也只需简单地调用I2C核心的 i2c_probe()函数， 如代码清


下面讲解 i2c_driver 中重要函数 yyy_command()的实现，它实现了针对设备的控
制命令。具体的控制命令是设备相关的，如对于实时钟而言，命令将是设置时间和获
取时间，而对于视频AD设备而言，命令会是设置采样方式、选择通道等。 

15.4.3   Linux I2C设备驱动的文件操作接口 
作为一种字符类设备， Linux I2C设备驱动的文件操作接口与普通的设备驱动是完
全一致的，但是在其中要使用i2c_client、i2c_driver、i2c_adapter 和 i2c_algorithm结构
体和I2C核心， 并且对设备的读写和控制需要借助体系结构中各组成部分的协同合作。

下面
详细讲解 I2C 设备读写过程中数据的流向和函数的调用关系。I2C 设备的写操作经历
了如下几个步骤。 
（1）从用户空间到字符设备驱动写函数接口，写函数构造 I2C消息数组。 
（2）写函数把构造的I2C消息数组传递给I2C核心的传输函数 i2c_transfer()。 
（3）I2C 核心的传输函数 i2c_transfer()找到对应适配器 algorithm 的通信方
法函数 master_xfer()去最终完成 I2C 消息的处理。 
如图15.6所示为从用户空间发起读写操作到algorithm进行消息传输的流程。 
通常，如果 I2C设备不是一个输入/输出设备或存储设备，就并不需要给I2C设备提
供读写函数。许多 I2C设备只是需要被设置以某种方式工作，而不是被读写。另外，I2C设备驱动的文件操作接口也不是必需的，
甚至极少被需要。大多数情况下，我们只需要通过i2c-dev.c文件提供的 I2C适配器设
备文件接口就可完成对I2C设备的读写。 
*/