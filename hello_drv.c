#include <linux/module.h>

#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/kmod.h>
#include <linux/gfp.h>

static char kernel_buf[1024];
#define MIN(a b) (a < b ? a:b)
static struct class *hello_class;

//① 确定主设备号，也可以让内核分配
static int major;
//③ 实现对应的 drv_open/drv_read/drv_write 等函数，填入 file_operations 结构体
static ssize_t hello_drv_read (struct file *file, char __user *buf, size_t size, loff_t *offset)
{
   int err;
   err = copy_to_user(buf, kernel_buf, MIN(1024, size));
   printk("%s %s line %d\n",_FILE_, __FUNCTION__, __LINE__);
   return MIN(1024, size);
}
static ssize_t hello_drv_write (struct file *file, const char __user *buf, size_t size, loff_t *offset)
{
   int err;
   copy_from_user(kernel_buf,buf, MIN(1024, size));
   err = printk("%s %s line %d\n",_FILE_, __FUNCTION__, __LINE__);
   return MIN(1024, size);
}
static int hello_drv_open (struct inode *node, struct file *file)
{
   printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
   return 0;
}
static int hello_drv_realse (struct inode *node, struct file *file)
{
   printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
   return 0;
}


//② 定义自己的 file_operations 结构体
static const struct file_operations hello_drv = {
	.owner		= THIS_MODULE,
	.open		= hello_drv_open,
	.write      = hello_drv_write,
	.read    	= hello_drv_read,
	.release	= hello_drv_realse,
};


//④ 把 file_operations 结构体告诉内核： register_chrdev
static int __init misc_init(void)
{
  int err;
  printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
  major = register_chrdev(0,"hello_drv",&hello_drv);
  hello_class = class_create(THIS_MODULE, "hello_class");
  err = PTR_ERR(hello_class);
  if(IS_ERR(hello_class))
  	{
  	  printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	  unregister_chrdev(major, "hello");
	  return -1;
  	}

  device_create(hello_class, NULL, MKDEV(major, 0), NULL, "hello"); 
  return 0;
}

static void __exit hello_exit(void)
{
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	device_destroy(hello_class, MKDEV(major, 0));
	class_destroy(hello_class);
	unregister_chrdev(major, "hello");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");

//⑤ 谁来注册驱动程序啊？得有一个入口函数：安装驱动程序时，就会去调用这个入口函数
//⑥ 有入口函数就应该有出口函数：卸载驱动程序时，出口函数调用 unregister_chrdev
//⑦ 其他完善：提供设备信息，自动创建设备节点： class_create, device_create


