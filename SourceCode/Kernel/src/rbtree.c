//
// Created by XingfengYang on 2020/6/30.
//
#include <list.h>
#include <rbtree.h>
#include <thread.h>

/**
 * 1. Node is red or black
 * 2. Root node is black
 * 3. All leaf nodes are nullptr and black
 * 4. The red node's children must be black, it means there can not have two connected red node from root to a leaf node
 * 5. All paths from any node to each of its leaves contain the same number of black nodes
 **/

RBNode *rbtree_default_get_min(RBTree *tree) {
  RBNode *tmp = tree->root;
  while (tmp->left != nullptr) {
    tmp = tmp->left;
  }
  return tmp;
}

RBNode *rbtree_default_get_max(RBTree *tree) {
  RBNode *tmp = tree->root;
  while (tmp->right != nullptr) {
    tmp = tmp->right;
  }
  return tmp;
}

RBNode *rbtree_insert(RBNode *node1, RBNode *node2) {
  Thread *node1Thread = getNode(node1, Thread, rbNode);
  Thread *node2Thread = getNode(node2, Thread, rbNode);

  if (node2Thread->runtimVirtualNs < node1Thread->runtimVirtualNs) {
    if (node1->left == nullptr) {
      node1->left = node2;
      node2->parent = node1;
      return node2;
    } else {
      return rbtree_insert(node1->left, node2);
    }
  } else {
    if (node1->right == nullptr) {
      node1->right = node2;
      node2->parent = node1;
      return node2;
    } else {
      return rbtree_insert(node1->right, node2);
    }
  }
}

RBNode *rbtree_default_insert(RBTree *tree, RBNode *node) {
  RBNode *root = tree->root;

  if (root == nullptr) {
    tree->root = node;
    return node;
  }
  return rbtree_insert(root, node);
}

RBNode *rbtree_default_remove(RBTree *tree, RBNode *node) {
  RBNode *root = tree->root;
  RBNode *left = node->left;
  RBNode *right = node->right;
  if (node == root) {
    tree->root = nullptr;
  } else {
    if (node->parent->left == node) {
      node->parent->left = nullptr;
    } else if (node->parent->right == node) {
      node->parent->right = nullptr;
    }
  }

  if (left != nullptr) {
    rbtree_default_insert(tree, left);
  }
  if (right != nullptr) {
    rbtree_default_insert(tree, right);
  }
  node->left = nullptr;
  node->right = nullptr;
}

RBTree *rb_tree_init(RBTree *tree) {
  tree->operations.getMax = rbtree_default_get_max;
  tree->operations.getMin = rbtree_default_get_min;
  tree->operations.insert = rbtree_default_insert;
  tree->operations.remove = rbtree_default_remove;
}
