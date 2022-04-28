
#include <cstddef>
#include <array>
#include <iostream>
using namespace std;

const unsigned int laenge = 10;

//hier

// Bubblesort Template
// returns sorted array
// takes array of size laenge
template <typename T>
array<T,laenge> sortiere(array<T,laenge> array)
{
    T temp;
    bool swapped = true;
    unsigned int counter = 0;
    while(swapped && counter < laenge)
    {
        swapped = false;
        for(unsigned int i = 0; i < laenge - 1-counter; i++)
        {
            if(array[i] > array[i + 1])
            {
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                swapped = true;
            }
        }
    }
    return array;
}


int main(int argc, char *argv[]) 
{
    array<int,laenge> int_feld = {10, 2, 7, 5, 8, 3, 4, 1, 9, 6};
    array<int, laenge> int_feld_sortiert = sortiere(int_feld);

    for (size_t i = 0; i < int_feld_sortiert.size(); i++) {
        cout << i << ": " << int_feld_sortiert[i] << endl;
    }

    array<char,laenge> char_feld = {'j', 'm', 'e', 't', 'k', 'o', 'p', 's', 'a', 'f'};
    array<char, laenge> char_feld_sortiert = sortiere(char_feld);

    for (size_t i = 0; i < char_feld_sortiert.size(); i++) {
        cout << i << ": " << char_feld_sortiert[i] << endl;
    }

}

