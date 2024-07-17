#include <stdio.h>
#include <stdlib.h>

// ��ǥ ����ü ����
typedef struct {
    int value; // ���� ��ǥ ��
    int index; // ���� ��ǥ�� �ε���
} Coordinate;

// �� �Լ�: qsort�� ���� ���
int compare(const void *a, const void *b) {
    return ((Coordinate*)a)->value - ((Coordinate*)b)->value;
}

int main() {
    int n;
    scanf("%d", &n);

    Coordinate *coords = (Coordinate*)malloc(n * sizeof(Coordinate));
    int *result = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &coords[i].value);
        coords[i].index = i; // ���� �ε����� ����
    }

    // ��ǥ�� �� �������� ����
    qsort(coords, n, sizeof(Coordinate), compare);

    // ����� ��ǥ�� ���
    int rank = 0;
    result[coords[0].index] = rank;
    for (int i = 1; i < n; i++) {
        if (coords[i].value != coords[i - 1].value) {
            rank++;
        }
        result[coords[i].index] = rank;
    }

    // ���� ������� ��� ���
    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(coords);
    free(result);

    return 0;
}
