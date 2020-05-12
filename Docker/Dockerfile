FROM ubuntu:20.04

COPY sources.list /etc/apt/sources.list
COPY sshd_config /etc/ssh/sshd_config

WORKDIR /root/SynestiaOS

ARG DEBIAN_FRONTEND=noninteractive

RUN apt update \
    && apt install --fix-missing -y build-essential binutils qemu-system-arm gdb-multiarch gcc-arm-none-eabi gcc-aarch64-linux-gnu make cmake gcc clang-format-10 ssh rsync \
    && update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-10 100 \
    && apt clean \
    && rm -rf /var/cache/apt/archives \
    && mkdir /run/sshd \
    && yes password | passwd root

CMD ["/usr/sbin/sshd", "-D"]
