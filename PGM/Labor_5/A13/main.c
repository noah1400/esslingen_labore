/*
* Eingabe:
* 1 4 42 10
*/

/*
* Ausgabe:
* Summe: 57
* Durchschnitt: 14.250000
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(int argc, char *argv[]) {
    int arr[4];
    int sum = 0;
    for (int i = 0; i < 4; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }
    printf("Summe: %d \n", sum);
    printf("Durchschnitt: %f \n", (float)sum / 4);
    return 0;
}
