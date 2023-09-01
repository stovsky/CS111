#include <linux/module.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>

static struct proc_dir_entry* new_proc;

static int count_processes(struct seq_file* m, void* v)
{
  int count = 0;
  struct task_struct* t;
  for_each_process(t) {
    count++;
  }
  seq_printf(m, "%d\n", count);
  return 0;
}


static int __init proc_count_init(void)
{
	pr_info("proc_count: init\n");
	new_proc = proc_create_single("count", 0, NULL, count_processes);
       	return 0;
}

static void __exit proc_count_exit(void)
{
	pr_info("proc_count: exit\n");
	proc_remove(new_proc);
}

module_init(proc_count_init);
module_exit(proc_count_exit);

MODULE_AUTHOR("Tyler Stovsky");
MODULE_DESCRIPTION("Adds a file /proc/count which reports the current number of running processes.");
MODULE_LICENSE("GPL");
