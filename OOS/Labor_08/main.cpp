
#include <iostream>
using namespace std;

class Point
{
private:
    double _x;
    double _y;

public:
    Point(double x = 0, double y = 0)
    {
        this->_x = x;
        this->_y = y;
    }

    void set_x(double x)
    {
        this->_x = x;
    }

    void set_y(double y)
    {
        this->_y = y;
    }

    double get_x()
    {
        return this->_x;
    }

    double get_y()
    {
        return this->_y;
    }

    void move(double dx, double dy)
    {
        this->_x += dx;
        this->_y += dy;
    }

    void print(bool newline = true)
    {
        cout << "(" << this->_x << ", " << this->_y << ")";
        if (newline)
            cout << endl;
    }
};

class Circle
{
private:
    Point _centre;
    double _radius;

public:
    Circle(Point centre = Point(), double radius = 1)
    {
        this->_centre = centre;
        this->_radius = radius;
    }

    void set_centre(Point centre)
    {
        this->_centre = centre;
    }

    void set_radius(double radius)
    {
        this->_radius = radius;
    }

    void move(double dx, double dy)
    {
        this->_centre.move(dx, dy);
    }

    void print()
    {
        cout << "[";
        this->_centre.print(false);
        cout << ", " << this->_radius << "]" << endl;
    }
};

// Hauptprogramm
int main(int argc, char *argv[])
{
    Point p;
    Circle c(p);
    cout << "Ausgabe 1:" << endl;
    p.print();
    c.print();
    p.set_x(1.1);
    p.set_y(2.2);
    c.set_centre(p);
    c.set_radius(3.3);
    cout << "Ausgabe 2:" << endl;
    p.print(false);
    cout << " == (" << p.get_x() << ", " << p.get_y() << ")"
         << endl;
    c.print();
    p.move(1.0, 1.0);
    c.move(2.0, 2.0);
    cout << "Ausgabe 3:" << endl;
    p.print();
    c.print();
    return 0;
}
