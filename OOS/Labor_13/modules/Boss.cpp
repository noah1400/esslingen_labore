#include <iostream>
using namespace std;

/* HIER */
#include "Boss.h"

Boss::Boss(const string vn, const string nn, double g = 0)
    : Mitarbeiter(vn, nn) 
{
    /* HIER */
    bossGehalt = g;
}
double Boss::getEinkommen() const
{
    /* HIER */
    return bossGehalt;
}
void Boss::print() const
{
    cout << "Boss: ";
    Mitarbeiter::print();
}