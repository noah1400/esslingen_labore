#include <string>
using namespace std;

/* HIER */
#include "Mitarbeiter.h"
class Boss : Mitarbeiter/* HIER */
{
    double bossGehalt;

public:
    Boss(const string, const string, double);
    double getEinkommen() const;
    void print() const;
};
