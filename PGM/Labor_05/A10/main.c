#include <stdio.h>
int main(int argc, char *argv[]) {
    int a = 0;
    int* pointer = a;
    printf("Resultat: %d \n", *pointer);
}
// Ausgabe:
// Resultat: 
// Programm startet nicht oder stürzt ab