#include <stdio.h>

int potenz_rekursive(int a, int b, int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return potenz_rekursive(a, b, n - 1) * (a + b);
    }
}

int main(int argc, char *argv[])
{
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);
    printf("%d", potenz_rekursive(a, b, n));
    return 0;
}
