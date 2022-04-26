#include <iostream>
using namespace std;

/* HIER */
#include "Angestellter.h"

Angestellter::Angestellter(const string vn, const string nn,
                   double stdl, double std)
    : Mitarbeiter(vn, nn)
{
    /* HIER */
    stundenLohn = stdl;
    stunden = std;
}
double Angestellter::getEinkommen() const
{
    /* HIER */
    return stundenLohn * stunden;
}

void Angestellter::print() const
{
    cout << "Angestellter: ";
    Mitarbeiter::print();
}