#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare (const void *a, const void *b) {
    return (*(char*)b - *(char*)a);

}
    
int main() {
    char num[11];
    scanf("%s",num);

    qsort(num,strlen(num),sizeof(char),compare);
    printf("%s\n",num);

    return 0;
}