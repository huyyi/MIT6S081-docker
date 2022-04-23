# Lab pgtbl: Page tables

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

## Print a page table

### `RISC-V` 的 `PTE` 结构
![](/imgs/PTE_struct.png)

1. 使用 44 位地址作为下一级页表的地址
2. 10 位的标志位

### 怎么查找下一级页表的 `PTE`
![](/imgs/vm2pm.png)

虚拟地址 64 位只使用了 39 位，第一级页表地址在 `satp` 寄存器中，通过 `satp[l2]` 即可访问对应的 `PTE`（用十进制表示 `l2` 即可），拿到 44 位的下一级页表地址，再使用中间9位拼接访问第三级页表最后得到 `44 + 12 = 64` 位的物理地址。
 
### 如何判断当前页表项是否为 `leaf`？
从源码的 `freewalk()`来看：
```C
// R, W, X 标志位全为0
if((pte & PTE_V) && (pte & (PTE_R|PTE_W|PTE_X)) == 0){
    // this PTE points to a lower-level page table.
    uint64 child = PTE2PA(pte);
    freewalk((pagetable_t)child);
    pagetable[i] = 0;
} else if(pte & PTE_V){
    panic("freewalk: leaf");
}
```

## Detecting which pages have been accessed
MMU 在进行虚拟地址转换时，在访问页表项时会将访问位标记。

