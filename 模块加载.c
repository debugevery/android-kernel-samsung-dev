模块加载后在/proc/modules添加一行记录 (2008-11-05 14:10) 

模块加载后在/proc/modules添加一行记录
 
只有在模块里注册设备后，才会在/proc/devices添加一行记录（含设备编号dev_t）
 
 
/proc/modules  :模块加载列表,insmod（加载模块）后在此添加一行
/sys/module    :添加一目录,insmod（加载模块）后在此添加一子目录
/proc/devices  :注册设备列表，注册设备（register_chrdev_region,allow_chrdev_region）后在此
                添加一行
/dev/*         :设备节点，mknod（创建设备节点）后在此添加一子目录
