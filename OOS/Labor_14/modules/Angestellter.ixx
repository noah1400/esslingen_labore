module;
#include<iostream>
using namespace std;
export module ang;
import mit;

export class Angestellter : public Mitarbeiter
{
    double stundenLohn;
    double stunden;

public:
    Angestellter(const string vn, const string nn, double stdl = 0.0, double std = 0.0) : Mitarbeiter(vn, nn)
    {
        stundenLohn = stdl;
        stunden = std;
    }

    double getEinkommen() const
    {
        return stundenLohn * stunden;
    }

    void print() const
    {
        cout << "Angestellter: ";
        Mitarbeiter::print();
    }
};