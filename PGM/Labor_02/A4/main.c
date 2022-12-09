/*
Beispielhafte Eingabe mit Gewicht in Gramm und Größe in Zentimeter:
82400 184
*/

/*
BMI	Ausgabe
bmi < 18.4	Untergewicht bmi-Wert
18.4 < bmi < 24.9	Normalgewicht bmi-Wert
bmi >= 24.9	Uebergewicht bmi-Wert
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
    float gewicht, groesse;
    float bmi;
    scanf("%f %f", &gewicht, &groesse);
    gewicht = gewicht / 1000;
    groesse = groesse / 100;
    bmi = gewicht / (groesse * groesse);
    if (bmi < 18.4)
    {
        printf("Untergewicht %.1f", bmi);
    } else if (bmi < 24.9)
    {
        printf("Normalgewicht %.1f", bmi);
    } else
    {
        printf("Uebergewicht %.1f", bmi);
    }
    return 0;
}
