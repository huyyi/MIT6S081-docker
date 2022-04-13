FROM ubuntu:20.04
ARG arch_name=amd64

# set time zone
ENV TZ=Asia/Shanghai \
    DEBIAN_FRONTEND=noninteractive
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# set gdb config
RUN mkdir /vx6 && echo add-auto-load-safe-path /xv6 >> /root/.gdbinit

# install compaile tools
# rsync and cmake for clion remote
RUN apt-get update && \
    apt-get install -y openssh-server rsync cmake git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu

# set sshd for remote develop
RUN echo 'root:passwd' | chpasswd && \
    mkdir /run/sshd && \
    sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

WORKDIR /xv6
CMD ["/usr/sbin/sshd", "-D"]
