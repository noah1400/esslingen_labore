#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(int argc, char *argv[]) {
    int arr[4];
    for (int i = 0; i < 4; i++) {
        scanf("%d", &arr[i]);
    }
    int *ptr = &arr[2];
    for (int i = 0; i < 4; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    *ptr = 42;
    for (int i = 0; i < 4; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}
