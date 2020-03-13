#include "Graph.h"

using namespace std;

Point::Point():x(0),y(0) {}
Point::Point(double a, double b)
{
    x = a;
    y = b;
}

bool Point::operator < (const Point& p)const {
    //return x==p.x?y<p.y:x<p.x;
    return (doubleCmp(x, p.x) == 0 ? 
		doubleCmp(y, p.y) < 0 : doubleCmp(x, p.x) < 0);

}

bool Point::operator ==(const Point& p)const {
    return (doubleCmp(x, p.x) == 0 && doubleCmp(y, p.y) == 0);
}
 

Line::Line() :A(0), B(0), C(0) {};
Line::Line(double x1, double y1, double x2, double y2) {
	A = y1 - y2;
	B = x2 - x1;
	C = x1 * y2 - x2 * y1;
}


Circle::Circle() :X(0), Y(0), R(0) {};
Circle::Circle(double x, double y, double r) {
	X = x;
	Y = y;
	R = r;
}
