#ifndef RB_DATA_H
#define RB_DATA_H

/* Helper layer for storing (key, object) pairs in the tree. */

typedef struct mydata {
    int key;        /* here: vruntime of process */
    void *object;   /* here: struct process* */
} mydata;

/* Allocator for mydata */
mydata *makedata_with_object(int key, void *object);

/* Compare function for rbtree: compares mydata->key (ascending). */
int compare_func(const void *a, const void *b);

/* Destroy function for rbtree: frees mydata only (not the embedded object). */
void destroy_func(void *data);

#endif /* RB_DATA_H */
