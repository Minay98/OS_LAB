#include <stdio.h>
#include <stdlib.h>
#include "rb.h"
#include "rb_data.h"

/* A small example of using the (red-)black tree with mydata. */

int main(void) {
    rbtree *t = rb_create(compare_func, destroy_func);
    if (!t) {
        fprintf(stderr, "could not create tree\n");
        return 1;
    }

    int keys[] = { 30, 10, 20, 40, 5 };
    for (int i = 0; i < 5; i++) {
        mydata *d = makedata_with_object(keys[i], NULL);
        if (!d) {
            fprintf(stderr, "out of memory\n");
            return 1;
        }
        rb_insert(t, d);
    }

    printf("Inserted 5 nodes. Minimal key should be 5.\n");
    rbnode *min = RB_MINIMAL(t);
    if (min) {
        mydata *d = (mydata *)min->data;
        printf("Minimal key = %d\n", d->key);
    } else {
        printf("Tree is empty!\n");
    }

    rb_destroy(t);
    return 0;
}
