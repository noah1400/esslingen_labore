
#include <iostream>
using namespace std;
int function(int i_1)
{
    cout << "Funktion  1: i_1=" << i_1 << endl;
    return 0;
}
// void function(int i_1)
// {
//     cout << "Funktion  2: i_1=" << i_1 << endl;
// }
// char function(int i_1)
// {
//     cout << "Funktion  3: i_1=" << i_1 << endl;
//     return 'a';
// }

// int function(int &i_1)
// {
//     cout << "Funktion  4: i_1=" << i_1 << endl;
//     return 1;
// }
int function(int i_1, int i_2)
{
    cout << "Funktion  5: i_1=" << i_1 << " i_2=" << i_2 << endl;
    return 1;
}
int function(char c_1, int i_1)
{
    cout << "Funktion  6: c_1=" << c_1 << " i_1=" << i_1 << endl;
    return 1;
}
// int function(int i_1, int i_2 = 0)
// {
//     cout << "Funktion  7: i_1=" << i_1 << " i_2=" << i_2 << endl;
//     return 1;
// }
int function(double d_1, int i_1, char c_1 = 'a')
{
    cout << "Funktion  8: d_1=" << d_1 << " i_1=" << i_1 << " c_1=" << c_1 << endl;
    return 1;
}
int function(double d_1, double d_2 = 1.1, int i_1 = 0)
{
    cout << "Funktion  9: d_1=" << d_1 << " d_2=" << d_2 << " i_1=" << i_1 << endl;
    return 1;
}
// int function(double d_1, double d_2 = 1.1, char c_1)
// {
//     cout << "Funktion 10: d_1=" << d_1 << " d_2=" << d_2 << " c_1=" << c_1 << endl;
//     return 1;
// }
int function(char c_1, char c_2, int i_1 = 2, char c_3 = 'c')
{
    cout << "Funktion 11: c_1=" << c_1 << " c_2=" << c_2 << " i_1=" << i_1 << " c_3=" << c_3 << endl;
    return 1;
}
int main(int argc, char *argv[])
{
    int i = 1;
    char c = 'a';
    function(1);
    function(c);
    function(i);
    c = function('a');
    c = 'a';
    function(1, 2);
    function(c, i);
    function(1.0, 2.0);
    function(1.0, 2.0, 1);
    function(1.0, 1, 'a');
    function(1.0, 1);
    function(1.0, static_cast<double>(i));
    function(c, c, i);
    function(c, i);
    return 0;
}
