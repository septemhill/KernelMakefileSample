#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h> // for threads
#include <linux/sched.h>   // for task_struct
#include <linux/time.h>    // for using jiffies 
#include <linux/timer.h>
#include <linux/kfifo.h>   // for kfifo
#include <pm1.h>           // for "show" function
#include <dev1.h>          // for "dev_display" function
#include <dri1.h>          // for "backup" function
#include <sys1.h>

static struct task_struct *thread1;
static struct task_struct *thread2;


#define BUFF_SIZE (20)

int thread_fn1(void *data) 
{
  unsigned long timeout;
  unsigned long count = 0;

  printk(KERN_INFO "In thread1\n");

  while (1) {
    if (kthread_should_stop()) break;

    show(count++);
    dev_display();
    back(1000);

    do {
      set_current_state(TASK_INTERRUPTIBLE);
      timeout = schedule_timeout(3 * HZ);
    } while (timeout);
  }

  return 0;
}

int thread_fn2(void *data) 
{
  unsigned long timeout;
  
  printk(KERN_INFO "In thread2\n");

  while (1) {
    if (kthread_should_stop()) break;

    printk("Hi, Septem\n");

    do {
      set_current_state(TASK_INTERRUPTIBLE);
      timeout = schedule_timeout(3 * HZ);
    } while (timeout);
  }

  return 0;
}

static int __init thread_init (void) 
{
  printk(KERN_INFO "[INIT THREAD]\n");

  thread1 = kthread_create(thread_fn1, NULL, "Septem");

  if((thread1)) {
    printk(KERN_INFO "[T1] INIT\n");
    wake_up_process(thread1);
  }

  thread2 = kthread_create(thread_fn2, NULL, "Hill");
  if ((thread2)) {
    printk(KERN_INFO "[T2] INIT\n");
    wake_up_process(thread2);
  }

  return 0;
}

void thread_cleanup(void) 
{
  int ret1, ret2;
 
  ret1 = kthread_stop(thread1);
  ret2 = kthread_stop(thread2);
 
  if (!ret1) {
    printk(KERN_INFO "Thread 1 stopped\n");
  }

  if (!ret2) {
    printk(KERN_INFO "Thread 2 stopped\n");
  }
}

MODULE_LICENSE("GPL");   
module_init(thread_init);
module_exit(thread_cleanup);

