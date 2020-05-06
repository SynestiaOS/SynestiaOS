#!/bin/bash
set -x

WORKSPACE_FULL_DIR=$(cd $(dirname ${BASH_SOURCE[0]})/../../ && pwd -P)

if [ "$ARCH" = "arm" ];then
    timeout --foreground 2s qemu-system-arm -M raspi2 -kernel $WORKSPACE_FULL_DIR/Kernel/kernel -nographic | \
        $WORKSPACE_FULL_DIR/Tests/tools/string_compare.sh "hello world"
elif [ "$ARCH" = "arm64" ];then
    timeout --foreground 2s qemu-system-aarch64 -M raspi3 -kernel $WORKSPACE_FULL_DIR/Kernel/kernel -nographic | \
        $WORKSPACE_FULL_DIR/Tests/tools/string_compare.sh "hello world"    
else
    echo "Wrong arch: $ARCH"
    exit 1
fi