#include<linux/module.h>
#include<linux/proc_fs.h>
#include<linux/uaccess.h>

MODULE_LICENSE("GPL");

static char hello_data[20] = {"Hello World!\n"};

static ssize_t hello_read(struct file *fp, char __user *user_buf, size_t count, loff_t *ppos){
        int ret = 0;
        if(clear_user(user_buf,count)){
                printk(KERN_ERR "clear error\n");
                return -EIO;
        }

        ret = simple_read_from_buffer(user_buf, count, ppos, hello_data, strlen(hello_data));
        return ret;
}

static ssize_t hello_write(struct file *fp, const char __user *user_buf, size_t count, loff_t *ppos){
	int ret;
	printk(KERN_INFO "hello_write: count is %ld.\n", count);
	memset(hello_data, 0, sizeof(hello_data));
	ret = simple_write_to_buffer(hello_data, sizeof(hello_data), ppos, user_buf, count);
	printk(KERN_INFO "hello_write: ret is %d.\n", ret);
	printk(KERN_INFO "hello_write: user_buf is %s.", hello_data);
	return count;
}

static const struct file_operations hello_fops = {
        .owner = THIS_MODULE,
        .read = hello_read,
	.write = hello_write,
};

struct proc_dir_entry *hello_dir = NULL;

struct proc_dir_entry *hello = NULL;

int __init module4_init(void){
	printk(KERN_INFO "folder hello_dir created.\n");
	hello_dir = proc_mkdir("hello_dir", NULL);
        printk(KERN_INFO "file hello created.\n");
        hello = proc_create("hello",0666,hello_dir,&hello_fops);
        return 0;
}

void __exit module4_exit(void){
        if(hello){
                remove_proc_entry("hello", hello_dir);
                printk(KERN_INFO "file hello removed.\n");
        }
	if(hello_dir){
		remove_proc_entry("hello_dir",NULL);
		printk(KERN_INFO "folder hello_dir removed.\n");
	}
}

module_init(module4_init);
module_exit(module4_exit);
