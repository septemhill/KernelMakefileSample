#include <pm1.h>

void show(int var)
{
  printk(KERN_INFO "Count: %d", var);
}
