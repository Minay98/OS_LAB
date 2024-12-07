#!/bin/bash

gcc red_black_tree/rb.c red_black_tree/rb_data.c proc.c cfs_scheduler.c -o cfs_scheduler.out && time ./cfs_scheduler.out
