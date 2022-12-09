/*
Eingabe
1 2 3 
42.1356 
Esslingen
*/

/*
Ausgabe
Ganze Zahlen: 1, 2, 3 
Fliesskommazahl mit Formatangabe: 42.14 
Zeichenkette: Esslingen 
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
    int i1, i2, i3;
    // noch ein Beispiel mit scanf
    scanf("%d %d %d", &i1, &i2, &i3);
    printf("Ganze Zahlen: %d, %d, %d \n", i1, i2, i3);

    float f;
    // Ihr Code hier
    scanf("%f", &f);
    printf("Fliesskommazahl mit Formatangabe: %.2f \n", f);

    char s[100];
    // Ihr Code hier
    scanf("%s", s);
    printf("Zeichenkette: %s \n", s);
    return 0;
}
