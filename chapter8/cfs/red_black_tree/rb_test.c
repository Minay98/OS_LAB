#include <stdio.h>
#include <stdlib.h>
#include "rb.h"
#include "rb_data.h"
#include "minunit.h"

int tests_run = 0;

static const char *test_insert_and_minimal(void) {
    rbtree *t = rb_create(compare_func, destroy_func);
    if (!t) return "rb_create failed";

    int keys[] = { 15, 3, 9, 20, 1 };
    for (int i = 0; i < 5; i++) {
        mydata *d = makedata_with_object(keys[i], NULL);
        if (!d) return "makedata_with_object failed";
        rb_insert(t, d);
    }

    rbnode *min = RB_MINIMAL(t);
    MU_ASSERT("RB_MINIMAL returned NULL", min != NULL);
    mydata *md = (mydata *)min->data;
    MU_ASSERT("Minimal key is not 1", md->key == 1);

    rb_destroy(t);
    return NULL;
}

static const char *all_tests(void) {
    MU_RUN_TEST(test_insert_and_minimal);
    return NULL;
}

int main(void) {
    const char *result = all_tests();
    if (result != NULL) {
        printf("TEST FAILED: %s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);
    return result != NULL;
}
