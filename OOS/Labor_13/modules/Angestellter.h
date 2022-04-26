#include <string>
using namespace std;

#include "Mitarbeiter.h"



class Angestellter : Mitarbeiter/* HIER */
{
    double stundenLohn;
    double stunden;

public:
    Angestellter(const string, const string, double = 0.0, double = 0.0);
    double getEinkommen() const;
    void print() const;
};