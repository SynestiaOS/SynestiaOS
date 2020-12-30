#!/usr/bin/env bash

BASEDIR=$(realpath "$(dirname "$0")")
BUILD_DIR="${BASEDIR}"/buildRaspi3

rm -rf "${BUILD_DIR}"
mkdir "${BUILD_DIR}"
cd "${BUILD_DIR}" || exit
cmake -DCMAKE_TOOLCHAIN_FILE="${BASEDIR}"/../CMake/ToolchainMacArm64.cmake -DARCH=arm64 -DPLATFORM=pi3 "${BASEDIR}/.."
VERBOSE=1 make

echo ">>>>>>>>>>>>>>>> RUNNING KERNEL <<<<<<<<<<<<<<<<"
qemu-system-aarch64 -M raspi3 -kernel ./bin/Kernel.elf -serial mon:stdio -nographic
