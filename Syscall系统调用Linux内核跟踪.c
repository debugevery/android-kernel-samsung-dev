Syscallϵͳ����Linux�ں˸��� ========================================================                                                                                                                                                                                                                                             
    ��Linux���û��ռ䣬���Ǿ��������ϵͳ���ã��������Ǹ���һ��readϵͳ���ã�ʹ�õ�Linux�ں˰汾ΪLinux2.6.37����ͬ��Linux�汾���е�ʵ�����в�ͬ��                                                                                                                                                                                
��һЩӦ�������ǿ��Կ��������һЩ���壺                                                                                                                                                                                                                                                                                          
#define real_read(fd, buf, count ) (syscall(SYS_read, (fd), (buf), (count)))                                                                                                                                                                                                                                                      
                                                                                                                                                                                                                                                                                                                                  
                                                                                                                                                                                                                                                                                                                                  
   ��ʵ�������õĻ���ϵͳ����syscall(SYS_read)��Ҳ����sys_read()�����У���Linux2.6.37�е����ü����궨��ʵ�֡�                                                                                                                                                                                                                     
                                                                                                                                                                                                                                                                                                                                  
    Linux ϵͳ���ã�SCI��system call interface����ʵ�ֻ���ʵ������һ����·����Լ��ֽ�Ĺ��̣��û�۵���� 0x80 �ж������ڵ㣨X86 ϵͳ�ṹ����Ҳ����˵������ϵͳ���ö����û��ռ��л�۵� 0x80 �жϵ㣬ͬʱ��������ϵͳ���úš��� 0x80 �жϴ����������ʱ��������ϵͳ���úŶԲ�ͬ��ϵͳ���÷ֱ������ò�ͬ���ں˺���������
                                                                                                                                                                                                                                                                                                                                  
����ϵͳ���õ�����;��                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                  
      ��1��int $0��80 , ��ʽlinux�ں˰汾������ϵͳ���õ�Ψһ��ʽ                                                                                                                                                                                                                                                                 
                                                                                                                                                                                                                                                                                                                                  
      ��2��sysenter���ָ��                                                                                                                                                                                                                                                                                                       
                                                                                                                                                                                                                                                                                                                                  
��Linux�ں���ʹ������ĺ����ϵͳ���� SYSCALL_DEFINE3(read, unsigned int, fd, char __user *, buf, size_t, count)                                                                                                                                                                                                                  
{                                                                                                                                                                                                                                                                                                                                 
    struct file *file;                                                                                                                                                                                                                                                                                                            
    ssize_t ret = -EBADF;                                                                                                                                                                                                                                                                                                         
    int fput_needed;                                                                                                                                                                                                                                                                                                              
                                                                                                                                                                                                                                                                                                                                  
    file = fget_light(fd, &fput_needed);                                                                                                                                                                                                                                                                                          
    if (file) {                                                                                                                                                                                                                                                                                                                   
        loff_t pos = file_pos_read(file);                                                                                                                                                                                                                                                                                         
        ret = vfs_read(file, buf, count, &pos);                                                                                                                                                                                                                                                                                   
        file_pos_write(file, pos);                                                                                                                                                                                                                                                                                                
        fput_light(file, fput_needed);                                                                                                                                                                                                                                                                                            
    }                                                                                                                                                                                                                                                                                                                             
                                                                                                                                                                                                                                                                                                                                  
    return ret;                                                                                                                                                                                                                                                                                                                   
}                                                                                                                                                                                                                                                                                                                                 
                                                                                                                                                                                                                                                                                                                                  
                                                                                                                                                                                                                                                                                                                                  
                                                                                                                                                                                                                                                                                                                                  
����SYSCALL_DEFINE3�ĺ궨�����£�                                                                                                                                                                                                                                                                                                 
                                                                                                                                                                                                                                                                                                                                  
#define SYSCALL_DEFINE3(name, ...) SYSCALL_DEFINEx(3, _##name, __VA_ARGS__)                                                                                                                                                                                                                                                       
                                                                                                                                                                                                                                                                                                                                  
                                                                                                                                                                                                                                                                                                                                  
##����˼���Ǻ��е��ַ�ֱ���滻��                                                                                                                                                                                                                                                                                                  
���name = read����ô�ں���__NR_##name���滻����__NR_read�ˡ� __NR_##name��ϵͳ���úţ�##ָ�������κ�չ��������ʵ�ʵ�ϵͳ�������ִ���"name",Ȼ���ٰ�__NR_...չ������name == ioctl����Ϊ__NR_ioctl��                                                                                                                               
                                                                                                                                                                                                                                                                                                                                  
                                                                                                                                                                                                                                                                                                                                  
                                                                                                                                                                                                                                                                                                                                  
                                                                                                                                                                                                                                                                                                                                  
                                                                                                                                                                                                                                                                                                                                  
#ifdef CONFIG_FTRACE_SYSCALLS                                                                                                                                                                                                                                                                                                     
#define SYSCALL_DEFINEx(x, sname, ...)                \                                                                                                                                                                                                                                                                           
    static const char *types_##sname[] = {            \                                                                                                                                                                                                                                                                           
        __SC_STR_TDECL##x(__VA_ARGS__)            \                                                                                                                                                                                                                                                                               
    };                            \                                                                                                                                                                                                                                                                                               
    static const char *args_##sname[] = {            \                                                                                                                                                                                                                                                                            
        __SC_STR_ADECL##x(__VA_ARGS__)            \                                                                                                                                                                                                                                                                               
    };                            \                                                                                                                                                                                                                                                                                               
    SYSCALL_METADATA(sname, x);                \                                                                                                                                                                                                                                                                                  
    __SYSCALL_DEFINEx(x, sname, __VA_ARGS__)                                                                                                                                                                                                                                                                                      
#else                                                                                                                                                                                                                                                                                                                             
#define SYSCALL_DEFINEx(x, sname, ...)                \                                                                                                                                                                                                                                                                           
    __SYSCALL_DEFINEx(x, sname, __VA_ARGS__)                                                                                                                                                                                                                                                                                      
#endif                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                  
                                                                                                                                                                                                                                                                                                                                  
�����Ƿ���CONFIG_FTRACE_SYSCALLS�꣬���ն���ִ�� ���������궨�壺                                                                                                                                                                                                                                                             
                                                                                                                                                                                                                                                                                                                                  
__SYSCALL_DEFINEx(x, sname, __VA_ARGS__)                                                                                                                                                                                                                                                                                          
                                                                                                                                                                                                                                                                                                                                  
#ifdef CONFIG_HAVE_SYSCALL_WRAPPERS                                                                                                                                                                                                                                                                                               
                                                                                                                                                                                                                                                                                                                                  
#define SYSCALL_DEFINE(name) static inline long SYSC_##name                                                                                                                                                                                                                                                                       
                                                                                                                                                                                                                                                                                                                                  
#define __SYSCALL_DEFINEx(x, name, ...)                    \                                                                                                                                                                                                                                                                      
    asmlinkage long sys##name(__SC_DECL##x(__VA_ARGS__));        \                                                                                                                                                                                                                                                                
    static inline long SYSC##name(__SC_DECL##x(__VA_ARGS__));    \                                                                                                                                                                                                                                                                
    asmlinkage long SyS##name(__SC_LONG##x(__VA_ARGS__))        \                                                                                                                                                                                                                                                                 
    {                                \                                                                                                                                                                                                                                                                                            
        __SC_TEST##x(__VA_ARGS__);                \                                                                                                                                                                                                                                                                               
        return (long) SYSC##name(__SC_CAST##x(__VA_ARGS__));    \                                                                                                                                                                                                                                                                 
    }                                \                                                                                                                                                                                                                                                                                            
    SYSCALL_ALIAS(sys##name, SyS##name);                \                                                                                                                                                                                                                                                                         
    static inline long SYSC##name(__SC_DECL##x(__VA_ARGS__))                                                                                                                                                                                                                                                                      
                                                                                                                                                                                                                                                                                                                                  
#else /* CONFIG_HAVE_SYSCALL_WRAPPERS */                                                                                                                                                                                                                                                                                          
                                                                                                                                                                                                                                                                                                                                  
#define SYSCALL_DEFINE(name) asmlinkage long sys_##name                                                                                                                                                                                                                                                                           
#define __SYSCALL_DEFINEx(x, name, ...)                    \                                                                                                                                                                                                                                                                      
    asmlinkage long sys##name(__SC_DECL##x(__VA_ARGS__))                                                                                                                                                                                                                                                                          
                                                                                                                                                                                                                                                                                                                                  
#endif /* CONFIG_HAVE_SYSCALL_WRAPPERS */                                                                                                                                                                                                                                                                                         
                                                                                                                                                                                                                                                                                                                                  
                                                                                                                                                                                                                                                                                                                                  
                                                                                                                                                                                                                                                                                                                                  
���ջ�����������͵ĺ궨�壺                                                                                                                                                                                                                                                                                                      
                                                                                                                                                                                                                                                                                                                                  
asmlinkage long sys##name(__SC_DECL##x(__VA_ARGS__))                                                                                                                                                                                                                                                                              
Ҳ��������ǰ���ᵽ��sys_read����ϵͳ������                                                                                                                                                                                                                                                                                        
asmlinkage֪ͨ����������ջ����ȡ�ú����Ĳ��������е�ϵͳ���ö���Ҫ����޶��ʣ����������һƪ����quagga���ᵽ�ĺ궨�壬������ͬ��֮�                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                  
Ҳ���Ǻ궨���е�������룺                                                                                                                                                                                                                                                                                                        
                                                                                                                                                                                                                                                                                                                                  
struct file *file;                                                                                                                                                                                                                                                                                                                
    ssize_t ret = -EBADF;                                                                                                                                                                                                                                                                                                         
    int fput_needed;                                                                                                                                                                                                                                                                                                              
                                                                                                                                                                                                                                                                                                                                  
    file = fget_light(fd, &fput_needed);                                                                                                                                                                                                                                                                                          
    if (file) {                                                                                                                                                                                                                                                                                                                   
        loff_t pos = file_pos_read(file);                                                                                                                                                                                                                                                                                         
        ret = vfs_read(file, buf, count, &pos);                                                                                                                                                                                                                                                                                   
        file_pos_write(file, pos);                                                                                                                                                                                                                                                                                                
        fput_light(file, fput_needed);                                                                                                                                                                                                                                                                                            
    }                                                                                                                                                                                                                                                                                                                             
                                                                                                                                                                                                                                                                                                                                  
    return ret;                                                                                                                                                                                                                                                                                                                   
                                                                                                                                                                                                                                                                                                                                  
                                                                                                                                                                                                                                                                                                                                  
                                                                                                                                                                                                                                                                                                                                  
���������                                                                                                                                                                                                                                                                                                                        
                                                                                                                                                                                                                                                                                                                                  
fget_light() ������ fd ָ�����������ӵ�ǰ������������ȡ����Ӧ�� file ���󣨼�ͼ3����                                                                                                                                                                                                                                              
���û�ҵ�ָ���� file �����򷵻ش���                                                                                                                                                                                                                                                                                            
����ҵ���ָ���� file ����                                                                                                                                                                                                                                                                                                      
���� file_pos_read() ����ȡ���˴ζ�д�ļ��ĵ�ǰλ�á�                                                                                                                                                                                                                                                                             
���� vfs_read() ִ���ļ���ȡ������������������յ��� file->f_op.read() ָ��ĺ������������£�                                                                                                                                                                                                                                     
if (file->f_op->read)                                                                                                                                                                                                                                                                                                             
ret = file->f_op->read(file, buf, count, pos);                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                                  
���� file_pos_write() �����ļ��ĵ�ǰ��дλ�á�                                                                                                                                                                                                                                                                                    
���� fput_light() �����ļ������ü�����                                                                                                                                                                                                                                                                                            
��󷵻ض�ȡ���ݵ��ֽ�����                                                                                                                                                                                                                                                                                                        
���ˣ������ļ�ϵͳ�������Ĵ��������ˣ�����Ȩ������ ext2 �ļ�ϵͳ�㡣                                                                                                                                                                                                                                                            
    



                                                                                                                                                                                                                                                                                                                              

































































































































































































































































































































































































































