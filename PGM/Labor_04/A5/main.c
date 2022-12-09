/*
Eingabe
Programmieren
*/

/*
pROGRAMMIEREN
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
    char str[40];
    scanf("%s", str);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32;
        }
    }
    printf("%s", str);
    return 0;
}