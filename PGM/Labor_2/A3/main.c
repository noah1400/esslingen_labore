/*
Eingabe
85000 150
*/

/*
Der BMI liegt bei: 37.78!
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
    float gewicht, groesse;
    scanf("%f %f", &gewicht, &groesse);
    gewicht = gewicht / 1000;
    groesse = groesse / 100;
    float bmi = gewicht / (groesse * groesse);
    printf("Der BMI liegt bei: %.2f!", bmi);
    return 0;
}