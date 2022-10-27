#include<iostream>
using namespace std;

class Datum {
	
	int tag, monat, jahr;

public:
	Datum(int = 0, int = 0, int = 0);
	Datum operator+(int tage);
	friend ostream & operator<<(ostream &, const Datum &);
};

// Implementierung des Konstruktors und der Operatoren

Datum::Datum(int t, int m, int j) {
    tag = t;
    monat = m;
    jahr = j;
}

Datum Datum::operator+(int tage) {
    Datum temp;
    // Addiere die Tage und berechne neues Datum
    int tageImMonat[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    temp.tag = tag + tage;
    temp.monat = monat;
    temp.jahr = jahr;
    while (temp.tag > tageImMonat[temp.monat-1]) {
        temp.tag -= tageImMonat[temp.monat-1];
        temp.monat++;
        if (temp.monat > 12) {
            temp.monat = 1;
            temp.jahr++;
        }
    }
    return temp;
}

ostream & operator<<(ostream & os, const Datum & d) {
    os << d.tag << "." << d.monat << "." << d.jahr;
    return os;
}

int main(int argc, char *argv[])
{
    Datum beginnAufgabe = Datum(26,10,2022); // Datum muss hier geändert werden
    cout << "Die Aufgabe beginnt am " << beginnAufgabe << endl;
    Datum endeAufgabe = beginnAufgabe + 8; // Tage müssen angepasst werden
    cout << "Die Aufgabe endet am " << endeAufgabe << endl;
    Datum einJahrMonatSpaeter = beginnAufgabe + 396; // Tage müssen angepasst werden
    cout << "Ein Jahr und ein Monat nach Aufgabenbeginn ist der " << einJahrMonatSpaeter << endl;
}

