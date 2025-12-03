#include <stdlib.h>
#include "rb_data.h"

mydata *makedata_with_object(int key, void *object) {
    mydata *d = (mydata *)malloc(sizeof(mydata));
    if (!d) return NULL;
    d->key = key;
    d->object = object;
    return d;
}

int compare_func(const void *a, const void *b) {
    const mydata *da = (const mydata *)a;
    const mydata *db = (const mydata *)b;

    if (da->key < db->key) return -1;
    if (da->key > db->key) return 1;
    return 0;
}

void destroy_func(void *data) {
    if (!data) return;
    free(data);
}
