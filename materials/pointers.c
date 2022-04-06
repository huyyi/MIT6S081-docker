#include <stdio.h>
#include <stdlib.h>

void
f(void)
{
    int a[4];
    int *b = malloc(16);
    int *c;
    int i;

    printf("1: a = %p, b = %p, c = %p\n", a, b, c);
    // 1. a = 数组a的起始地址（栈上），b = 16个字节的堆空间地址的起始位置（堆上），c = 指向整型的指针

    c = a;
    for (i = 0; i < 4; i++)
	a[i] = 100 + i;  // a = {100, 101, 102, 103}
    c[0] = 200;  // a = {200, 101, 102, 103}
    printf("2: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
	   a[0], a[1], a[2], a[3]);

    c[1] = 300;  // a = {200, 300, 102, 103}
    *(c + 2) = 301;  // a = {200, 300, 301, 103}
    3[c] = 302;  // a = {200, 300, 301, 302}
    printf("3: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
	   a[0], a[1], a[2], a[3]);

    c = c + 1;
    *c = 400;  // a = {200, 400, 301, 302}
    printf("4: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
	   a[0], a[1], a[2], a[3]);

    c = (int *) ((char *) c + 1);  
    *c = 500;
    printf("5: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
	   a[0], a[1], a[2], a[3]);

    b = (int *) a + 1;
    c = (int *) ((char *) a + 1);
    printf("6: a = %p, b = %p, c = %p\n", a, b, c);
}

int
main(int ac, char **av)
{
    f();
    return 0;
}