#include "Circle.h"

Circle::Circle() :X(0), Y(0), R(0) {};
Circle::Circle(double x, double y, double r) {
	X = x;
	Y = y;
	R = r;
}

double Circle::getX() {
	return X;
}

double Circle::getY() {
	return Y;
}

double Circle::getR() {
	return R;
}


