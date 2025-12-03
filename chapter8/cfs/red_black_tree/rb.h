#ifndef RB_H
#define RB_H

#include <stddef.h>

/* Simple (unbalanced) binary search tree API with a red-black like interface.
 * For purposes of the lab, balancing is not necessary; we only rely on:
 *  - rb_create
 *  - rb_insert
 *  - rb_delete
 *  - RB_MINIMAL (left-most node)
 */

typedef struct rbnode {
    int color;                 /* unused in this simple implementation */
    struct rbnode *left;
    struct rbnode *right;
    struct rbnode *parent;
    void *data;                /* user data (here: struct mydata*) */
} rbnode;

typedef struct rbtree {
    rbnode *root;
    int (*cmp)(const void *a, const void *b);   /* compare function on node->data */
    void (*destroy)(void *data);               /* destroy function for node->data */
} rbtree;

/* Create / destroy tree */
rbtree *rb_create(int (*cmp)(const void*, const void*),
                  void (*destroy)(void*));
void rb_destroy(rbtree *tree);

/* Insert a new data element into tree. Returns created node or NULL on error. */
rbnode *rb_insert(rbtree *tree, void *data);

/* Delete a node from tree (does NOT free node->data, that is done via destroy). */
void rb_delete(rbtree *tree, rbnode *node);

/* Helper: minimum node starting from given node. */
rbnode *rb_minimum_node(rbnode *node);

/* Macro used in the lab text: returns the left-most (minimal key) node. */
#define RB_MINIMAL(tree) rb_minimum_node((tree)->root)

#endif /* RB_H */
