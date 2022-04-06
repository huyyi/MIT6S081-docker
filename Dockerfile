FROM ubuntu:20.04
ARG arch_name=amd64

# 创建一个mit6s081的用户和其home目录
RUN useradd -m mit6s081 && \
    echo "root ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers && \
    echo "mit6s081 ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers 
    
# 设置一些环境变量
ENV TZ=Asia/Shanghai \
    LANG=en_US.utf8 \
    LANGUAGE=en_US.UTF-8 \
    LC_ALL=en_US.UTF-8 \
    DEBIAN_FRONTEND=noninteractive


# MIT6.S081 Lab所用依赖
# 1.安装RISC-V交叉编译工具和一些其他的常用工具
RUN apt-get update && \
    apt-get install -y git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu 