#include <stdio.h>

int fibonacci(int n)
{
    if (n < 2)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    while (n < 2)
        scanf("%d", &n);
    int fib = fibonacci(n);
    printf("%d", fib);
    return 0;
}
