#include <stdio.h>

int add(int a, int s) {
    if (a) s = add(a - 1, s);
    return s + a;
}

int main() {
    printf("Resultat: %d", add(4, 0));
    return 0;
}

// Outputs: Resultat: 10