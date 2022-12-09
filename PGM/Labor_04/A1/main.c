/*
Eingabe
4.12 2 6 5
*/

/*
Ausgabe
Kleinste Zahl: 2.0 an Index 1
*/
#include <stdio.h>

int main(int argc, char *argv[]) {
    int i, index;
    float x, min;
    scanf("%f", &min);
    index = 0;
    for (i = 1; i < 4; i++) {
        scanf("%f", &x);
        if (x < min) {
            min = x;
            index = i;
        }
    }
    printf("Kleinste Zahl: %.1f an Index %d", min, index);
    return 0;
}
