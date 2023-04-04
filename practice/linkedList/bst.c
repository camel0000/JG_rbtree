#include <stdio.h>
#include <stdlib.h>

// Binary Search Tree

// makeNode : 새 노드 생성
// insertNode : 새 노드를 삽입
// searchNode : 노드 탐색, 찾을 값 반환
// deleteNode : 노드 삭제
// inTraversal : 트리 중위 순회 출력

typedef struct Node {
    int key;
    struct Node *lChild, *rChild, *parent;
} Node;

Node *makeNode(int key){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->lChild = newNode->rChild = newNode->parent = NULL;
    newNode->key = key;
    return newNode;
}
Node *treeSearch(Node *root, int key) {
    Node *t = root;
    if (t->lChild == NULL && t->rChild == NULL) return t;

    if (key == t->key) return t;
    if (key < t->key) return treeSearch(t->lChild, key);
    else return treeSearch(t->rChild, key);
}
void insertNode(Node *root, int key) {
    // searching location of inserting node
    Node *t = treeSearch(root, key);

    Node *lChildNode = (Node *)malloc(sizeof(Node));
    Node *rChildNode = (Node *)malloc(sizeof(Node));
    
    t->key = key;
    t->lChild = lChildNode;
    t->rChild = rChildNode;

    // making child nodes
    lChildNode->parent = rChildNode->parent = t;
    lChildNode->lChild = rChildNode->rChild = NULL;
    lChildNode->rChild = rChildNode->lChild = NULL;
}
int deleteNode(Node *root, int key) {
    // searching location of deleting node
    Node *t = treeSearch(root, key);
    
    // 
    if (t->lChild == NULL && t->rChild == NULL) return -1;

    int elem = t->key;

    Node *tmp = t->lChild;
    if (tmp->lChild != NULL && tmp->rChild != NULL) tmp = t->rChild;

    if (tmp->lChild == NULL && tmp->rChild == NULL) {
        // reduceExternal(t, tmp);
    }
    else {
        Node *suc = t;
        suc = suc->rChild;

        // if (suc->lChild == NULL && suc->rChild == NULL) return;
        while (!(suc->lChild == NULL && suc->rChild == NULL)) suc = suc->lChild;
        tmp = suc->lChild;
        t->key = suc->key;
        // reduceExternal(t, tmp);
    }
}
void inorderTraversalPrint(Node *root) {
    if (root->lChild == NULL && root->rChild == NULL) return;

    inorderTraversalPrint(root->lChild);
    printf("%d ", root->key);
    inorderTraversalPrint(root->rChild);
}


int main(void) {
    Node *root = makeNode(0);
    int tmp_del;

    insertNode(root, 30);
    insertNode(root, 20);
    insertNode(root, 60);
    insertNode(root, 100);
    insertNode(root, 70);
    insertNode(root, 5);
    insertNode(root, 15);
    insertNode(root, 25);
    insertNode(root, 40);
    insertNode(root, 45);
    inorderTraversalPrint(root);    // 20 30 60
    printf("\n");

    tmp_del = deleteNode(root, 20);
    if (tmp_del == -1) printf("Nothing deleted!\n");
    else printf("deleted %d\n", tmp_del);


    return 0;
}