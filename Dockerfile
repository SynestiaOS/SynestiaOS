FROM ubuntu:20.04

COPY sources.list /etc/apt/sources.list

WORKDIR /root/SynestiaOS

ARG DEBIAN_FRONTEND=noninteractive

RUN apt update \
    && apt install -y build-essential binutils qemu-system-arm gdb-multiarch gcc-arm-none-eabi gcc-aarch64-linux-gnu make gcc \
    && apt clean \
    && rm -rf /var/cache/apt/archives
