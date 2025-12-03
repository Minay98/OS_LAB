#!/bin/sh
set -e

echo "Compiling red-black tree tests..."
gcc -std=c11 -Wall -Wextra -g \
    rb.c rb_data.c rb_test.c \
    -o rb_test

echo "Running tests..."
./rb_test
