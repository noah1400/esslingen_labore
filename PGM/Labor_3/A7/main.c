/*
Ausgabe
Tabelle
Fahrenheit      Celsius
       -20       -28.89
         0       -17.78
        20        -6.67
        40         4.44
        60        15.56
            [...]
       300       148.89
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Fahrenheit\tCelsius\n");
    for (int i = -20; i <= 300; i += 20)
    {
        printf("%10d\t%7.2f", i, (5 * ((float)i - 32)) / 9);
        printf("\n");
    }
    return 0;
}
