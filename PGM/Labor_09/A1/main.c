#include <stdio.h>

typedef struct Bruch
{
    float zaehler;
    float nenner;
} Bruch;

Bruch mult(Bruch a, Bruch b)
{
    Bruch c;
    c.zaehler = a.zaehler * b.zaehler;
    c.nenner = a.nenner * b.nenner;
    return c;
}

Bruch div(Bruch a, Bruch b)
{
    Bruch c;
    c.zaehler = a.zaehler * b.nenner;
    c.nenner = a.nenner * b.zaehler;
    return c;
}

int main(int argc, char *argv[])
{

    float zaehler1, nenner1, zaehler2, nenner2;
    scanf("%f/%f", &zaehler1, &nenner1);
    scanf("%f/%f", &zaehler2, &nenner2);

    Bruch a = {zaehler1, nenner1};
    Bruch b = {zaehler2, nenner2};
    Bruch c = mult(a, b);
    Bruch d = div(a, b);

    printf("(%.1f/%.1f)*(%.1f/%.1f)=(%.1f/%.1f)\n", a.zaehler, a.nenner, b.zaehler, b.nenner, c.zaehler, c.nenner);
    printf("(%.1f/%.1f)/(%.1f/%.1f)=(%.1f/%.1f)", a.zaehler, a.nenner, b.zaehler, b.nenner, d.zaehler, d.nenner);
}
