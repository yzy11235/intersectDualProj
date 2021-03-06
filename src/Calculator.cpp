#include "Calculator.h"
#include "Exception.h"
#include <iterator>

using namespace std;


Calculator::Calculator() {}

inline double Calculator::xmult(Point v1, Point v2) {
	return (v1.getX() * v2.getY() - v1.getY() * v2.getX());
}

double Calculator::xmult(Point o, Point a, Point b) {
	return (a.getX() - o.getX())
		* (b.getY() - o.getY()) - (b.getX() - o.getX())
		* (a.getY() - o.getY());
}

bool Calculator::isParallel(Line l1, Line l2) {
	if (doubleCmp(l1.getSlope(), l2.getSlope()) == 0) {
		Point p11 = l1.getP1();
		Point p12 = l1.getP2();
		Point p21 = l2.getP1();
		Point p22 = l2.getP2();
		Line line('L', p11.getX(), p11.getY(), p12.getX(), p12.getY());
		// 重合
		if (pOnLine(p21, line)) {
			if (l1.getType() == 'L' || l2.getType() == 'L') {
				throw lineException(LINE_INFINITE_INTERSECT);
			}
			else if ((l1.getType() == 'R' || l2.getType() == 'R')
				&& (pOnLine(p11, l2) || pOnLine(p21, l1))) {
				throw lineException(LINE_INFINITE_INTERSECT);
			}
			else if (l1.getType() == 'S' && l2.getType() == 'S') {
				if (p11 == p21 || p11 == p22 || p12 == p21 || p12 == p22) {
					// 排除端点重合的情况
					if ((p11 == p21 || p11 == p22) && (p12 == p21 || p12 == p22)) {
						throw lineException(LINE_INFINITE_INTERSECT);
					}
					else if (p11 == p21 && (pOnLine(p12, l2) || pOnLine(p22, l1))) {
						throw lineException(LINE_INFINITE_INTERSECT);
					}
					else if (p11 == p22 && (pOnLine(p12, l2) || pOnLine(p21, l1))) {
						throw lineException(LINE_INFINITE_INTERSECT);
					}
					else if (p12 == p21 && (pOnLine(p11, l2) || pOnLine(p22, l1))) {
						throw lineException(LINE_INFINITE_INTERSECT);
					}
					else if (p12 == p22 && (pOnLine(p11, l2) || pOnLine(p21, l1))) {
						throw lineException(LINE_INFINITE_INTERSECT);
					}
				}
				else if (pOnLine(p11, l2) || pOnLine(p12, l2)
					|| pOnLine(p21, l1) || pOnLine(p22, l1)) {
					throw lineException(LINE_INFINITE_INTERSECT);
				}
			}
		}
		return true;
	}
	return false;
}

bool Calculator::pOnLine(Point p, Line l) {
	if (doubleCmp(l.getA() * p.getX() + l.getB() * p.getY() + l.getC(), 0) == 0) {
		//if (doubleCmp(xmult(v1, v2), 0) == 0) {
		Point p1 = l.getP1();
		Point p2 = l.getP2();
		Point v1 = p1 - p;
		Point v2 = p2 - p;
		char type = l.getType();
		if (type == 'L') {//直线           
			return true;
		}
		else if (type == 'S') {
			if (doubleCmp(v1.getX() * v2.getX(), 0) <= 0
				&& doubleCmp(v1.getY() * v2.getY(), 0) <= 0) {
				return true;
			}
		}
		else if (type == 'R') {
			Point r = p1 - p2;
			if (doubleCmp(r.getX() * v1.getX(), 0) >= 0
				&& doubleCmp(r.getY() * v1.getY(), 0) >= 0) {
				return true;
			}
		}
	}
	return false;
}

bool Calculator::pInCircle(Point p, Circle c) {
	double x = p.getX();
	double y = p.getY();
	double x0 = c.getX();
	double y0 = c.getY();
	double r = c.getR();
	double t = (x - x0) * (x - x0) + (y - y0) * (y - y0) - r * r;
	return (doubleCmp(t, 0) < 0);
}

int Calculator::haveIntersection(Line l1, Line l2, set<Point>& nodeSet) {
	double A1 = l1.getA();
	double B1 = l1.getB();
	double C1 = l1.getC();
	double A2 = l2.getA();
	double B2 = l2.getB();
	double C2 = l2.getC();
	double den = A1 * B2 - A2 * B1;
	if (isParallel(l1, l2) == true) {
		return 0;
	}
	double num1 = B1 * C2 - B2 * C1;
	double num2 = A2 * C1 - A1 * C2;
	Point  node(num1 / den, num2 / den);
	if (pOnLine(node, l1) && pOnLine(node, l2)) {
		nodeSet.insert(node);
		//cout << "one node line and line!" << endl;
		return 1;
	}
	return 0;
}

// 先算交点，再判断交点是否在线上；
int Calculator::haveIntersection(Circle c, Line l, set<Point>& nodeSet) {
	double A = l.getA();
	double B = l.getB();
	double C = l.getC();
	Point p1 = l.getP1();
	Point p2 = l.getP2();
	char type = l.getType();
	if (type == 'S' && pInCircle(p1, c) && pInCircle(p2, c)) {//线段的两端点都在圆内
		return 0;
	}
	double X = c.getX();
	double Y = c.getY();
	double R = c.getR();
	double  den = A * A + B * B;
	double d = abs(A * X + B * Y + C) / sqrt(den);
	if (d - R > EPS) {
		return 0;
	}
	else {
		double x0 = (B * B * X - A * B * Y - A * C) / (den);
		double y0 = (A * A * Y - A * B * X - B * C) / (den);
		if (doubleCmp(d, R) == 0) { //相切
			Point node(x0, y0);
			if (pOnLine(node, l)) {
				nodeSet.insert(node);
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			int count = 0;
			double a = sqrt(R * R - d * d);
			if (B == 0) {
				Point node1(x0, y0 + a);
				Point node2(x0, y0 - a);
				if (pOnLine(node1, l)) {
					nodeSet.insert(node1);
					count++;
				}
				if (pOnLine(node2, l)) {
					nodeSet.insert(node2);
					count++;
				}
			}
			else {
				double k = -A / B;
				double cos = abs(B) / sqrt(den);
				double sin = k * abs(B) / sqrt(den);
				Point node1(x0 + a * cos, y0 + a * sin);
				Point node2(x0 - a * cos, y0 - a * sin);
				if (pOnLine(node1, l)) {
					nodeSet.insert(node1);
					count++;
				}
				if (pOnLine(node2, l)) {
					nodeSet.insert(node2);
					count++;
				}
			}
			return count;
		}
	}
}


int Calculator::haveIntersection(Circle c1, Circle c2, set<Point>& nodeSet) {
	double a1 = c1.getX();
	double b1 = c1.getY();
	double r1 = c1.getR();
	double a2 = c2.getX();
	double b2 = c2.getY();
	double r2 = c2.getR();
	if (doubleCmp(a1, a2) == 0 && doubleCmp(b1, b2) == 0 && doubleCmp(r1, r2) == 0) {
		throw CircleException(CIRCLE_INFINITE_INTERSECT);
	}

	double r11 = r1 * r1;
	double a11 = a1 * a1;
	double b11 = b1 * b1;
	double r22 = r2 * r2;
	double a22 = a2 * a2;
	double b22 = b2 * b2;

	double r12 = r1 * r2;
	double a12 = a1 * a2;
	double b12 = b1 * b2;

	double subs1 = a11 - 2 * a12 + a22 + b11 - 2 * b12 + b22;

	double subs2 = -r11 * a1 + r11 * a2 + r22 * a1 - r22 * a2 + a11 * a1
		- a11 * a2 - a1 * a22 + a1 * b11 - 2 * a1 * b12 + a1 * b22
		+ a22 * a2 + a2 * b11 - 2 * a2 * b12 + a2 * b22;
	double subs3 = -r11 * b1 + r11 * b2 + r22 * b1 - r22 * b2 + a11 * b1
		+ a11 * b2 - 2 * a12 * b1 - 2 * a12 * b2 + a22 * b1
		+ a22 * b2 + b11 * b1 - b11 * b2 - b1 * b22 + b22 * b2;

	double s = (r11 + 2 * r12 + r22 - subs1) * (-r11 + 2 * r12 - r22 + subs1);
	if (s < 0 || subs1 == 0) {
		return 0;
	}
	else if (s == 0) {
		Point node(subs2 / (2 * subs1), subs3 / (2 * subs1));
		nodeSet.insert(node);
		return 1;
	}
	else {
		double sigma = sqrt(s);
		double dx = sigma * (b1 - b2);
		double dy = sigma * (a2 - a1);
		double x1 = (subs2 - dx) / (2 * subs1);
		double y1 = (subs3 - dy) / (2 * subs1);
		Point  node1(x1, y1);
		nodeSet.insert(node1);
		double x2 = (subs2 + dx) / (2 * subs1);
		double y2 = (subs3 + dy) / (2 * subs1);
		Point  node2(x2, y2);
		nodeSet.insert(node2);
		return 2;
	}
}


int Calculator::countAllinsect(vector<Line> lVec, vector<Circle> cVec, set<Point>& nodeSet) {
	Line l1, l2;
	Circle c1, c2;
	for (auto iterI = lVec.begin(); iterI != lVec.end(); iterI++) {
		l1 = (Line)* iterI;
		for (auto iterJ = iterI + 1; iterJ < lVec.end(); iterJ++) {
			l2 = (Line)* iterJ;
			haveIntersection(l1, l2, nodeSet);
		}
	}

	for (auto iterI = cVec.begin(); iterI != cVec.end(); iterI++) {
		for (auto iterJ = lVec.begin(); iterJ != lVec.end(); iterJ++) {
			haveIntersection((Circle)* iterI, (Line)* iterJ, nodeSet);
		}
	}

	for (auto iterI = cVec.begin(); iterI != cVec.end(); iterI++) {
		for (auto iterJ = iterI + 1; iterJ != cVec.end(); iterJ++) {
			haveIntersection((Circle)* iterI, (Circle)* iterJ, nodeSet);
		}
	}
	return (int)nodeSet.size();
}
