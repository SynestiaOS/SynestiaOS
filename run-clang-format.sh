#!/usr/bin/env bash

BASEDIR=$(dirname "$0")

find "${BASEDIR}/SourceCode" -type f \( -name '*.h' -o -name '*.c' -o -name '*.hpp' -o -name '*.cc' -o -name '*.cpp' \) -exec echo "clang-format: {}" \; -a -exec clang-format -i "{}" \;
