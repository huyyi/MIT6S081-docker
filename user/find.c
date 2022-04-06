#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find_sub(char *path, char *target) {
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      // printf("buf: %s \t path: %s \t file: %s\n", buf, path, de.name);
      if (st.type == T_FILE && !strcmp(de.name, target))
        printf("%s\n", buf);
      else if (st.type == T_DIR && strcmp(de.name, ".") && strcmp(de.name, "..")) 
        find_sub(buf, target);
    }
    break;
  }
}

int main(int argc, char *argv[]) {
  if (argc == 2) 
  {
    find_sub(".", argv[1]);
  }
  else if (argc == 3) 
  {
    find_sub(argv[1], argv[2]);
  }
  exit(0);
}