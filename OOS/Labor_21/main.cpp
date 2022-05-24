
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Eigene Exceptionklasse "MyException"
// abgeleitet von Exception
class MyException : public exception
{
    public:
        string file;
        int line;
        string message;
        MyException(string file, int line, string msg);
        virtual const char* what() const noexcept override;
};

MyException::MyException(string file, int line, string msg)
: file(file), line(line), message(msg)
{
}

const char* MyException::what() const noexcept
{
    return message.c_str();

}

// Eigene Exceptionklasse "ElefantTrifftAufMaus"
// abgeleitet von MyException
class ElefantTrifftAufMaus: public MyException {  // HIER
	// HIER
    public:
        ElefantTrifftAufMaus(string file, int line, string msg);
};

ElefantTrifftAufMaus::ElefantTrifftAufMaus(string file, int line, string msg)
: MyException(file, line, msg)
{
}

// Klasse der Tiere
class Tier {
	// Name des Tiers
	string name;
public:
	// Konstruktor
	Tier(string n = "") : name(n) {};
	// virtuelle print-Funktion
	virtual void print(bool nl) const {
        cout << name;
        if (nl) { cout << endl; }
    }
    virtual Tier* clone() const = 0;

    string getName() const { return name; }
};

class Elefant : public Tier {
public:
	// Konstruktor
	Elefant(string n = " ") : Tier(n) {}
	// virtuelle clone-Funktion
	virtual Elefant* clone() const {
        return new Elefant(*this);
    }
};

class Tiger : public Tier {
public:
	// Konstruktor
	Tiger(string n = "") : Tier(n) {};
	// virtuelle clone-Funktion
	virtual Tiger* clone() const {
        return new Tiger(*this);
    }
};

class Maus : public Tier {
public:
	// Konstruktor
	Maus(string n = "") : Tier(n) {};
	// virtuelle clone-Funktion
	virtual Maus* clone() const {
        return new Maus(*this);
    }
};

class Zoo {
	// Name des Zoos
	string name;
	// Die Tiere werden in einem vektor gespeichert 
    vector<Tier*> tiere;
public:
	// Konstruktor
    Zoo(string n) {
        // Name zuweisen
        name = n;
        // Wenn der String kuerzer als 4 Zeichen ist, 
        // dann MyException werfen
        // Nutzen Sie die Praeprozessormakros __LINE__ und __FILE__
        // HIER






        if(n.length() < 4) {
            throw MyException(__FILE__, __LINE__, "Fehler ZoonameZuKurz ");
        }

        // Ansonsten, den 5. Buchstaben des Namens gross machen
        name.at(4) = toupper(name.at(4));
    }

	
	// Ein Tier dem Zoo hinzufuegen
    void hinzu(const Tier &t) {
        // Wenn ein Elefant hinter/nach einer Maus eingefuegt wird, 
        // dann Ausnahme werfen
        // Nutzen Sie die Praeprozessormakros __LINE__ und __FILE__
        
        if(tiere.size() > 0){
            if ((typeid(*tiere[tiere.size()-1]) == typeid(Elefant) && typeid(t) == typeid(Maus))
                || (typeid(*tiere[tiere.size()-1]) == typeid(Maus) && typeid(t) == typeid(Elefant))){
                
                
                throw ElefantTrifftAufMaus(__FILE__, __LINE__, "Fehler ElefantTrifftAufMaus ");
            }
        }
        tiere.push_back(t.clone());

    }
	// Alle Zootiere ausgeben
    void print() const {
        // HIER
        for(auto it = tiere.begin(); it != tiere.end(); it++) {
            (*it)->print(true);
        }
    }
};

int main(int argc, char* argv[]) {
	string str;
	char c = 'X';
	// Ausnahmepruefung aktivieren
	// HIER
    try {


		cout << "Bitte Name des Zoos eingeben: ";
		cin >> str;
		Zoo z(str);
		while (c != 'e') {
			cout << endl << "Bitte Tierart auswaehlen:" << endl;
			cout << "1 = Elefant" << endl;
			cout << "2 = Tiger" << endl;
			cout << "3 = Maus" << endl;
			cout << "e = Ende mit Eingabe" << endl;
			cout << "Eingabe: ";
			cin >> c;
			if (c != 'e') {
				cout << "Bitte Namen des Tieres eingeben: ";
				cin >> str;
				Elefant el;
				Tiger ti;
				Maus ma;
				switch (c) {
				case '1': el = Elefant(str); z.hinzu(el); break;
				case '2': ti = Tiger(str); z.hinzu(ti); break;
				case '3': ma = Maus(str); z.hinzu(ma); break;
				case 'e': break;
				default: // Einen String als Ausnahme werfen
					// HIER
                    throw string("Ungueltige Eingabe");


				}
			}
			cout << endl;
			z.print();
		}


    }
	// Ausnahmen auffangen
	// Speziellste Ausnahme auffangen und ausgeben
	// HIER
    catch(ElefantTrifftAufMaus &e) {
        cout << e.what() << "aufgetreten in Datei " << e.file  << ", Zeile: " << e.line << "." << endl;
    }





	// MyException auffangen und ausgeben
	// HIER
    catch(MyException &e) {
        cout << e.what() << "aufgetreten in Datei " << e.file  << ", Zeile: " << e.line << "." << endl;
    }






	// Alle anderen Standardausnahmen auffangen und ausgeben
	// HIER
    catch(exception &e) {
        cout << "Standardausnahme: " << e.what() << endl;
    }





	// Alle anderen Ausnahmen auffangen
	// HIER
    catch(...) {
        cout << "Exception" << endl;
    }




	return 0;
}


