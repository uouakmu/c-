#include <stdio.h>
#include <stdlib.h>

// 좌표 구조체 정의
typedef struct {
    int value; // 원래 좌표 값
    int index; // 원래 좌표의 인덱스
} Coordinate;

// 비교 함수: qsort를 위해 사용
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
        coords[i].index = i; // 원래 인덱스를 저장
    }

    // 좌표를 값 기준으로 정렬
    qsort(coords, n, sizeof(Coordinate), compare);

    // 압축된 좌표를 계산
    int rank = 0;
    result[coords[0].index] = rank;
    for (int i = 1; i < n; i++) {
        if (coords[i].value != coords[i - 1].value) {
            rank++;
        }
        result[coords[i].index] = rank;
    }

    // 원래 순서대로 결과 출력
    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(coords);
    free(result);

    return 0;
}
