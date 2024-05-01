#include<linux/module.h>
#include<linux/proc_fs.h>
#include<linux/uaccess.h>

MODULE_LICENSE("GPL");

static char hello_data[20] = {"Hello World!\n"};

static ssize_t hello_proc_read(struct file *fp, char __user *user_buf, size_t count, loff_t *ppos){
	int ret = 0;
	if(clear_user(user_buf,count)){
		printk(KERN_ERR "clear error\n");
		return -EIO;
	}

	ret = simple_read_from_buffer(user_buf, count, ppos, hello_data, strlen(hello_data));
	return ret;	
}

static const struct file_operations hello_proc_fops = {
        .owner = THIS_MODULE,
        .read = hello_proc_read,
};

struct proc_dir_entry *hello_proc = NULL;

int __init module3_init(void){
	printk(KERN_INFO "file hello_proc created.\n");
	hello_proc = proc_create("hello_proc",0444,NULL,&hello_proc_fops);
	return 0;
}

void __exit module3_exit(void){
	if(hello_proc){
		remove_proc_entry("hello_proc", NULL);
		printk(KERN_INFO "file hello_proc removed.\n");
	}
}

module_init(module3_init);
module_exit(module3_exit);
