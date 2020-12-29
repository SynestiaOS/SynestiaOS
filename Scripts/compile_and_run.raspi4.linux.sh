#!/usr/bin/env bash

BASEDIR=$(realpath "$(dirname "$0")")
BUILD_DIR="${BASEDIR}"/buildRaspi4

rm -rf "${BUILD_DIR}"
mkdir "${BUILD_DIR}"
cd "${BUILD_DIR}" || exit
cmake -DCMAKE_TOOLCHAIN_FILE="${BASEDIR}"/../CMake/ToolchainLinuxArm.cmake -DARCH=arm -DPLATFORM=pi4 "${BASEDIR}/.."
VERBOSE=1 make
