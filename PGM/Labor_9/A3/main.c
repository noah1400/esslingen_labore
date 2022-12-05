#include <stdio.h>

int faculty(int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return faculty(n - 1) * n;
    }
}

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    printf("%d! = %d", n, faculty(n));
    return 0;
}
