/*
Eingabe
m 80 500 5 
*/

/*
Ausgabe
0.36 Promille
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
    char geschlecht;
    float gewicht, menge, prozent;
    scanf(" %c %f %f %f", &geschlecht, &gewicht, &menge, &prozent);
    float r;
    if (geschlecht == 'm')
    {
        r = 0.7;
    } else if(geschlecht == 'w')
    {
        r = 0.6;
    }else
    {
        r = 0.8;
    } 
    float A = menge*prozent*0.8;
    float promille = A/(gewicht*r)/100;
    printf("%.2f Promille", promille);
    return 0;
}