
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Klasse für alle Personen, die Medien ausleihen können aus Aufgabe 10
class Person
{
    // Name der Person
    string name;
    // Dauer in Tagen, die die Person ein Medium ausleihen darf
    // wird von den abgelieteten Klassen festgelegt
    int ausleihdauer;

public:
    // Standardkonstruktor
    Person(string name, int dauer = 0);
    // den Namen zurückliefern
    string getName() const;
    // die Ausliehdauer zurückliefern
    int getAusleihdauer() const;
    // die Person auf der Konsole ausgeben
    void print() const;
};

Person::Person(string name, int dauer)
    : name(name), ausleihdauer(dauer)
{
}

string Person::getName() const
{
    return name;
}

int Person::getAusleihdauer() const
{
    return ausleihdauer;
}

void Person::print() const
{
    cout << name;
}

// Klasse Dozent als Spezialisierung von Person aus Aufgabe 10
class Dozent : public Person
{
    // Prüfernummer des Dozenten
    int prfrNr;

public:
    // Standardkonstruktor
    Dozent(string name, int prfrNr);
    // Dozenten auf der Konsole ausgeben
    void print() const;
};

Dozent::Dozent(string name, int prfrNr)
    : Person(name, 90), prfrNr(prfrNr)
{
}

void Dozent::print() const
{
    Person::print();
    cout << "prfrNr" << prfrNr << endl;
}

// Klasse Student als Spezialisierung von Person aus Aufgabe 10
class Student : public Person
{
    // Matrikelnummer des Studenten/der Studentin
    int matNr;

public:
    // Standardkonstruktor
    Student(string name, int matNr);
    // Student auf der Konsole ausgeben
    void print() const;
};

Student::Student(string name, int matNr)
    : Person(name, 30), matNr(matNr)
{
}

void Student::print() const
{
    Person::print();
    cout << "matNr" << matNr;
}

// Klasse Datum aus Aufgabe 9
class Datum
{
    // Elemente eines Datums
    int tag, monat, jahr;

public:
    // Standardkonstruktor
    Datum(int = 0, int = 0, int = 0);
    // ** neu **
    // Konvertierkonstruktor für String
    Datum(const string&);
    // ** neu **
    // Konvertierkonstruktor für C-String
    Datum(const char*);
    // Operator + addiert eine Anzahl von Tagen zum Datum hinzu
    Datum operator+(int tage);
    // Ausgabeoperator <<, Ausgabe in dem Format tt.mm.jjjj
    friend ostream& operator<<(ostream&, const Datum&);
};

Datum::Datum(int t, int m, int j)
    : tag(t), monat(m), jahr(j)
{
}

Datum::Datum(const string& datumStr) {
    string tstr(datumStr, 0, 2);
    string mstr(datumStr, 3, 2);
    string jstr(datumStr, 6, 9);


    tag = stoi(tstr);
    monat = stoi(mstr);
    jahr = stoi(jstr);
}

// hier Konvertierkonstruktor für String

// hier Konvertierkonstruktor für C-String

Datum::Datum(const char* datumChars) {
    string datumStr(datumChars);


    string tstr(datumStr, 0, 2);
    string mstr(datumStr, 3, 2);
    string jstr(datumStr, 6, 9);

    tag = stoi(tstr);
    monat = stoi(mstr);
    jahr = stoi(jstr);
}

Datum Datum::operator+(int tage)
{
    int absDate = tag + monat * 30 + jahr * 360;
    absDate += tage;
    int j = absDate / 360;
    absDate = absDate % 360;
    int m = absDate / 30;
    absDate = absDate % 30;
    int t = absDate;

    return Datum(t, m, j);
}

ostream& operator<<(ostream& os, const Datum& d)
{
    os << d.tag << "." << d.monat << "." << d.jahr;
    return os;
}


// Klasse für die Medien, die in der Bibliothek ausgeliehen werden
// können
class Medium
{

protected:
    // Titel des Mediums
    const string titel;
    // Verlag, der das Medium herausgibt
    const string verlag;
    // Jahr, in dem das Medium veröffentlicht wurde
    const int jahr;
    // ausgeliehen am
    Datum von;
    // ausgeliehen bis
    Datum bis;
    // ausgeliehen von
    Person* ausleiher;

public:
    // Konstruktor
    Medium(string _titel = "", string _verlag = "", int _jahr = 0);
    virtual ~Medium();
    // Titel zurückliefern
    string getTitel() const;
    // Ausleiher zurückliefern
    Person* getAusleiher() const;
    // das Medium "ausleihen", d.h. Person p, von und bis eintragen
    void ausleihen(Person& _person, Datum _von, Datum _bis);
    // Medium in der Konsole ausgeben
    virtual void print() const;
    virtual Medium* clone() const;
};

// hier Konstruktor und Methoden
Medium::Medium(string _titel, string _verlag, int _jahr) : titel(_titel), verlag(_verlag), jahr(_jahr) {
    ausleiher = nullptr;
}

Medium::~Medium(){}

void Medium::print() const {
    cout << "Titel:         " << titel << endl;
    cout << "Verlag:        " << verlag << endl;
    cout << "Jahr:          " << jahr << endl;
    cout << "Ausleiher:     ";
    if (ausleiher != nullptr) {
        ausleiher->print();
        cout << " von: " << von << " bis: " << bis;
    }
    else {
        cout << "-";
    }
    cout << endl;
} 

string Medium::getTitel() const {
    return titel;
}

Person* Medium::getAusleiher() const {
    return ausleiher;
}

Medium* Medium::clone() const {
    return new Medium(*this);
}

void Medium::ausleihen(Person& _person, Datum _von, Datum _bis) {
    ausleiher = &_person;
    von = _von;
    bis = _bis;
}

// Klasse für die Bücher als Spezialisierung von Medium
class Buch: public Medium
{
    // Autor(en) des Buches
    string autor;

public:
    // Standardkonstruktor
    Buch(string _autor = "", string _titel = "", string _verlag = "", int _jahr = 0);
    // das Buch auf der Konsole ausgeben
    void print() const;
    Medium* clone() const override;
};

Medium* Buch::clone() const {
    return new Buch(*this);
}

Buch::Buch(string _autor, string _titel, string _verlag, int _jahr):Medium(_titel, _verlag, _jahr), autor(_autor){}

void Buch::print() const {
    cout << "Author:        " << autor << endl;
    Medium::print();
    cout << endl;
}
// hier Konstruktor und Methoden

// Klasse für die DVDs als Spezialisierung von Medium
class DVD: public Medium
{
    // Abspieldauer der DVD
    const int dauer;

public:
    // Standardkonstruktor
    DVD(string _titel = "", string _verlag = "", int _jahr = 0, int _dauer = 0);

    // die DVD auf der Konsole ausgeben
    void print() const;
    Medium* clone() const override;
};

DVD::DVD(string _titel, string _verlag, int _jahr, int _dauer):Medium(_titel, _verlag, _jahr), dauer(_dauer) {}

// hier Konstruktor und Methoden
Medium* DVD::clone() const {
    return new DVD(*this);
}



void DVD::print() const {
    Medium::print();
    cout << "Dauer:         " << dauer << endl << endl;
}

// Die Klasse Bibliothek verweist auf alle Medien (Bücher und DVDs),
// die von Personen (Studierende und Dozenten) ausgeliehen werden 
// können.
class Bibliothek
{
    // maximale Anzahl der Medien im Katalog
    const int maxAnz;
    // Der Medienkatalog
    vector<Medium*> medien;
public:
    // Standardkonstruktor
    Bibliothek(int maxAnz = 1000);

    // Kopie einer DVD oder eines Buches in den Katalog der Bibliothek eintragen
    // Die maximale Anzahl an Medien darf nicht überschritten werden
    void mediumBeschaffen(Medium&);

    // alle Medien auf der Konsole ausgeben, 
    // die im Titel das Suchwort enthalten
    void mediumSuchen(string suchwort);

    // im Medium mit der Nummer nr, die Person p als Ausleiher
    // eintragen mit von-Datum d und bis-Datum d+p.ausleihdauer
    void mediumAusleihen(int nr, Person& p, Datum d);

    // alle Medien in der Konsole ausgeben
    void print() const;
};

void Bibliothek::print() const {
    cout  << "Bibliothekskatalog:" << endl;
    cout << "---------------------------------------" << endl << endl;
    for (unsigned int i = 0; i < medien.size(); i++) {
        cout << "Medium " << i << ":" << endl;
        medien[i]->print();
    }
    cout << "---------------------------------------" << endl << endl;
}

Bibliothek::Bibliothek(int maxAnz): maxAnz(maxAnz){}

void Bibliothek::mediumBeschaffen(Medium& m) {
    if (medien.size() != static_cast<unsigned int>(maxAnz)) {
        medien.push_back(m.clone());
    }
}

void Bibliothek::mediumSuchen(string suchwort) {
    cout  << "Suche nach \"" << suchwort << "\" Ergebnis:" << endl;
    cout << "---------------------------------------" << endl << endl;
    for (unsigned int i = 0; i < medien.size(); i++) {
        if (medien[i]->getTitel().find(suchwort) != string::npos) {
            cout << "Medium " << i << ":" << endl;
            medien[i]->print();
        }
    }
    cout << "---------------------------------------" << endl << endl;
}

void Bibliothek::mediumAusleihen(int nr, Person& p, Datum d) {
    medien[nr]->ausleihen(p, d, d + p.getAusleihdauer());
}

// hier Konstruktor und Methoden

int main(int argc, char* argv[])
{
    // Umlaute etc. in der Konsole zulassen
    setlocale(LC_ALL, "");
    // Bibliothek mit 100 Plätzen initialisieren
    Bibliothek bib(100);
    // Bücher und DVDs erstellen
    Buch b1("Jürgen Wolf", "C++: das umfassende Handbuch", "Galileo Press", 2014);
    Buch b2("Arnold Willemer", "C++ - der Einstieg", "Wiley", 2014);
    Buch b3("Rainer Grimm", "Der C++-Programmierer", "O'Reilly", 2014);
    Buch b4("Stephen R. Davies", "C++ for Dummies", "Wiley", 2012);
    Buch b5("Ulla Kirch und Peter Prinz", "C++ lernen und professionell anwenden", "mitp", 2012);
    Buch b6("Matt Richardson", "BeagleBone für Einsteiger", "O'Reilly", 2014);
    DVD d1("Die Rächer von C++", "DVD ex", 1984, 127);
    DVD d2("Ganz nah dabei - Raumgestaltung in Kitas / für 0- bis 3-Jährige", "Cornelsen", 2013, 58);
    // Ein Buch und eine DVD ausgeben
    b1.print();
    d1.print();
    cout << endl;
    // Kopien der Bücher und DVDs (Medien) in die Bibliothek
    // einfügen
    bib.mediumBeschaffen(b1);
    bib.mediumBeschaffen(b2);
    bib.mediumBeschaffen(b3);
    bib.mediumBeschaffen(b4);
    bib.mediumBeschaffen(b5);
    bib.mediumBeschaffen(b6);
    bib.mediumBeschaffen(d1);
    bib.mediumBeschaffen(d2);
    // Bestand der Bibliothek ausgeben
    bib.print();
    // Personen anlegen
    Student p1("Peter", 12345678);
    Student p2("Lisa", 87654321);
    Dozent p3("Prof Mueller", 4711);
    // Suchen im Bibliotheksbestand durchführen
    bib.mediumSuchen("C++");
    bib.mediumSuchen("Kita");
    // Medien ausleihen
    bib.mediumAusleihen(1, p1, "03.05.2022");
    bib.mediumAusleihen(7, p2, "07.05.2022");
    bib.mediumAusleihen(4, p3, "08.05.2022");
    // Bestand der Bibliothek ausgeben
    bib.print();
}

