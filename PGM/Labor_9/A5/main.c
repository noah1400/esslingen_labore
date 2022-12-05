#include <stdio.h>

double calculate_series(double a, double x, int N, int i)
{
    if (i == N)
    {
        return a + 2 * i * x;
    }
    else
    {
        return calculate_series(a, x, N, i + 1) + (a + 2 * i * x);
    }
}

int main(int argc, char *argv[])
{
    double a, x;
    int N;
    scanf("%lf %lf %d", &a, &x, &N);
    printf("%.1lf", calculate_series(a, x, N, 1));
    return 0;
}
