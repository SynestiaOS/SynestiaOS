//
// Created by XingfengYang on 2020/6/30.
//

#ifndef __KERNEL_RBTREE_H__
#define __KERNEL_RBTREE_H__

#include <stdint.h>

typedef enum NodeColor {
    RED,
    BLACK,
} __attribute__((packed)) NodeColor;

typedef struct RBTreeNode {
    struct TreeNode *left;
    struct TreeNode *right;
    NodeColor color;
}  __attribute__((packed)) RBTreeNode;


void *rbtree_create(RBTreeNode *root);

void rbtree_instert(RBTreeNode *root, RBTreeNode *node);

void rbtree_erase(RBTreeNode *root, RBTreeNode *node);

RBTreeNode *rbtree_get_min(RBTreeNode *root);

#endif //__KERNEL_RBTREE_H__
