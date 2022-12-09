/*
Eingabe
Programmieren
*/

/*
Ausgabe
nereimmargorP
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
    char str[40];
    int len = 0;
    scanf("%s", str);
    for (int i = 0; str[i] != '\0'; i++) {
        len++;
    }
    for (int i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
    printf("%s ", str);
    return 0;   
}