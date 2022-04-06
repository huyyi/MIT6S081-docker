#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void process(int p) {
    int pn[2], t, prime;

    read(p, &prime, sizeof prime);
    fprintf(0, "prime %d \n", prime);

    if (prime == 31) {
        close(p);
        exit(0);
    }

    pipe(pn);

    if (fork() == 0) {
        close(pn[1]);
        process(pn[0]);
    } else {
        close(pn[0]);
        while (read(p, &t, sizeof t)) {
            if (t % prime) {
                write(pn[1], &t, sizeof t);
            }
        }
        close(pn[1]);
        close(p);
        wait(0);
    }
    exit(0);
}

int main(int argc, char *argv[]) {
    int pn[2];

    pipe(pn);

    if (fork() == 0) {
        close(pn[1]);  // 子进程不需要使用用于read的pn[1]，关闭
        process(pn[0]);
    } else {
        close(pn[0]);  // 父进程不需要使用用于write的pn[0]，关闭
        for (int i = 2; i < 35; ++i) {
            write(pn[1], &i, sizeof i);
        }
        close(pn[1]);  // 发送完毕及时关闭
        wait(0);
    }
    exit(0);
}
