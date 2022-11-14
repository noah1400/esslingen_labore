#include <stdio.h>
int main(int argc, char *argv[]) {
    int a = 0;
    int pointer* = &a; // Pointer stern an der falschen Stelle!
    printf("Resultat: %p \n", pointer);
}
// Ausgabe: Syntaxfehler
