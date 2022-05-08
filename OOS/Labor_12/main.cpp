
#include <iostream>
#include <string>
using namespace std;

// Name s und Wert val einer Instanzvariable ausgeben
void speicherzelle(string s, int val) {
	cout << "---------------------" << endl;
	cout << s << "= " << val << endl;
}

// Die Instanzvariablen raussuchen und ausgeben,
// die wegen virtuellen Basisklassen zusammenfallen
void suche(string s[], int * vptr[], int n) {
	// Zustand von cout zwischenspeichern
	ios::fmtflags cflags = cout.flags(); 
	// Hilfsvariablen initialisieren
	int i = 0;
	int k = 0;
	string str = "";
	// cout für Ausgabe der Instanzvariablen konfigurieren
	cout << hex << uppercase;
	// Schauen, ob Instanzvariable i (vptr[i])
	// evtl. mit Variable k (vptr[k]) zusammenfällt 
	while (i < n) {
		// Wenn Variable i+k und i+k+1 identisch ...
		if ((i+k < n-1) && (vptr[i+k] == vptr[i+k+1])) { 
			// erhöhe k
			k++; 
		} else {
		// andernfalls gib die zusammengefallenen Variablen 
		// auf einer Zeile aus
			// Text für Ausgabe zusammenstellen
			for (int m = i; m<=i+k; m++) {
				str += s[m]+" ";
			}
			// Text und Wert ausgeben
			speicherzelle(str, *vptr[i]);
			// Hilfsvariablen für nächste Prüfung zurücksetzen
			str = "";
			i += k+1;
			k = 0;
		}
	}
	cout << "---------------------" << endl << endl;
	// Ursprünglicher Zustand von cout wieder herstellen
	cout.flags(cflags);
}

// Klassenhierarchie
class A { 
public:
	int a;
	A(int a = 0xA) : a(a) {}
};

class B : virtual public A {
public:
	int b; 
	B(int a = 0xBA, int b = 0xB) : A(a), b(b) {}
};

class C1 : public B { 
public:
	C1(int a = 0xC1A, int b = 0xC1B) 
		: B(a, b) {} 
};

class C2 : virtual public B { 
public:
	C2(int a = 0xC2A, int b = 0xC2B) 
		: B(a, b) {} 
};

class C3 : virtual public B {
public:
	C3(int a = 0xC2A, int b = 0xC2B) 
		: B(a, b) {} 
};

class D1 : public C2, public C3 {
public:
	D1(int C2_a = 0xD1C2A, int C3_a = 0xD1C3A, 
	   int C2_b = 0xD1C2B, int C3_b = 0xD1C3B) 
		: A(0xD1A),C2(C2_a, C2_b), C3(C3_a, C3_b) {}                                                      
	void print() {
		cout << "D1::print() ..." << endl;
		string strArr[] = 
			{ "C2::a", "C3::a", "C2::b", "C3::b" };
		int * intPtrArr[] = { &(C2::a), &(C3::a),  
							  &(C2::b), &(C3::b) };
		suche(strArr, intPtrArr, 4);	
	}
};

class D2 : public C1, public C2, public C3 {
public:
	D2(int C1_a = 0xD2C1A, int C2_a = 0xD2C2A, int C3_a = 0xD2C3A, 
	   int C1_b = 0xD2C1B, int C2_b = 0xD2C2B, int C3_b = 0xD2C3B) 
		: B(0x0,0xD2B),C1(C1_a, C1_b), C2(C2_a, C2_b), C3(C3_a, C3_b) {}                              
	void print() { 
		cout << "D2::print() ..." << endl;
		string strArr[] = { "C1::a", "C2::a", "C3::a", 
			                "C1::b", "C2::b", "C3::b" };
		int * intPtrArr[] = { &(C1::a), &(C2::a), &(C3::a), 
							  &(C1::b), &(C2::b), &(C3::b) };
		suche(strArr, intPtrArr, 6);
	}
};

int main(int argc, char *argv[]) {
	D1 d1obj;
	D2 d2obj;
	d1obj.print();
	d2obj.print();
	return 0;
}

