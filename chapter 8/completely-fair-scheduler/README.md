
# Completely Fair Scheduler using Red-black Tree Implementation In C

## Completely Fair Scheduler
CFS stands for “Completely Fair Scheduler,” and is the new “desktop” process scheduler implemented by Ingo Molnar and merged in Linux 2.6.23. It is the replacement for the previous vanilla scheduler’s SCHED_OTHER interactivity code.
80% of CFS’s design can be summed up in a single sentence: CFS basically models an “ideal, precise multi-tasking CPU” on real hardware.
“Ideal multi-tasking CPU” is a (non-existent :-)) CPU that has 100% physical power and which can run each task at precise equal speed, in parallel, each at 1/nr_running speed. For example: if there are 2 tasks running, then it runs each at 50% physical power --- i.e., actually in parallel.

## Implementation of Red-black Tree

There are several choices when implementing red-black trees:
- store parent reference or not
- recursive or non-recursive (iterative)
- do top-down splits or bottom-up splits (only when needed)
- do top-down fusion or top-bottom fusion (only when needed)

This implementation's choice:
- store parent reference
- non-recursive (iterative)
- do bottom-up splits (only when needed)
- do top-bottom fusion (only when needed)

Files
* rb.h - red-black tree header
* rb.c - red-black tree library
* rb_data.h - data header
* rb_data.c - data library
* rb_example.c - example code for red-black tree application
* rb_test.c - unit test program
* rb_test.sh - unit test shell script
* README.md - implementation note

## DEFINITION of Red-black Tree

A red-black tree is a binary search tree where each node has a color attribute, the value of which is either red or black. Essentially, it is just a convenient way to express a 2-3-4 binary search tree where the color indicates whether the node is part of a 3-node or a 4-node. 2-3-4 trees and red-black trees are equivalent data structures, red-black trees are simpler to implement, so tend to be used instead.

Binary search property or order property: the key in each node must be greater than or equal to any key stored in the left sub-tree, and less than or equal to any key stored in the right sub-tree.

In addition to the ordinary requirements imposed on binary search trees, we make the following additional requirements of any valid red-black tree.

Red-black properties:
1. Every node is either red or black.
2. The root and leaves (NIL's) are black.
3. Parent of each red node is black.
4. Both children of each red node are black.
5. Every path from a given node to any of its descendant NIL nodes contains the same number of black nodes.

## INSERTION

**Insertion into a red-black tree**

Insert as in simple binary search tree

- 0-children root cluster (parent node is BLACK) becomes 2-children root cluster: paint root node BLACK, and done
- 2-children cluster (parent node is BLACK) becomes 3-children cluster: done
- 3-children cluster (parent node is BLACK) becomes 4-children cluster: done
- 3-children cluster (parent node is RED) becomes 4-children cluster: rotate, and done
- 4-children cluster (parent node is RED) splits into 2-children cluster and 3-children cluster: split, and insert grandparent node into parent cluster

## DELETION

**Deletion from red-black tree**

Delete as in simple binary search tree

- 4-children cluster (RED target node) becomes 3-children cluster: done
- 3-children cluster (RED target node) becomes 2-children cluster: done
- 3-children cluster (BLACK target node, RED child node) becomes 2-children cluster: paint child node BLACK, and done
- 2-children root cluster (BLACK target node, BLACK child node) becomes 0-children root cluster: done
- 2-children cluster (BLACK target node, 4-children sibling cluster) becomes 3-children cluster: transfer, and done
- 2-children cluster (BLACK target node, 3-children sibling cluster) becomes 2-children cluster: transfer, and done
- 2-children cluster (BLACK target node, 2-children sibling cluster, 3/4-children parent cluster) becomes 3-children cluster: fuse, paint parent node BLACK, and done
- 2-children cluster (BLACK target node, 2-children sibling cluster, 2-children parent cluster) becomes 3-children cluster: fuse, and delete parent node from parent cluster

## References

1. [https://en.wikipedia.org/wiki/Red-black_tree](https://en.wikipedia.org/wiki/Red-black_tree)
2. [https://www.cs.usfca.edu/~galles/visualization/RedBlack.html](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html)

## License

Copyright (c) 2019 xieqing. https://github.com/xieqing

May be freely redistributed, but copyright notice must be retained.
