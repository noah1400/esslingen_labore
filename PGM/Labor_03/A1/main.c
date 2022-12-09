/*
Eingabe
5
*/

/*
Ausgabe
*****
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("*");
    }
    return 0;
}
