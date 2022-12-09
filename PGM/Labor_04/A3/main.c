/*
Eingabe
Programmieren
*/

/*
5 Vokale
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
    int count;
    char s[100];
    scanf("%s", s);
    count = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u'
            || s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U') {
            count++;
        }
    }
    printf("%d Vokale", count);
    return 0;
}
