#ifndef LINE_H_
#define LINE_H_

#include "Point.h"

// 'L' -> line;
// 'R' -> radio;
// 'S' -> segment;
enum lineType
{
	L,
	R,
	S
};

class Line
{
public:
	Line();
	Line(lineType newType, double x1, double y1, double x2, double y2);
	lineType getType();
	double getA();
	double getB();
	double getC();
	Point  getP1();
	Point  getP2();

private:
	lineType type;
	Point p1;
	Point p2;
	double A;
	double B;
	double C;
};


#endif // !LINE_H_

