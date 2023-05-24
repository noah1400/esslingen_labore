#include <stdio.h>

int fibonacci(int n)
{
    int first = 0;
    int second = 1;
    int result = 0;

    for (int i = 2; i <= n; i++)
    {
        result = first + second;
        first = second;
        second = result;
    }

    return result;
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