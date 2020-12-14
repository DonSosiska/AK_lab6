#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>

#include <linux/types.h>

struct list_head_AC {
	struct list_head_AC *next;
	ktime_t time;
};

MODULE_AUTHOR("DonSosiska <don.sosiska339@gmail.com>");
MODULE_DESCRIPTION("Helloooooooooooooo!");
MODULE_LICENSE("Dual BSD/GPL");

static struct list_head_AC *head;

static uint repetitions = 1;
module_param(repetitions, uint, S_IRUGO);
MODULE_PARM_DESC(repetitions, "The amount of times to print hello world");

static int __init initter(void)
{
	uint i = 1;
	struct list_head_AC *head1, *head2;
	head = kmalloc(sizeof(struct list_head_AC *), GFP_KERNEL);
	head->next = NULL;
	head->time = ktime_get();
	head1 = head;


	printk(KERN_INFO "Repetitions: %d\n", repetitions);
	if (repetitions == 0) {
		printk(KERN_WARNING "The parameter is 0");
	} else if (repetitions >= 5 && repetitions <= 10) {
		printk(KERN_WARNING "The parameter is between 5 and 10");
	} else if (repetitions > 10) {
		printk(KERN_ERR "The parameter is greater than 10");
	return -EINVAL;
	}

	for (i = 0; i < repetitions; i++) {
		head1->next = kmalloc(sizeof(struct list_head_AC *), GFP_KERNEL);
		head1->time = ktime_get();
		head2 = head1;
		head1 = head1->next;
		pr_info("Hello, world!\n");
	}
	if (repetitions != 0) {
		kfree(head2->next);
		head2->next = NULL;
	}
	return 0;
}

static void __exit exitter(void)
{
	struct list_head_AC *head1 = head;
	struct list_head_AC *head2 = head1;

	pr_err("%p", head);
	while (head1 != NULL) {
		pr_info("%lld", head1->time);
		head2 = head1;
		head1 = head2->next;
		kfree(head2);
	}
	pr_info("");
}

module_init(initter);
module_exit(exitter);
