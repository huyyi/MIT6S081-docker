#include "types.h"
#include "riscv.h"
#include "param.h"
#include "defs.h"
#include "date.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

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


#ifdef LAB_PGTBL
/* 
System call that reports which pages have been accessed. 
va_st: Starting virtual address of the first user page to check.
pgnum: the number of pages to check.
bufaddr: user address to a buffer to store the results into a bitmask
*/
int
sys_pgaccess(void)
{
  uint64 va_st, bufaddr;
  int pgnum;
  uint32 buf = 0;

  if (argaddr(0, &va_st) < 0)
    return -1;
  if (argint(1, &pgnum) < 0 || pgnum > 32)
    return -1;
  if (argaddr(2, &bufaddr) < 0)
    return -1;

  struct proc *p;
  if ((p = myproc()) == 0)
    return -1;
  pagetable_t tbl = p->pagetable;
  pte_t *pte;
  for (int i = 0; i < pgnum; ++i) {
    pte = walk(tbl, va_st + i * PGSIZE, 0);
    if (*pte && *pte & PTE_A) {
      buf |= 1 << i;
      *pte &= ~PTE_A;
    }
  }
  if (copyout(tbl, bufaddr, (char *)&buf, sizeof buf) < 0)
      return -1;
  return 0;
}
#endif

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
