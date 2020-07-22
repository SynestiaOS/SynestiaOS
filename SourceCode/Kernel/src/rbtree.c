//
// Created by XingfengYang on 2020/6/30.
//
#include <kheap.h>
#include <log.h>
#include <rbtree.h>

/**
 * 1. Node is red or black
 * 2. Root node is black
 * 3. All leaf nodes are nullptr and black
 * 4. The red node's children must be black, it means there can not have two connected red node from root to a leaf node
 * 5. All paths from any node to each of its leaves contain the same number of black nodes
 **/

RBNode* rbtree_get_root(RBNode *node){
  RBNode* tmp = node;
  while(tmp->parent!=nullptr){
    tmp = tmp->parent;
  }
  return tmp;
}

void rbtree_rebalance(RBNode *root, RBNode *node) {
  LogWarnning("[CSF] rebalance.\n");
  RBNode *newNodeParent = node->parent;
  if (newNodeParent != nullptr && newNodeParent->color != NODE_BLACK) {
    RBNode *pnode = node;
    while ((root != pnode) && (pnode->parent != nullptr) && pnode->parent->color == NODE_RED) {
      RBNode *parent = pnode->parent;
      RBNode *grandparent = pnode->parent->parent;
      RBNode *uncle = nullptr;
      int uncle_is_left;

      if (pnode->color != NODE_RED) {
        // todo: error
        LogError("[RBTree]: unexpected node color.\n");
      }

      if (parent == grandparent->left) {
        uncle_is_left = 0;
        uncle = grandparent->right;
      } else {
        uncle_is_left = 1;
        uncle = grandparent->left;
      }

      /* Case 1: Uncle is not black */
      if (uncle && uncle->color == NODE_RED) {
        /* Color parent and uncle black */
        parent->color = NODE_BLACK;
        uncle->color = NODE_BLACK;

        /* Color Grandparent as Red */
        grandparent->color = NODE_RED;
        pnode = grandparent;
        /* Continue iteration, processing grandparent */
      } else {
        /* Case 2 - node's parent is red, but uncle is black */
        if (!uncle_is_left && parent->right == pnode) {
          pnode = pnode->parent;
          rbtree_rotate_left(root, pnode);
        } else if (uncle_is_left && parent->left == pnode) {
          pnode = pnode->parent;
          rbtree_rotate_right(root, pnode);
        }

        /* Case 3 - Recolor and rotate*/
        parent = pnode->parent;
        parent->color = NODE_BLACK;

        grandparent = pnode->parent->parent;
        grandparent->color = NODE_RED;
        if (!uncle_is_left) {
          rbtree_rotate_right(root, grandparent);
        } else {
          rbtree_rotate_left(root, grandparent);
        }
      }
    }

    /* Make sure the tree root is black (Case 1: Continued) */
    RBNode *treeRoot = root;
    treeRoot->color = NODE_BLACK;
  }
}

void rbtree_erase(RBNode *root, RBNode *node) {}

void rbtree_recolor(RBNode *root, RBNode *node) {}

void rbtree_rotate_left(RBNode *root, RBNode *node) {
  RBNode *x = node;
  RBNode *y = x->right;

  x->right = y->left;

  if (y->left != nullptr) {
    RBNode *yleft = y->left;
    yleft->parent = x;
  }

  y->parent = x->parent;

  if (x->parent == nullptr) {
    root = y;
  } else {
    RBNode *xp = x->parent;
    if (x == xp->left) {
      xp->left = y;
    } else {
      xp->right = y;
    }
  }

  y->left = x;
  x->parent = y;
}

void rbtree_rotate_right(RBNode *root, RBNode *node) {
  RBNode *x = node;
  RBNode *y = x->left;

  x->left = y->right;

  if (y->right != nullptr) {
    RBNode *yright = y->right;
    yright->parent = x;
  }

  y->parent = x->parent;

  if (x->parent == nullptr) {
    root = y;
  } else {
    RBNode *xp = x->parent;
    if (x == xp->left) {
      xp->left = y;
    } else {
      xp->right = y;
    }
  }

  y->right = x;
  x->parent = y;
}

RBNode *rbtree_get_min(RBNode *root) {
  RBNode *tmp = root;
  while (tmp->left != nullptr) {
    tmp = tmp->left;
  }
  return tmp;
}
