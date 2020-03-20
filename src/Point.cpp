#include "Point.h"
#include "pch.h"

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

bool Point::operator !=(const Point& p)const {
	return (doubleCmp(x, p.x) != 0 || doubleCmp(y, p.y) != 0);
}
Point Point:: operator -(const Point& p)const{
	 double x0 = x - ((Point) p).getX();
	 double y0 = y - ((Point) p).getY();
	 Point newP(x0,y0);
	 return newP;
}

double Point:: getX(){
	return x;
}

double Point:: getY(){
	return y;
}

void Point::setXY(double a,double b){
	x = a;
	y = b;
}

/*
double Point:: cross(Point p0, Point p1,Point p2){ 
	Point v1 = p1-p0;
	Point v2 = p2-p0;
	double x1 = v1.getX();
	double y1 = v1.getY();
	double x2 = v2.getX();
	double y2 = v2.getY();
	return (x1*y2-x2*y1);
}
 */


