#include<linux/module.h>
#include<linux/moduleparam.h>

MODULE_LICENSE("GPL");

static int int_var = 1984;
module_param(int_var, int, 0644);
MODULE_PARM_DESC(int_var, "int param\n");

static char* str_var = "Lancer";
module_param(str_var, charp, 0644);
MODULE_PARM_DESC(str_var, "char* param\n");

static int array_size;
module_param(array_size, int, 0644);
MODULE_PARM_DESC(array_size, "int param\n");

static int int_array[10];
module_param_array(int_array, int, &array_size, 0644);
MODULE_PARM_DESC(int_array, "int_array param\n");

void print_variable(int int_var, char* str_var, int* int_array){
	int i;
	printk(KERN_INFO "int_var: %d.\n", int_var);
	printk(KERN_INFO "str_var: %s.\n", str_var);
	for(i = 0; i < array_size; i++){
	printk(KERN_INFO "int_array[%d]: %d.\n", i, int_array[i]);
	}
}

int __init module2_init(void){
	print_variable(int_var, str_var, int_array);
	return 0;
}

void __exit module2_exit(void){

}

module_init(module2_init);
module_exit(module2_exit);
