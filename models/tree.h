#include <stdio.h>

#ifndef TREE_H
#define TREE_H

#define LEFT 0
#define RIGHT 1

typedef struct TreeNode {
    void *data;
    TreeNode *left;
    TreeNode *right;
} TreeNode;

typedef struct Binary_tree {
    TreeNode *head;
} Tree;

void insert_node(TreeNode *node, void *data);
bool remove_node(TreeNode *node, void *data);

#endif // !TREE_H
