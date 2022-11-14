#include <stdio.h>
int main() {
        int i = 0, sum = 0;
        while (i > 3) {
            sum = sum + i;
            ++i;
        }
        printf("Resultat: %d", sum);
        return 0;
}

// Das Programm gibt 0 aus, da die Bedingung i > 3 nie erfüllt ist.