#include <stdio.h>
#include <stdlib.h>

#ifndef TREE_H
#define TREE_H

#define LEFT 0
#define RIGHT 1

typedef struct TreeNode {
    void *data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct Binary_tree {
    TreeNode *head;
} Tree;

TreeNode *create_tree_node(void *data) {
    TreeNode *tmp = malloc(sizeof *tmp);
    tmp->data = data;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

void insert_node(TreeNode *node, void *data) {
    TreeNode *tmp = create_tree_node(data);
    if (!node->left) {
        node->left = tmp;
    } else if (node->right) {
    }
}

#endif // !TREE_H
