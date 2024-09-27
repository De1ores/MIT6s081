```cpp
struct proc
```

描述进程的结构体,表示进程的状态,有进程的页表,进程的文件打开表...

```cpp
void syscall(void){
  int num;
  struct proc *p = myproc();
  num = p->trapframe->a7;
  if(num > 0 && num < NELEM(syscalls) && syscalls[num]) {
    p->trapframe->a0 = syscalls[num]();
  } else {
    printf("%d %s: unknown sys call %d\n",
            p->pid, p->name, num);
    p->trapframe->a0 = -1;
  }
}
```

print " li a7, SYS_${name}\n";
在RISC-V汇编中，li指令用于加载立即数到寄存器，这里将系统调用编号加载到寄存器a7中.
SYS_${name}是一个宏，它会被替换为对应的系统调用编号.
print "ecall\n";：执行ecall指令，这是RISC-V架构中触发系统调用的指令。

当用户进行系统调用时，编译器会把系统调用号放到寄存器a7中，然后调用ecall指令


获取当前的运行的进程的task_struct

```cpp 
// Return the current struct proc *, or zero if none.
struct proc* myproc(void) {
  push_off();
  struct cpu *c = mycpu();
  struct proc *p = c->proc;
  pop_off();
  return p;
} 
```




