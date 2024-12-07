/*
 * Copyright (c) 2019 xieqing. https://github.com/xieqing
 * May be freely redistributed, but copyright notice must be retained.
 */

#ifndef _RB_DATA_HEADER
#define _RB_DATA_HEADER

typedef struct {
	void* object;
	int key;
} mydata;

mydata *makedata(int key);
mydata *makedata_with_object(int key, void* object);
int compare_func(const void *d1, const void *d2);
void destroy_func(void *d);
void print_func(void *d);
void print_char_func(void *d);

#endif /* _RB_DATA_HEADER */

