/*
Ausgabe
Tabelle:
Celsius Fahrenheit
    -20         -4
      0         32
     20         68
     40        104
     60        140
        [...]
    300        572
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Celsius\tFahrenheit\n");
    for (int i = -20; i <= 300; i += 20)
    {
        printf("%7d\t %9d", i, i * 9 / 5 + 32);
        printf("\n");
    }
    return 0;
}
