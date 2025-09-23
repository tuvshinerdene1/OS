#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <linux/list.h>
#include <linux/types.h>
struct birthday
{
    int month;
    int year;
    int day;
    struct list_head list;
};
static LIST_HEAD(birthday_list);

/*this function is called when the module is loaded.*/
int simple_init(void)
{
    printk(KERN_INFO "Loading Kernel Module\n");

    struct birthday *person;
    person = kmalloc(sizeof(*person), GFP_KERNEL);
    person->day = 2;
    person->month = 8;
    person->year = 1995;
    INIT_LIST_HEAD(&person->list);
    list_add_tail(&person->list, &birthday_list);

    struct birthday *person1;
    person1 = kmalloc(sizeof(*person), GFP_KERNEL);
    person1->day = 3;
    person1->month = 10;
    person1->year = 1991;
    list_add_tail(&person1->list, &birthday_list);

    struct birthday *person2;
    person2 = kmalloc(sizeof(*person), GFP_KERNEL);
    person2->day = 5;
    person2->month = 11;
    person2->year = 1995;
    list_add_tail(&person2->list, &birthday_list);

    struct birthday *person3;
    person3 = kmalloc(sizeof(*person), GFP_KERNEL);
    person3->day = 3;
    person3->month = 12;
    person3->year = 2000;
    list_add_tail(&person3->list, &birthday_list);

    struct birthday *person4;
    person4 = kmalloc(sizeof(*person), GFP_KERNEL);
    person4->day = 3;
    person4->month = 10;
    person4->year = 1910;
    list_add_tail(&person4->list, &birthday_list);

    struct birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list)
    {
        printk(KERN_INFO "%d\n", ptr->year);
        printk(KERN_INFO "%d\n", ptr->month);
        printk(KERN_INFO "%d\n", ptr->day);
    }
    return 0;
}
/*this function is called when the module is removed*/
void simple_exit(void)
{
    printk(KERN_INFO "Removing Kernel Module\n");

    struct birthday *ptr, *next;
    list_for_each_entry_safe(ptr, next, &birthday_list, list)
    {
        list_del(&ptr->list);
        kfree(ptr);
    }
}
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");