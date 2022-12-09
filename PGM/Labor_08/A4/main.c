#include <stdio.h>

double calculate_series(double a, double x, int N)
{
    double result = 0;
    int i;
    for (i = 1; i <= N; i++)
    {
        result = result + (a + 2 * i * x);
    }
    return result;
}

int main(int argc, char *argv[])
{
    double a, x;
    int N;
    scanf("%lf %lf %d", &a, &x, &N);
    printf("%.1lf", calculate_series(a, x, N));
    return 0;
}
