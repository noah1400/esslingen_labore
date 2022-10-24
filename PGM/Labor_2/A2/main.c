/*
Eingabe
20.5
*/

/*
Ausgabe
20.5 Grad Fahrenheit = -6.4 Grad Celsius
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main(int argc, char *argv[])
{
    float fahrenheit;
    scanf("%f", &fahrenheit);
    float celsius = (fahrenheit - 32) * 5 / 9;
    printf("%.1f Grad Fahrenheit = %.1f Grad Celsius", fahrenheit, celsius);
    return 0;
}