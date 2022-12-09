#include <stdio.h>
int main(int argc, char *argv[]) {
    int a = 0;
    int* pointer = &a;
    printf("Resultat: %p \n", pointer);
}
// Ausgabe:
// Resultat: 0x7ffeeb5b9cfc