# Lab: system calls

## System call tracing
要实现`trace()`，首先看xv6是如何实现系统调用的。

### xv6的系统调用实现
1. 用户态程序发起系统调用，此时表现为函数调用，把参数压栈。之后把系统调用好存入`a7`寄存器。
3. 内核中的[`syscall.c:138-141`](https://github.com/huyyi/MIT6S081-docker/tree/syscall/kernel/syscall.c#L138)从寄存器`a7`中取出系统调用号执行系统调用
4. 由于已经不再是函数调用了，内核中的系统调用都没有参数，而系统调用的参数利用用户空间的`%esp`寄存器定位第`n`个参数：`%esp`指向系统调用结束后的返回地址。参数就恰好在`%esp`之上（`%esp+4`）。因此第`n`个参数就在`%esp+4*(n+1)`。

### `trace()`内核中的实现
1. 在`sys_trace`系统调用的时候在`PCB`上做相应的记录（[kernel/sysproc.c:106](https://github.com/huyyi/MIT6S081-docker/tree/syscall/kernel/sysproc.c#L106)），在`fork()`时子进程同样要继承相应的记录（[kernel/proc.c:296](https://github.com/huyyi/MIT6S081-docker/tree/syscall/kernel/proc.c#L296)）
2. 在系统调用时输出相关trace信息（[kernel/syscall.c:170](https://github.com/huyyi/MIT6S081-docker/tree/syscall/kernel/syscall.c#L170)）
