#include <iostream>
using namespace std;

import mit;
import ang;
import bos;

int main()
{
    Boss b("Gerd", "Mayer", 1000.00);
    b.print();
    cout << "Gehalt: " << b.getEinkommen() << endl << endl;
    Angestellter a("Rainer", "Mueller", 10.00, 40);
    a.print();
    cout << "Lohn: " << a.getEinkommen() << endl;
    return 0;
}