#include <stdio.h>
#include <stdlib.h>

// 더블 링크드 리스트의 노드 구조체 정의
typedef struct Node {
    struct Node *before;
    int data;
    struct Node *after;
} Node;

int main() {
    // 각 노드를 생성하고 데이터를 할당
    Node *node1 = (Node*)malloc(sizeof(Node));
    node1->before = NULL;
    node1->data = 1;
    node1->after = NULL;

    Node *node2 = (Node*)malloc(sizeof(Node));
    node2->before = node1;
    node2->data = 2;
    node2->after = NULL;

    Node *node3 = (Node*)malloc(sizeof(Node));
    node3->before = node2;
    node3->data = 3;
    node3->after = NULL;

    // 각 노드의 before과 after 포인터 설정
    node1->after = node2;
    node2->after = node3;

    // 메모리 해제
    free(node1);
    free(node2);
    free(node3);

    return 0;
}
