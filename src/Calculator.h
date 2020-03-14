#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "def.h"
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include <vector>
#include <set>

using namespace std;

class Calculator
{
public:
	Calculator();
	double crossMul();
	bool pOnLine(Point p, Line l);//判断点是否在line上

	int haveIntersection(Line l1, Line l2, set<Point>& nodeSet);
	int haveIntersection(Circle c, Line l, set<Point>& nodeSet);
	int haveIntersection(Circle c1, Circle c2, set<Point>& nodeSet);
	//计算全部交点
	int countAllinsect(vector<Line> lVec, vector<Circle> cVec, set<Point> &nodeSet);

};

//inline 函数？
// TODO finish it in the class Calculator above;
double xmult(Point v1, Point v2);
double xmult(Point o, Point a, Point b);


#endif // !CALCULATOR_H_

