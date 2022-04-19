
#include <iostream>
#include <string>
using namespace std;

class A {
public:
	void f() {
		cout << "A::f()" << endl;
	}
	void g(double d) {
		cout << "A::g(double)" << endl;
	}
	void g(string s) {
		cout << "A::g(string)" << endl;
	}
	void h(char c) {
		cout << "A::h(char)" << endl;
	}
	void h(string s) {
		cout << "A::h(string)" << endl;
	}
};

class B : public A {
public:
	void g(int i) {
		cout << "B::g(int)" << endl;
	}
	void h(int i) {
		cout << "B::h(int)" << endl;
	}
	void h(string s) {
		cout << "B::h(string)" << endl;
	}
};

int main(int argc, char *argv[]) {
	A a;
	B b;
	cout << "a.f() ";
	a.f(); // a) keine Fehlermeldung; b) Ausgabe: a.f(): A::f()
	cout << "b.f() ";
	b.f(); // a) keine Fehlermeldung; b) Ausgabe: b.f(): A::f()
	cout << "a.g(1.2) ";
	a.g(1.2);// a) keine Fehlermeldung; b) Ausgabe: a.g(1.2): A::g(double)
	cout << "b.g(1.2) ";
	b.g(1.2);// a) keine Fehlermeldung; b) Ausgabe: b.g(1.2): A::g(int)
	cout << "a.g(1) ";
	a.g(1);// a) keine Fehlermeldung; b) Ausgabe: a.g(1) A::g(double)
	cout << "b.g(1) ";
	b.g(1);// a) keine Fehlermeldung; b) Ausgabe: b.g(1): A::g(int)
	cout << "a.g('a') ";
	a.g('a');// a) keine Fehlermeldung; b) Ausgabe: a.g('a') A::g(double)
	cout << "b.g('a') ";
	b.g('a');// a) keine Fehlermeldung; b) Ausgabe: b.g('a') B::g(int)
	cout << "a.g(''a'') ";
	a.g("a");// a) keine Fehlermeldung; b) Ausgabe: a.g(''a'') A::g(string)
	//cout << "b.g(''a'') ";
	//b.g("a"); // a) Fehlermeldung
	cout << "a.h(1) ";
	a.h(1);// a) keine Fehlermeldung; b) Ausgabe: a.h(1) A::h(char)
	cout << "b.h(1) ";
	b.h(1);// a) keine Fehlermeldung; b) Ausgabe: b.h(1) B::h(int)
	cout << "a.h('a') ";
	a.h('a');// a) keine Fehlermeldung; b) Ausgabe: a.h('a') A::h(char)
	cout << "b.h('a') ";
	b.h('a');// a) keine Fehlermeldung; b) Ausgabe: b.h('a') B::h(int)
	cout << "a.h(''a'') ";
	a.h("a");// a) keine Fehlermeldung; b) Ausgabe: a.h(''a'') A::h(string)
	cout << "b.h(''a'') ";
	b.h("a");// a) keine Fehlermeldung; b) Ausgabe: b.h(''a'') B::h(string)
	return 0;
}


//Aufgabe c)
//Funktion      | überlädt, verdeckt oder redefniert. | Funktion
//-------------------------------------------------------------------
//void B::g(int i) | verdeckt                            | void A::g(double d)
//void B::h(int i) | überlädt                            | void B::h(string s)
//void B::h(string s) | redefiniert + verdeckt           | void A::h(string s)




