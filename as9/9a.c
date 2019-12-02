#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENCSE("GPL");
MODULE_AUTHOR("Saurabh");
MODULE_DESCRIPTION("LKM");


int init_module(void){
    printk(KERN_INFO "Loaded successfully\n");
    return 0;
}
void cleanup_module(void){
    printk(KERN_INFO "Done....so byee");
}