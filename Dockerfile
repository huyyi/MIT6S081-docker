FROM ubuntu:20.04
ARG arch_name=amd64

RUN apt-get update && \
    apt-get install -y git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu 