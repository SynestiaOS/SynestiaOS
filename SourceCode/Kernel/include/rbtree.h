//
// Created by XingfengYang on 2020/6/30.
//

#ifndef __KERNEL_RBTREE_H__
#define __KERNEL_RBTREE_H__

#include <kvector.h>
#include <list.h>
#include <stdint.h>
#include <type.h>

typedef enum NodeColor {
  NODE_RED,
  NODE_BLACK,
} __attribute__((packed)) NodeColor;

typedef struct RBNode {
  struct RBNode *parent;
  struct RBNode *left;
  struct RBNode *right;
  NodeColor color;
} __attribute__((packed)) RBNode;

RBNode *rbtree_get_root(RBNode *node);

void rbtree_rebalance(RBNode *root, RBNode *node);

void rbtree_reconstruct_to_list_recursion(KernelVector *vector, RBNode *root);

void rbtree_reconstruct_to_list(KernelVector *vector, RBNode *root);

KernelStatus rbtree_remove(RBNode *root, RBNode *node);

void rbtree_remove_rebalance(RBNode *root, RBNode *node);

void rbtree_rotate_left(RBNode *root, RBNode *node);

void rbtree_rotate_right(RBNode *root, RBNode *node);

RBNode *rbtree_get_min(RBNode *root);

RBNode *rbtree_get_max(RBNode *root);

#endif //__KERNEL_RBTREE_H__
