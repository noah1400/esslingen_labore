#include <iostream>
#include <string>
using namespace std;
#include "Mitarbeiter.h"

/* HIER */

Mitarbeiter::Mitarbeiter(const string vn, const string nn)
{
    /* HIER */
    vorname = vn;
    nachname = nn;
}
void Mitarbeiter::print() const
{
    cout << nachname << ", " << vorname << endl;
}