//
// Created by XingfengYang on 2020/6/30.
//

#include <rbtree.h>
#include <kheap.h>


void *rbtree_create(RBTreeNode *root) {
    root = kheap_alloc(sizeof(RBTreeNode));
    root->color = BLACK;
    root->left = nullptr;
    root->right = nullptr;
}

void rbtree_instert(RBTreeNode *root, RBTreeNode *node) {

}

void rbtree_erase(RBTreeNode *root, RBTreeNode *node){

}

RBTreeNode *rbtree_get_min(RBTreeNode *root) {

}
