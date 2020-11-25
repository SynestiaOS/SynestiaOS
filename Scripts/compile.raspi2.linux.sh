#!/usr/bin/env bash

BASEDIR=$(dirname "$0")
BUILD_DIR="${BASEDIR}"/buildRaspi2

rm -rf "${BUILD_DIR}"
mkdir "${BUILD_DIR}"
cd "${BUILD_DIR}" || exit
cmake -DCMAKE_TOOLCHAIN_FILE="${BASEDIR}"/../../CMake/ToolchainLinuxArm.cmake -DARCH=arm -DPLATFORM=pi2 "${BASEDIR}/../.."
VERBOSE=1 make
