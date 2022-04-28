
#include <iostream>
#include <vector>
using namespace std;

class Point
{
	double x;
	double y;
public:
    // Konstruktor mit Parametern
	Point(double x = 0.0, double y = 0.0);
	// Verschiebt einen Punkt
	void move(double dx, double dy);
	// gibt den Punkt auf der Konsole aus
	void print(bool nl = true);
};

// Implementierung Konstruktor
Point::Point(double x, double y)
{
    this->x = x;
    this->y = y;
}

// Implementierung Methoden
void Point::move(double dx, double dy)
{
    this->x += dx;
    this->y += dy;
}

void Point::print(bool nl)
{
    cout << "(" << this->x << ", " << this->y << ")";
    if (nl)
        cout << endl;
}

class Polygonline{
    vector<Point> points;
public:
	// Konstruktor
	Polygonline();
	// Konstruktor mit Parameter
	Polygonline(Point& p);
	// gibt die Elemente des Polygons auf der Konsole aus
	void print(bool nl);
	// Hängt einen Punkt hinten an
	Polygonline& addPoint(Point p);
	// Hängt einen zusätzlichen Polygon hinten an
	void appendPolygonline(Polygonline& pl);
	// Verschiebt den gesamten Polygon
	void move(double dx, double dy);
};

// Implementierung Konstruktor
Polygonline::Polygonline(){}
Polygonline::Polygonline(Point& p)
{
    points.push_back(p);
}


// Implementierung Methoden
void Polygonline::print(bool nl=true)
{
    cout << '|';
    for (size_t i = 0; i < points.size(); i++) {
        points[i].print(false);
        if (i < points.size() - 1)
            cout << " - ";
    }
    cout << '|';
    if (nl)
        cout << endl;
}

Polygonline& Polygonline::addPoint(Point p)
{
    points.push_back(p);
    return *this;
}

void Polygonline::appendPolygonline(Polygonline& pl)
{
    for (size_t i = 0; i < pl.points.size(); i++) {
        points.push_back(pl.points[i]);
    }
}

void Polygonline::move(double dx, double dy)
{
    for (size_t i = 0; i < points.size(); i++) {
        points[i].move(dx, dy);
    }
}

int main(int argc, char *argv[]) 
{
	Point p1(1, 1), p2(2, 2), p3(3, 3), p4(4, 4), p5(5, 5);
	Polygonline l1;
	Polygonline l2(p3);
	cout << "Ausgabe 1:" << endl;
	l1.print();
	l2.print();
	l1.addPoint(p1).addPoint(p2);
	l2.addPoint(p4).addPoint(p5);
	cout << "Ausgabe 2:" << endl;
	l1.print();
	l2.print();
	p2.move(0.5, 0.5);
	cout << "Ausgabe 3:" << endl;
	p2.print();
	l1.print();
	l2.print();
	l1.appendPolygonline(l2);
	cout << "Ausgabe 4:" << endl;
	l1.print();
	l2.print();
	l1.move(0, 0.5);
	cout << "Ausgabe 5:" << endl;
	l1.print();
	l2.print();
	return 0;
}

