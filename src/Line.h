#ifndef LINE_H_
#define LINE_H_

#include "stdafx.h"
#include "Point.h"

// 'L' -> line;
// 'R' -> radio;
// 'S' -> segment;

class Line
{
public:
	Line();
	Line(char newType, double x1, double y1, double x2, double y2);
	char getType();
	double getA();
	double getB();
	double getC();
                double getSlope();
	Point  getP1();
	Point  getP2();

private:
	char type;
	Point p1;
	Point p2;
	double A;
	double B;
	double C;
                double slope;
};


#endif // !LINE_H_

