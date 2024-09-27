#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sysinfo.h"

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
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

uint64
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

uint64
sys_kill(void)
{
  int pid;
  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64 sys_trace(void){
  int mask;
  if(argint(0, &mask) < 0)
    return -1;
  trace(mask);
  return 0;
}
int sysinfo_(uint64 pinfo);
uint64 sys_sysinfo(void){
   uint64 pinfo;
   if(argaddr(0, &pinfo) < 0) return -1;
   if(sysinfo_(pinfo)<0) return -1;
   return 0;
}

int sysinfo_(uint64 pinfo){
   struct proc *p = myproc();
   struct sys_info_t info;
   info.freemem=collect_free_count(); 
   info.nproc=collect_process_count();
   if(copyout(p->pagetable,pinfo,(char*)&info, sizeof(struct sys_info_t)) < 0)
     return -1;
   return 0;
}

/*

copyout的过程:
程序: void f(struct xx *);
f(void){
   uint64 p;
   argaddr(n,&p);
   f_(p);
}

f_(uint64 addr){
  struct xx *;
}


上面参照fstat filestat写.
sysinfo_ 如果声明 struct sys_info_t *t;会报错，指针未初始化。
所以需要声明为局部变量，然后使用.初始化。


*/
