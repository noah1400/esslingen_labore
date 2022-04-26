module;
#include<iostream>
using namespace std;
export module bos;
import mit;
export class Boss : public Mitarbeiter
{
    double bossGehalt;

public:
    Boss(const string vn, const string nn, double g = 0)
    : Mitarbeiter(vn, nn) 
{
        bossGehalt = g;
}
    double getEinkommen() const
{
        return bossGehalt;
}
void print() const
{
    cout << "Boss: ";
    Mitarbeiter::print();
}
};


