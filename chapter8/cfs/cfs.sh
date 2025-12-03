#!/bin/sh
set -e

echo "Compiling CFS scheduler example..."
gcc -std=c11 -Wall -Wextra -g \
    proc.c cfs_scheduler.c \
    red_black_tree/rb.c red_black_tree/rb_data.c \
    -o cfs

echo "Running CFS scheduler..."
./cfs
