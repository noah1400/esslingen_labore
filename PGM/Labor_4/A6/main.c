/*
Eingabe
Programmieren 3 7
*/

/*
Programmieren 3-7: gramm
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
    char str[40];
    int start, end;
    scanf("%s %d %d", str, &start, &end);
    printf("%s %d-%d: ", str, start, end);
    for (int i = start; i <= end; i++) {
        printf("%c", str[i]);
    }
    return 0;
}
