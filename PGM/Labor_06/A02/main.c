#include <stdio.h>

int add(int a, int b) {
    int c = a + b;
    return c;
}
int main() {
    printf("Resultat: %d\n", add(19, 2.8));
    return 0;
}

// Outputs: Resultat: 21