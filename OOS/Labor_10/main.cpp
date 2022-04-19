
#include <string>
#include <iostream>
using namespace std;

class Person {
	string name;
	int ausleihdauer;
public:
	Person(string name, int dauer = 0);
	int getAusleihdauer() const;
	void print() const;
};

Person::Person(string name, int dauer): name(name), ausleihdauer(dauer) {}
int Person::getAusleihdauer() const { return ausleihdauer; }
void Person::print() const { cout << name; }
// Implmentierung des Konstruktors und der Methoden

class Dozent : public Person
{
	int prfrNr;
public:
	Dozent(string name, int prfrNr);
	void print() const;
};

Dozent::Dozent(string name, int prfrNr): Person(name,90), prfrNr(prfrNr) {}
void Dozent::print() const {
    Person::print();
    cout << ", prfrNr " << prfrNr << endl;
}

// Implmentierung des Konstruktors und der Methoden

class Student : public Person
{
	int matNr;

public:
	Student(string name, int matNr);
	void print() const;
};

Student::Student(string name, int matNr): Person(name,30), matNr(matNr) {}
void Student::print() const {
    Person::print();
    cout << ", matNr " << matNr << endl;
}

// Implmentierung des Konstruktors und der Methoden

int main(int argc, char *argv[]) {
    Student maier = Student("maier", 12345678);
    Dozent mueller = Dozent("mueller", 98);
    maier.print();
    cout << "Ausleihdauer: " << maier.getAusleihdauer() << " Tage(e)" << endl;
    mueller.print();
    cout << "Ausleihdauer: " << mueller.getAusleihdauer() << " Tage(e)" << endl;
}

