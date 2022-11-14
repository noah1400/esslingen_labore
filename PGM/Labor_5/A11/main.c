#include <stdio.h>
int main() {
    int value = 42;
    int *pointer = &value;
    
    printf("%d\n", value);
    *pointer = 85;
    printf("%d\n", value);
    (*pointer)++;
    printf("%d\n", value);
    return 0;
}