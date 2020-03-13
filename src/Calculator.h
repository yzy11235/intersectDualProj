#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "def.h"
#include "Graph.h"
#include <vector>
#include <set>

using namespace std;

class Calculator
{
public:
	Calculator();
	int haveIntersection(Line l1, Line l2, set<Point>& nodeSet);
	int haveIntersection(Circle c, Line l, set<Point>& nodeSet);
	int haveIntersection(Circle c1, Circle c2, set<Point>& nodeSet);
	//计算全部交点
	int countAllinsect(vector<Line> lVec, vector<Circle> cVec, set<Point> &nodeSet);

};



#endif // !CALCULATOR_H_

