# Lab pgtbl: Page tables

## Notes

## Speed up system calls

### `fork()`进程创建流程
1. 在进程数组中找一个`UNUSED`的槽位
2. 为进程分配`pid`
3. 为进程分配`trapframe`，空间为1页
4. 为进程构建页表（proc_pagetable()）
5. 为进程设置上下文包含`ra`和`sp`寄存器

### `proc_pagetable()`构建页表流程
1. 分配一页内存
2. 为内核态用户态切换代码`trampoline`（对应`trampoline.S`）映射物理内存，虚拟地址为可用虚拟地址的最高一页
3. 为陷入内核的栈帧映射内存

### 页表权限解释
- `V`: valid, 页是否可用
- `R`: 内核可读
- `W`: 内核可写
- `X`: 内核可执行
- `U`: 用户态可访问

### 实验[commit:419850](https://github.com/huyyi/MIT6S081-docker/commit/dcad2cb7692a8b7a27bf9849d25eaca619419850)
1. 在进程结构体中添加一个指向`usyscall`结构体的指针
2. 在`alloc_proc`中为`usyscall`页分配内存，注意`kalloc`分配的地址是物理地址。同时要在`free_proc`释放内存，在`proc_freepagetable`销毁页内存
3. 在`proc_pagetable`中添加虚拟地址到`usyscall`页的页表，标记位为`PTE_R | PTE_W | PTE_U`