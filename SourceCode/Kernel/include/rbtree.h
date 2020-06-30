//
// Created by XingfengYang on 2020/6/30.
//

#ifndef __KERNEL_RBTREE_H__
#define __KERNEL_RBTREE_H__

typedef enum NodeColor {
    RED,
    BLACK,
} __attribute__((packed)) NodeColor;

typedef struct TreeNode {
    struct TreeNode *left;
    struct TreeNode *right;
    void *value;
}  __attribute__((packed)) TreeNode;


TreeNode *rbtree_create();

void rbtree_inster(TreeNode *root, TreeNode *node);

TreeNode *rbtree_get_min(TreeNode *root);

#endif //__KERNEL_RBTREE_H__
