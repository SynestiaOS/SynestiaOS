//
// Created by XingfengYang on 2020/6/30.
//
#include <kheap.h>
#include <rbtree.h>
#include <log.h>

/**
 * 1. Node is red or black
 * 2. Root node is black
 * 3. All leaf nodes are nullptr and black
 * 4. The red node's children must be black, it means there can not have two connected red node from root to a leaf node
 * 5. All paths from any node to each of its leaves contain the same number of black nodes
 **/
void rbtree_balance(RBNode *root, RBNode *node) {
  LogWarnning("[CSF] balance.\n");
}

void rbtree_erase(RBNode *root, RBNode *node) {}

void rbtree_recolor(RBNode *root, RBNode *node) {}

void rbtree_rotate_left(RBNode *root, RBNode *node) {}

void rbtree_rotate_right(RBNode *root, RBNode *node) {}

RBNode *rbtree_get_min(RBNode *root) {}
