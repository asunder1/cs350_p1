#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

// copy pasted from ulib.c to avoid errors from doing #include "ulib.c"
int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}



int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


int
sys_shutdown(void)
{
  outw(0xB004, 0x0|0x2000);
  outw(0x604, 0x0|0x2000);
  return 0;
}

int 
sys_shutdown2(void) {
  char *msg;
  if(argstr(0, &msg) < 0)
    return -1;
  
  cprintf("%s\n", msg);

  // Send a special command to QEMU to trigger the shutdown
  outw(0xB004, 0x0|0x2000);
  outw(0x604, 0x2000);  // This sends a shutdown signal to QEMU (using Bochs/QEMU-compatible port)
  return 0;
}

int sys_exit2(void) {
  int status;
  if (argint(0, &status) < 0)
      return -1;

  cprintf("Process exited with status: %d\n", status);
  exit(); 
  return 0; 
}

int sys_uptime2(void) {
  int option;
  uint xticks;

  if(argint(0, &option) < 0)
      return -1;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);

  if (option == 1) {
      return xticks;
  } else if (option == 2) {
      return xticks / 100;  
  } else if (option == 3) {
      return xticks / (100 * 60);  
  }
  
  return -1; 
}
