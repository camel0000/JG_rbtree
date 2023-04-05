#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

void inorderTraversalPrint(node_t *root) {
    if (root->left == NULL && root->right == NULL) return;

    inorderTraversalPrint(root->left);
    printf("%c %d %d\n", root->color == RBTREE_BLACK ? 'B' : 'R', root->key, root->parent->key);
    inorderTraversalPrint(root->right);
}

int main(int argc, char *argv[]) {

    rbtree *tree = new_rbtree();
    node_t *t = rbtree_insert(tree, 10);
    t = rbtree_insert(tree, 5);
    t = rbtree_insert(tree, 8);
    t = rbtree_insert(tree, 34);
    t = rbtree_insert(tree, 67);
    t = rbtree_insert(tree, 23);
    t = rbtree_insert(tree, 156);
    t = rbtree_insert(tree, 24);
    t = rbtree_insert(tree, 2);
    t = rbtree_insert(tree, 12);
    t = rbtree_insert(tree, 24);
    t = rbtree_insert(tree, 36);
    t = rbtree_insert(tree, 990);
    t = rbtree_insert(tree, 25);

    inorderTraversalPrint(t);

    key_t *arr = (key_t *)calloc(14, sizeof(key_t));
    rbtree_to_array(tree, arr, 14);
    for (int i = 0; i < 14; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int x;
    x = rbtree_erase(tree, rbtree_find(tree, 10));
    x = rbtree_erase(tree, rbtree_find(tree, 5));
    x = rbtree_erase(tree, rbtree_find(tree, 8));
    // x = rbtree_erase(tree, rbtree_find(tree, 34));
    // x = rbtree_erase(tree, rbtree_find(tree, 67));
    // x = rbtree_erase(tree, rbtree_find(tree, 23));
    // x = rbtree_erase(tree, rbtree_find(tree, 156));
    // x = rbtree_erase(tree, rbtree_find(tree, 24));
    // x = rbtree_erase(tree, rbtree_find(tree, 2));
    // x = rbtree_erase(tree, rbtree_find(tree, 12));
    // x = rbtree_erase(tree, rbtree_find(tree, 24));
    // x = rbtree_erase(tree, rbtree_find(tree, 36));
    // x = rbtree_erase(tree, rbtree_find(tree, 990));
    // x = rbtree_erase(tree, rbtree_find(tree, 25));

    inorderTraversalPrint(t);


    return 0;
}

// 10, 5, 8, 34, 67, 23, 156, 24, 2, 12, 24, 36, 990, 25