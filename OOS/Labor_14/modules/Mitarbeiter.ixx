module;
#include<iostream>
using namespace std;
export module mit;
export class Mitarbeiter
{
    string vorname;
    string nachname;

public:
    Mitarbeiter(const string vn, const string nn)
    {
        vorname = vn;
        nachname = nn;
    }
    void print() const
    {
        cout << nachname << ", " << vorname << endl;
    }
};
