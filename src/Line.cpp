#include "Line.h"


Line::Line() :A(0), B(0), C(0) {};
Line::Line(lineType newType, double x1, double y1, double x2, double y2) {
	type = newType;
	A = y1 - y2;
	B = x2 - x1;
	C = x1 * y2 - x2 * y1;
	p1.setXY(x1, y1);
	p2.setXY(x2, y2);
}

lineType Line::getType() {
	return type;
}

double Line::getA() {
	return A;
}

double Line::getB() {
	return B;
}

double Line::getC() {
	return C;
}

Point Line::getP1() {
	return p1;
}

Point Line::getP2() {
	return p2;
}



