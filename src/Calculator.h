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
	inline double xmult(Point v1, Point v2);
	double xmult(Point o, Point a, Point b);
	//判断点是否在line上 在line上则return true
	bool pOnLine(Point p, Line l);
	// 圆内 return true;  相切/相离  return false;
	bool pInCircle(Point p, Circle c);
	// TODO: add slope class
	bool isParallerl(Line l1, Line l2);//判断两线是否平行 (并捕捉 重叠的异常)	 
	int haveIntersection(Line l1, Line l2, set<Point>& nodeSet);
	int haveIntersection(Circle c, Line l, set<Point>& nodeSet);
	int haveIntersection(Circle c1, Circle c2, set<Point>& nodeSet);
	//计算全部交点
	int countAllinsect(vector<Line> lVec, vector<Circle> cVec, set<Point> &nodeSet);

};


#endif // !CALCULATOR_H_

