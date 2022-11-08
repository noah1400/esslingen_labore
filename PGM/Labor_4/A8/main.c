/*
Eingabe
1 2 3 4 0
*/

/*
Ausgabe
Durchschnitt (N=4): 2.50
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
    int n = 0, sum = 0, input = 0;
    do {
        scanf("%d", &input);
        sum += input;
        n++;
    } while (input >= 1 && input <= 6);
    if (n > 1) {
        printf("Durchschnitt (N=%d): %.2f", n - 1, (float)sum / (n - 1));
    }else {
        printf("Durchschnitt (N=%d): %.2f", n - 1, (float)n - 1);
    }
    return 0;
}
