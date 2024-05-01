#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");

int __init module1_init(void){
	printk(KERN_INFO "Init module.\n");
	
	return 0;
}

void __exit module1_exit(void){
	printk(KERN_INFO "Exit module.\n");
}

module_init(module1_init);
module_exit(module1_exit);
