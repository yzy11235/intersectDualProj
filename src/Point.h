#ifndef GRAPH_H_
#define GRAPH_H_

#include "def.h"
#include <iostream>
#include <fstream>
#include <set>
#include <vector>

class Point
{
public:
	Point();
	Point(double a, double b);
	bool operator < (const Point& p)const;
	bool operator ==(const Point& p)const;
	Point operator -(const Point& p)const;
	double getX();
	double getY();
	void setXY(double x, double y);
	//double cross(Point p1, Point p2, Point p3 ); //向量v1 与 向量v2的叉乘的数值

private:
	double x;
	double y;
};




    
#endif // !GLOBAL_H_

