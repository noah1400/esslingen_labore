#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(int argc, char* argv[])
{
    float iArr[4];
    float min;
    int i, index=0;
    for (i = 0; i < 4; i++)
    {
        scanf("%f", &iArr[i]);
    }

    min = iArr[0];

    for (i = 0; i < 4; i++)
    {
        if (iArr[i] < min)
        {
            min = iArr[i];
            index = i;
        }
    }

    printf("Kleinste Zahl: %.1f an Index %d", min, index);

    return 0;
}