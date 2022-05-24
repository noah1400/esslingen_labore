
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char* argv[]) {
	double d = 1.234;
	cout << "Nr  Oct  Hex String  Fixed     Scientific " << endl;
	for (int k = 1; k < 11; k++)
	{
		cout << right << setw(3) << setfill(' ') << dec << k << " ";
		cout << showbase << oct << setw(3)  << k << "  ";
		cout << showbase << hex << k << noshowbase << " ";
		cout << left << setw(7) << setfill('+') << string(k % 5 + 1, '*')  << " ";
		cout << internal << setprecision(3) << setw(9) << setfill(' ') <<  fixed << showpos << d << noshowpos << " ";
		cout << setw(10) << scientific << uppercase << d << nouppercase << " ";
		d = d*-2;
		
		cout << endl;
	}
	return 0;
}

