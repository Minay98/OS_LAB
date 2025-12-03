CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

RBT_DIR = red_black_tree

RBT_SRCS = $(RBT_DIR)/rb.c $(RBT_DIR)/rb_data.c
RBT_TEST_SRCS = $(RBT_SRCS) $(RBT_DIR)/rb_test.c
RBT_EXAMPLE_SRCS = $(RBT_SRCS) $(RBT_DIR)/rb_example.c

CFS_SRCS = proc.c cfs_scheduler.c $(RBT_SRCS)

all: cfs rb_test rb_example

cfs: $(CFS_SRCS)
	$(CC) $(CFLAGS) $(CFS_SRCS) -o cfs

rb_test: $(RBT_TEST_SRCS)
	$(CC) $(CFLAGS) $(RBT_TEST_SRCS) -o rb_test

rb_example: $(RBT_EXAMPLE_SRCS)
	$(CC) $(CFLAGS) $(RBT_EXAMPLE_SRCS) -o rb_example

clean:
	rm -f cfs rb_test rb_example
