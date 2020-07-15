//
// Created by XingfengYang on 2020/6/30.
//

#ifndef __KERNEL_RBTREE_H__
#define __KERNEL_RBTREE_H__

#include <list.h>
#include <stdint.h>
#include <type.h>

typedef enum NodeColor {
  RED,
  BLACK,
} __attribute__((packed)) NodeColor;

typedef struct RBNode {
  struct RBNode *left;
  struct RBNode *right;
  NodeColor color;
} __attribute__((packed)) RBNode;

void *rbtree_create(RBNode *root);

void rbtree_balance(RBNode *root, RBNode *node);

void rbtree_erase(RBNode *root, RBNode *node);

void rbtree_recolor(RBNode *root, RBNode *node);

void rbtree_rotate_left(RBNode *root, RBNode *node);

void rbtree_rotate_right(RBNode *root, RBNode *node);

RBNode *rbtree_get_min(RBNode *root);

#endif //__KERNEL_RBTREE_H__
