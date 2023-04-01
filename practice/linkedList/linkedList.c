#include <stdio.h>
#include <stdlib.h>

// Singly linked List

// makeNode : 노드 생성 ADT -> ok
// appendNode : 리스트 끝에 노드를 붙이는 ADT -> ok
// unshiftNode : 리스트 앞에 노드를 붙이는 ADT -> ok
// popNode : 리스트 맨 뒤 노드를 빼서 반환하는 ADT -> ok
// shiftNode : 리스트 맨 앞 노드를 빼서 반환하는 ADT -> ok
// insertByIndex : 특정 index 바로 뒤에 노드를 붙이는 ADT -> ok
// removeByIndex : 특정 index의 노드를 빼서 반환하는 ADT -> ok
// printList : 리스트 전체를 출력하는 ADT -> ok
// deleteList : 해당 리스트를 삭제하는 ADT

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *makeNode(int newData) {       // 완료
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = NULL;
    return newNode;
}
void appendNode(Node *header, int newData){     // 완료
    Node *p;
    Node *newNode = makeNode(newData);
    
    if (header->next == NULL) {
        header->next = newNode;
    }
    else {
        for (p = header; p->next; p = p->next) { }
        p->next = newNode;
    }    
}
void unshiftNode(Node *header, int newData) {       // 완료
    Node *newNode = makeNode(newData);

    newNode->next = header->next;
    header->next = newNode;
}
int popNode(Node *header) {     // 완료
    Node *p = header;

    if (header->next == NULL) return -1;

    for (p = header->next; p->next->next; p = p->next) { }
    
    int rt = p->next->data;
    free(p->next);
    p->next = NULL;
    return rt;
}
int shiftNode(Node *header) {    // 완료
    Node *p = header->next;

    if (p == NULL) return -1;

    int rt = header->next->data;
    header->next = p->next;
    free(p);
    return rt;
}
void insertByIndex(Node *header, int insertIdx, int newData){   // 완료
    Node *p = header;
    Node *newNode = makeNode(newData);
    
    for (int i = 0; i < insertIdx; i++) { p = p->next; }
    newNode->next = p->next;
    p->next = newNode;
}
int removeByIndex(Node *header, int removeIdx) {    // 완료
    Node *p = header;

    for (int i = 0; i < removeIdx - 1; i++) { p = p->next; }

    int rt = p->next->next->data;
    Node *q = p->next;
    p->next = p->next->next;
    free(q);
    return rt;
}
void printList(Node *header) {      // 완료
    Node *p = header;
    if (p->next == NULL) {
        printf("None!\n");
        return;
    }

    for (p = header->next; p; p = p->next) { printf("%d ", p->data); };
    printf("\n");
}


// 이중 반복?
void deleteList(Node *header) {
    Node *p = header;

    for (p = header; p !)
    
}

int main(void) {
    Node *header = makeNode(0);

    printList(header);  // None!

    appendNode(header, 3);
    appendNode(header, 2);
    appendNode(header, 8);
    printList(header);  // 3 2 8

    unshiftNode(header, 6);
    unshiftNode(header, 11);
    printList(header);  // 11 6 3 2 8

    printf("shifted %d\n", shiftNode(header));  // 11 삭제
    printList(header);  // 6 3 2 8

    printf("popped %d\n", popNode(header));     // 8 삭제
    printf("popped %d\n", popNode(header));     // 2 삭제
    printList(header);  // 6 3

    insertByIndex(header, 1, 20);
    insertByIndex(header, 0, 15);
    insertByIndex(header, 0, 50);
    printList(header);  // 50 15 6 20 3

    printf("removed %d\n", removeByIndex(header, 1));   // 50 삭제
    printf("removed %d\n", removeByIndex(header, 2));   // 6 삭제
    printList(header);  // 15 20 3

    deleteList(header);
    printList(header);  // None!

    return 0;
}