#include "Line.h"

Line::Line() :A(0), B(0), C(0), slope(0), type('L') {};
Line::Line(char newType, double x1, double y1, double x2, double y2) {
	type = newType;
	A = y1 - y2;
	B = x2 - x1;
	C = x1 * y2 - x2 * y1;
	p1.setXY(x1, y1);
	p2.setXY(x2, y2);
	if (x1 - x2 == 0) {
		slope = DBL_MAX;
	}
	else {
		slope = (y1 - y2) / (x1 - x2);
	}
}

char Line::getType() {
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

double Line::getSlope() {
    return slope;
}

Point Line::getP1() {
	return p1;
}

Point Line::getP2() {
	return p2;
}



