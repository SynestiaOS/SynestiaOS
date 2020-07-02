//
// Created by XingfengYang on 2020/6/30.
//

#ifndef __KERNEL_RBTREE_H__
#define __KERNEL_RBTREE_H__

#include <stdint.h>

/**
 * get node's member value by rbnode
 */
#define getNodeValue(ptr, type, member, valueMember)(uint32_t)(((type *)((char *)(ptr) - (char *)(&(((type *)0)->member))))->valueMember)

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

void rbtree_instert(RBNode *root, RBNode *node);

void rbtree_insert_with_val(RBNode *root, RBNode *node, uint32_t parentValue, uint32_t nodeValue);

#define rbtreeInsert(root, node, type, member, valueMember) {   \
    uint32_t parentValue = getNodeValue(root,type,rbTree,runtimeNs);    \
    uint32_t nodeValue = getNodeValue(node,type,rbTree,runtimeNs);    \
    rbtree_insert_with_val(root,node,parentValue,nodeValue);   \
    }

void rbtree_erase(RBNode *root, RBNode *node);

void rbtree_rotate_left(RBNode *root, RBNode *node);

void rbtree_rotate_right(RBNode *root, RBNode *node);

RBNode *rbtree_get_min(RBNode *root);

#endif //__KERNEL_RBTREE_H__
