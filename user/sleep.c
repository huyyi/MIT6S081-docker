#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error! Time to sleep?\n");
        exit(1);
    }

    int dura = atoi(argv[1]);
    sleep(dura);
    exit(0);
}