#ifndef CIRCLE_H_
#define CIRCLE_H_

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
