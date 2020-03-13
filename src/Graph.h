#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "def.h"
#include <iostream>
#include <fstream>
#include <set>
#include <vector>

class Point
{
public:
	double x;
	double y;

	Point();
	Point(double a, double b);
	bool operator < (const Point& p)const;
	bool operator ==(const Point& p)const;

};

class Line 
{
public:
	double A;
	double B;
	double C;
	// TODO: boundaries for lines;

	Line();
	Line(double x1, double y1, double x2, double y2);

};

class Circle 
{
public:
	double X;
	double Y;
	double R;

	Circle();
	Circle(double x, double y, double r);

};



#endif // !GLOBAL_H_

