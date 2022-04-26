/* hier */

#include <string>
using namespace std;

#ifndef MITARBEITER_H
#define MITARBEITER_H
class Mitarbeiter
{
    string vorname;
    string nachname;
 
public:
    Mitarbeiter(const string, const string);
    void print() const;
};
#endif