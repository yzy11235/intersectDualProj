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
	//�жϵ��Ƿ���line�� ��line����return true
	bool pOnLine(Point p, Line l);
	// Բ�� return true;  ����/����  return false;
	bool pInCircle(Point p, Circle c);
	// TODO: add slope class
	bool isParallel(Line l1, Line l2);//�ж������Ƿ�ƽ�� (����׽ �ص����쳣)	 
	int haveIntersection(Line l1, Line l2, set<Point>& nodeSet);
	int haveIntersection(Circle c, Line l, set<Point>& nodeSet);
	int haveIntersection(Circle c1, Circle c2, set<Point>& nodeSet);
	//����ȫ������
	int countAllinsect(vector<Line> lVec, vector<Circle> cVec, set<Point> &nodeSet);

};


#endif // !CALCULATOR_H_

