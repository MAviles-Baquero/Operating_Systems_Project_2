/*
Maria Elena Aviles-Baquero
CPSC 346
Project 2: Linux Kernel Modules
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

/*Creates Linked List Structure*/
struct person {
	int month;
	int day;
	int year;
	struct person *next;
};

/*Initializes a Linked List*/
struct person *list_enter;

	
/* This function is called when the module is loaded. */
int simple_init(void)
{
	/*Outputs to the Kernel Buffer that Module is Loading*/
	printk(KERN_INFO "Loading Module\n");
	
	printk(KERN_INFO "Printing List...\n");
	printk(KERN_INFO "Day / Month / Year\n");

	/*Traverses Linked List and Prints Out Values*/
	int i;
	for(i = 0; i < 5; i++) {
		list_enter = kmalloc(sizeof(*list_enter), GFP_KERNEL);
		list_enter->day = 10 + i;
		list_enter->month = 6 + i;
		list_enter->year = 2000 + i;
		list_enter->next = NULL;
		printk(KERN_INFO "%d / %d / %d\n", list_enter->day, list_enter->month, list_enter->year);
	}
	
	return 0;
}


/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module...\n");
	/**/
	struct person *curr;
	struct person *ptr;
	curr = list_enter;
	
	int j;
	for(j = 0; j < 5; j++) {
		ptr = curr->next;
		curr = NULL;
		curr = ptr;
	}
	
	printk(KERN_INFO "Nodes Freed; Module Removed\n");
	
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

