/*
Eingabe
Programmieren
*/

/*
Ausgabe
12 Kleinbuchstaben
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
    int count;
    char s[100];
    scanf("%s", s);
    count = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            count++;
        }
    }
    printf("%d Kleinbuchstaben", count);
    return 0;
}
