#include <stdio.h>
#include <stdlib.h>

// ���� ��ũ�� ����Ʈ�� ��� ����ü ����
typedef struct Node {
    struct Node *before;
    int data;
    struct Node *after;
} Node;

int main() {
    // �� ��带 �����ϰ� �����͸� �Ҵ�
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

    // �� ����� before�� after ������ ����
    node1->after = node2;
    node2->after = node3;

    // �޸� ����
    free(node1);
    free(node2);
    free(node3);

    return 0;
}
