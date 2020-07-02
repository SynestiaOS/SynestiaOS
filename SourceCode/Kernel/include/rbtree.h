//
// Created by XingfengYang on 2020/6/30.
//

#ifndef __KERNEL_RBTREE_H__
#define __KERNEL_RBTREE_H__

#include <stdint.h>
#include <list.h>
#include <type.h>

typedef enum NodeColor {
    RED,
    BLACK,
} __attribute__((packed)) NodeColor;

typedef struct RBNode {
    struct TreeNode *left;
    struct TreeNode *right;
    NodeColor color;
}  __attribute__((packed)) RBNode;

void *rbtree_create(RBNode *root);

void rbtree_balance(RBNode *root, RBNode *node);

void rbtree_erase(RBNode *root, RBNode *node);

void rbtree_recolor(RBNode *root, RBNode *node);

void rbtree_rotate_left(RBNode *root, RBNode *node);

void rbtree_rotate_right(RBNode *root, RBNode *node);

RBNode *rbtree_get_min(RBNode *root);

#define  RBTreeInsert(root, node, type, member, valueMember) {  \
    uint32_t parentValue = getNode(root, type, member)->valueMember;    \
    uint32_t nodeValue = getNode(node, type, member)->valueMember;  \
    if (nodeValue >= parentValue) { \
        if (root->right != nullptr) {   \
            RBTreeInsert(root->right, node, type, member, valueMember); \
        } else {    \
            root->right = node; \
            rbtree_balance(root,node);  \
        }   \
    } else {    \
        if (root->left != nullptr) {    \
            RBTreeInsert(root->left, node, type, member, valueMember);  \
        }else{  \
            root->left = node;  \
            rbtree_balance(root,node);  \
        }   \
    }   \
}

#endif //__KERNEL_RBTREE_H__
