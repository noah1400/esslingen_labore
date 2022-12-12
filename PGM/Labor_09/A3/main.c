#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    int *array = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (array[j] > array[j + 1])
            {
                int tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (array[i] == 0)
        {
            printf("%3.d:   0", i + 1);
        }
        else
        {
            printf("%3.d: %3.d", i + 1, array[i]);
        }
    }
}