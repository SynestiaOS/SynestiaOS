//
// Created by XingfengYang on 2020/6/30.
//

#include <rbtree.h>
#include <kheap.h>
#include <thread.h>


void *rbtree_create(RBNode *root) {
    root = kheap_alloc(sizeof(RBNode));
    root->color = BLACK;
    root->left = nullptr;
    root->right = nullptr;
}

void rbtree_instert(RBNode *root, RBNode *node) {
    RBNode *left = root->left;
}

void rbtree_insert_with_val(RBNode *root, RBNode *node, uint32_t parentValue, uint32_t nodeValue) {
    RBNode *left = root->left;
}

void rbtree_erase(RBNode *root, RBNode *node) {

}

void rbtree_rotate_left(RBNode *root, RBNode *node) {

}

void rbtree_rotate_right(RBNode *root, RBNode *node) {

}

RBNode *rbtree_get_min(RBNode *root) {

}
