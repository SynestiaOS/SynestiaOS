#!/bin/bash

sudo apt-get update

sudo apt install -y qemu-system-arm \
                gdb-multiarch \
                gcc-arm-none-eabi \
                gcc-aarch64-linux-gnu \
                make \
                gcc