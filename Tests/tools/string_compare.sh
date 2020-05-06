#!/bin/bash

# get input from pipe and terminal
# usage: echo "string" | ./compare_string.sh "string"
# 0 equal, 1 not equal
set -x

if [ ! -t 0 ]; then
    read pipe_input
fi

arg_input="$*"

if [ "$pipe_input" == "$arg_input" ]; then
    exit 0
else
    exit 1
fi