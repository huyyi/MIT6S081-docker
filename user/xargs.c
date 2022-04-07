#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    char buf[1024];
    if (argc < 2) 
    {
        fprintf(2, "Error, not enough parameters");
        exit(1);
    }

    int n = strlen(argv[1]);
    char *cmd = malloc(n + 1);
    memmove(cmd, argv[1], n);
    cmd[n] = 0;

    int i = 0;
    char *call_args[MAXARG];
    for (; i + 1 < argc; ++i) {
        call_args[i] = argv[i + 1];
    }

    while (*gets(buf, 1024)) {
        // gets行尾有换行符需要处理
        n = strlen(buf);
        if (buf[n - 1] == '\n' || buf[n - 1] == '\r') buf[n - 1] = 0;
        call_args[i] = buf;
        // for (int k = 0; k <= i; k++) {
        //     fprintf(1, call_args[k]);
        //     fprintf(1, " ");
        // }
        if (fork() == 0) {
            exec(cmd, call_args);
            exit(1);
        } else {
            wait(0);
        }
    }
    exit(0);
}