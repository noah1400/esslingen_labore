#define PI 3.1415

void sphere(double radius, double *volume, double *surface)
{
    *volume = (4.0 / 3.0) * PI * radius * radius * radius;
    *surface = 4.0 * PI * radius * radius;
}