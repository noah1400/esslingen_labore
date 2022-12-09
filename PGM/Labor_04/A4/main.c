/*
Eingabe
w Programmieren
*/

/*
Ausgabe
Prwgrwmmwwrwn
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
    char vowel, str[100];
    scanf(" %c %s", &vowel, str);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u'
            || str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U') {
            str[i] = vowel;
        }
    }
    printf("%s", str);
    return 0;
}
