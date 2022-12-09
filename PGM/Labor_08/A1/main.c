#include <stdio.h>

int potenz_iter(int a, int b, int n)
{
    int i, result = 1;
    for (i = 0; i < n; i++)
    {
        result = result * (a + b);
    }
    return result;
}

int main(int argc, char *argv[])
{
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);
    printf("%d", potenz_iter(a, b, n));
    return 0;
}
