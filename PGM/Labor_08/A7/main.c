#include <stdio.h>

int isPrime(int n, int i)
{
    if (n < 2)
    {
        return 0;
    }
    if (n == 2)
    {
        return 1;
    }
    if (n % 2 == 0)
    {
        return 0;
    }
    if (i * i > n)
    {
        return 1;
    }
    if (n % i == 0)
    {
        return 0;
    }
    return isPrime(n, i + 2);
}

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    int ip = isPrime(n, 3);
    printf("%d", ip);
    return 0;
}
