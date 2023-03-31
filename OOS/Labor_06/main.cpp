#include <string>
#include <iostream>
using namespace std;

// Klasse Student
class Student
{
    private:
        string _name;
        string _first_name;
    public:
        Student(string name, string vorname);
        ~Student();

        string get_name() const;
        string get_first_name() const;

        void print(bool break_line) const;
        void print() const;
};

Student::Student(string name, string vorname) {
    _name = name;
    _first_name = vorname;
    cout << "Parametrisierter Konstruktor Student: " << _first_name << " " << _name << endl;
};

string Student::get_name() const {
    return _name;
};

string Student::get_first_name() const {
    return _first_name;
};

Student::~Student() {
    cout << "Destruktor Student: " << _first_name << " " << _name << endl;
};

void Student::print(bool break_line) const {
    cout << "print() ";
    cout << "mit Parameter;";
    cout << " Student: " << _first_name << " " << _name;
    if (break_line) {
        cout << endl;
    }
};

void Student::print() const {
    cout << "print() ohne Parameter;";
    cout << " Student: " << _first_name << " " << _name << endl;
};

// Klasse Employee
class Employee
{
    private:
        string _name;
        string _first_name;
    public:
        Employee(string name, string vorname) : _name(name), _first_name(vorname) {
            cout << "Parametrisierter Konstruktor Employee: " << _first_name << " " << _name << endl;
        };
        Employee() : Employee("Mustermann", "Erika") {
            cout << "Standardkonstruktor Employee: " << _first_name << " " << _name << endl;
        };
        Employee(const Student &student) : _name(student.get_name()), _first_name(student.get_first_name()) {
            cout << "Konvertierungskonstruktor Employee: " << _first_name << " " << _name << endl;
        };
        ~Employee() {
            cout << "Destruktor Employee: " << _first_name << " " << _name << endl;
        };

        void print(bool break_line) const {
            cout << "print() ";
            cout << "mit Parameter;";
            cout << " Mitarbeiter: " << _first_name << " " << _name;
            if (break_line) {
                cout << endl;
            }
        };
        void print() const {
            cout << "print() ohne Parameter;";
            cout << " Mitarbeiter: " << _first_name << " " << _name << endl;
        };
};

int main(int argc, char *argv[])
{
    Student stud_mustermann = Student("Mustermann", "Max");
    Employee empl_mustermann = Employee(stud_mustermann);
    Employee mit_default = Employee();
    stud_mustermann.print();
    stud_mustermann.print(true);
    empl_mustermann.print();
    mit_default.print();
    Student *p_stud_mustermann = nullptr;
    cout << "Block wird betreten" << endl;
    {
        p_stud_mustermann = new Student("Mustermann", "Markus");
        p_stud_mustermann->print(true);
    }
    cout << "Block wurde verlassen" << endl;
    delete p_stud_mustermann;
    return 0;
}