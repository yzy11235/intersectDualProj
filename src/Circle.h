#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "stdafx.h"

class Circle
{
public:
	Circle();
	Circle(double x, double y, double r);
	double getX();
	double getY();
	double getR();

private:
	double X;
	double Y;
	double R;
};


#endif // !CIRCLE_H_
