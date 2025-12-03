#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

/* Internal helper to create a node */
static rbnode *rbnode_create(void *data) {
    rbnode *n = (rbnode *)malloc(sizeof(rbnode));
    if (!n) return NULL;
    n->color = 0;
    n->left = n->right = n->parent = NULL;
    n->data = data;
    return n;
}

/* Recursively destroy nodes */
static void rb_destroy_nodes(rbtree *tree, rbnode *node) {
    if (!node) return;
    rb_destroy_nodes(tree, node->left);
    rb_destroy_nodes(tree, node->right);
    if (tree->destroy) {
        tree->destroy(node->data);
    }
    free(node);
}

rbtree *rb_create(int (*cmp)(const void*, const void*),
                  void (*destroy)(void*)) {
    rbtree *t = (rbtree *)malloc(sizeof(rbtree));
    if (!t) return NULL;
    t->root = NULL;
    t->cmp = cmp;
    t->destroy = destroy;
    return t;
}

void rb_destroy(rbtree *tree) {
    if (!tree) return;
    rb_destroy_nodes(tree, tree->root);
    free(tree);
}

/* Simple BST insert using tree->cmp on node->data */
rbnode *rb_insert(rbtree *tree, void *data) {
    if (!tree) return NULL;

    rbnode *new_node = rbnode_create(data);
    if (!new_node) return NULL;

    if (!tree->root) {
        tree->root = new_node;
        return new_node;
    }

    rbnode *cur = tree->root;
    rbnode *parent = NULL;
    int cmp_res = 0;

    while (cur) {
        parent = cur;
        cmp_res = tree->cmp(data, cur->data);
        if (cmp_res < 0) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    new_node->parent = parent;
    if (cmp_res < 0) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }

    /* NOTE: no balancing; this is a plain BST. */
    return new_node;
}

/* Helper: transplant subtree v in place of u */
static void rb_transplant(rbtree *tree, rbnode *u, rbnode *v) {
    if (!u->parent) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v) {
        v->parent = u->parent;
    }
}

rbnode *rb_minimum_node(rbnode *node) {
    if (!node) return NULL;
    while (node->left) node = node->left;
    return node;
}

/* Simple BST delete */
void rb_delete(rbtree *tree, rbnode *node) {
    if (!tree || !node) return;

    if (!node->left) {
        rb_transplant(tree, node, node->right);
    } else if (!node->right) {
        rb_transplant(tree, node, node->left);
    } else {
        rbnode *y = rb_minimum_node(node->right);
        if (y->parent != node) {
            rb_transplant(tree, y, y->right);
            y->right = node->right;
            if (y->right) y->right->parent = y;
        }
        rb_transplant(tree, node, y);
        y->left = node->left;
        if (y->left) y->left->parent = y;
    }

    /* data is freed when tree is destroyed; do not free node->data here */
    free(node);
}
