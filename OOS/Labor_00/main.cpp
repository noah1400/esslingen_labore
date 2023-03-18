#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    int size;
    cout << "Anzahl eingeben:" << endl;
    cin >> size;
    int numbers[size];
    for (int i = 0; i < size; i++)
    {
        cout << "Zahl eingeben:" << endl;
        cin >> numbers[i];
    }
    for (int i = 0; i < size; i++)
    {
        cout << "Zahl[" << i << "]: " << numbers[i] << endl;
    }
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += numbers[i];
    }
    cout << "Durchschnitt: " << sum / size << endl;
    return 0;
}
