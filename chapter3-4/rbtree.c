#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/rbtree.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Operating Systems Lab Team");
MODULE_DESCRIPTION("Example of Red-Black Tree in Linux Kernel Module");

struct my_node {
    int key;
    struct rb_node node;
};

static struct rb_root my_tree = RB_ROOT;

static int insert(struct rb_root *root, struct my_node *data) {
    struct rb_node **new = &(root->rb_node), *parent = NULL;

    while (*new) {
        struct my_node *this = container_of(*new, struct my_node, node);

        parent = *new;
        if (data->key < this->key)
            new = &((*new)->rb_left);
        else if (data->key > this->key)
            new = &((*new)->rb_right);
        else
            return -1; 
    }

    rb_link_node(&data->node, parent, new);
    rb_insert_color(&data->node, root);

    return 0;
}

static void traverse(struct rb_root *root) {
    struct rb_node *node;
    for (node = rb_first(root); node; node = rb_next(node)) {
        struct my_node *data = container_of(node, struct my_node, node);
        pr_info("key available: %d\n", data->key);
    }
}

static void free_tree(struct rb_root *root) {
    struct rb_node *node;
    struct my_node *data;

    while ((node = rb_first(root))) {
        data = container_of(node, struct my_node, node);
        pr_info("key deleted: %d\n", data->key);
        rb_erase(&data->node, root);
        kfree(data);
    }
}

static int __init rbtree_example_init(void) {
    struct my_node *node;
    int keys[] = {10, 20, 15, 30, 25, 5};
    int i;

    pr_info("Initializing Red-Black Tree Module\n");

    for (i = 0; i < sizeof(keys)/sizeof(keys[0]); i++) {
        node = kmalloc(sizeof(struct my_node), GFP_KERNEL);
        if (!node)
            return -ENOMEM;
        
        node->key = keys[i];
        if (insert(&my_tree, node) != 0) {
            pr_warn("Duplicate key: %d\n", node->key);
            kfree(node);
        }
    }

    pr_info("Traversing the tree:\n");
    traverse(&my_tree);

    return 0;
}

static void __exit rbtree_example_exit(void) {
    pr_info("Cleaning up Red-Black Tree Module\n");

    free_tree(&my_tree);
}

module_init(rbtree_example_init);
module_exit(rbtree_example_exit);
