#include "pch.h"
#include "CppUnitTest.h"
#include "..\Intersect\Calculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace intersectTest
{

	TEST_CLASS(PointTest)
	{
	public:
		TEST_METHOD(TestLessAndEql)
		{
			Point p1(2.99999999999999, 4.00000000000002);
			Point p2(3, 4);
			Point p3(2.0001, 5);
			Point p4(2.00005, 10);
			Point p5(-0.00000000001, -1.0000000000002);
			Point p6(0, -1);
			Point p7(1.000000000099, 2.234344);
			Point p8(1.000000000008, 2.4535356);

			// test get;
			Assert::IsTrue(p1.getX() == 2.99999999999999);
			Assert::IsTrue(p1.getY() == 4.00000000000002);
			Assert::IsTrue(p5.getY() == -1.0000000000002);
			Assert::IsFalse(p2.getY() == 2.99999999999999);
			Assert::IsFalse(p1.getX() == p2.getX());
			Assert::IsFalse(p1.getY() == p2.getY());
			Assert::IsFalse(p5.getX() == p6.getX());
			Assert::IsFalse(p5.getY() == p6.getY());
			Assert::IsFalse(p7.getX() == p8.getX());

			// test < & == ;
			Assert::IsFalse(p1 < p2);
			Assert::IsFalse(p2 < p1);
			Assert::IsTrue(p1 == p2);
			Assert::IsFalse(p5 < p6);
			Assert::IsFalse(p6 < p5);
			Assert::IsTrue(p5 == p6);
			Assert::IsTrue(p4 < p3);
			Assert::IsFalse(p3 < p4);
			Assert::IsTrue(p7 < p8);
			Assert::IsFalse(p8 < p7);

			// test -  ;
			Point p1Sub2(2.99999999999999 - 3, 0.00000000000002);
			Assert::IsTrue(p1Sub2 == p1 - p2);
			Assert::IsFalse(p2 == p1 - p3);
			Point p7Subp8(1.000000000099 - 1.000000000008, 2.234344 - 2.4535356);
			Assert::IsTrue(p7Subp8 == p7 - p8);
			Point p5Sub6(-0.00000000001, -1.0000000000002 + 1);
			Assert::IsTrue(p5Sub6 == p5 - p6);

			// test setXY
			p1.setXY(3, 4);
			p3.setXY(2.00005, 10);
			p5.setXY(0, -1);
			p7.setXY(1.000000000008, 2.4535356);
			Assert::IsTrue(p1 == p2);
			Assert::IsTrue(p3 == p4);
			Assert::IsTrue(p5 == p6);
			Assert::IsTrue(p7 == p8);

		}
	};

	TEST_CLASS(LineTest) {
public:
	TEST_METHOD(lineTestBasic) {
		Line l1('L', 1, 1, 2, 2);
		Line l2('R', 0, 2, 1, 0);
		Line l3('S', 1, 0, 5, 0);

		// test getType
		Assert::IsTrue(l1.getType() == 'L');
		Assert::IsTrue(l2.getType() == 'R');
		Assert::IsTrue(l3.getType() == 'S');

		// test get abc
		Assert::IsTrue((l1.getA() == 1 && l1.getB() == -1) ||
			(l1.getA() == -1 && l1.getB() == 1)
			&& l1.getC() == 0);
		Assert::IsTrue((l2.getA() == -2 && l2.getB() == -1 && l2.getC() == 2) ||
			(l2.getA() == 2 && l2.getB() == 1 && l2.getC() == -2));

		// test get p1 p2;
		Point p1(1, 1);
		Point p2(1, 0);
		Point p3(5, 0);
		Assert::IsTrue(l1.getP1() == p1);
		Assert::IsTrue(l2.getP2() == p2);
		Assert::IsTrue(l3.getP2() == p3);

	}
	};

	TEST_CLASS(CircleTest) {
public:
	TEST_METHOD(circleTestBasic) {
		Circle c1(1, -2, 5);
		// test xyr
		Assert::IsTrue(c1.getR() == 5);
		Assert::IsTrue(c1.getX() == 1);
		Assert::IsTrue(c1.getY() == -2);
	}
	};

	TEST_CLASS(CalBasicTest) {
public:
	TEST_METHOD(xmulPoint) {
		Point v1(1, 1);
		Point v2(-3, -5);
		Point v3(-569, -2262);
		Point v4(-42, 1074);
		Point v5(196, 5619);

		// xmul 2points test
		Calculator* calc = new Calculator();
		Assert::IsTrue(calc->xmult(v1, v2) == -2);
		Assert::IsTrue(calc->xmult(v2, v4) == -3432);
		Assert::IsTrue(calc->xmult(v3, v4) == -706110);

		// xmul 3 points test
		Point o(1, 2);
		Point a(3, 5);
		Point b(4, -1);
		Assert::IsTrue(calc->xmult(o, a, b) == -15);
		Assert::IsTrue(calc->xmult(v1, v2, v3) == 5632);
		Assert::IsTrue(calc->xmult(v2, v3, v4) == -698737);
		Assert::AreEqual(calc->xmult(v3, v4, v5), (double) 1601247);
	}

	TEST_METHOD(onLineTest) {
		Calculator* calc = new Calculator();
		char line = 'L';
		char radio = 'R';
		char segment = 'S';
		Line l(line, 7, 10, 9, 100);
		Line rUp(radio, 7, 10, 9, 100);
		Line rDown(radio, 9, 100, 7, 10);
		Line s(segment, 7, 10, 9, 100);
		Point pDown(6, -35);
		Point p1(7, 10);
		Point pMid(8, 55);
		//Point pMidOut1(8, 55.00000000001);
		// 精度，小数点后十位
		Point pMidOut1(8, 55.0000000001);
		Point pMidOut2(7.9999999999, 55);
		Point p2(9, 100);
		Point pUp(10, 145);
		Point pUpOut(9, 10000);
		Assert::IsTrue(calc->pOnLine(pDown, l));
		Assert::IsTrue(calc->pOnLine(pDown, rUp) == false);
		Assert::IsTrue(calc->pOnLine(pDown, rDown));
		Assert::IsTrue(calc->pOnLine(pDown, s) == false);

		Assert::IsTrue(calc->pOnLine(p1, l));
		Assert::IsTrue(calc->pOnLine(p1, rUp));
		Assert::IsTrue(calc->pOnLine(p1, rDown));
		Assert::IsTrue(calc->pOnLine(p1, s));

		Assert::IsTrue(calc->pOnLine(pMid, l));
		Assert::IsTrue(calc->pOnLine(pMid, rUp));
		Assert::IsTrue(calc->pOnLine(pMid, rDown));
		Assert::IsTrue(calc->pOnLine(pMid, s));

		Assert::IsTrue(calc->pOnLine(pMidOut1, l) == false);
		Assert::IsTrue(calc->pOnLine(pMidOut1, rUp) == false);
		Assert::IsTrue(calc->pOnLine(pMidOut1, rDown) == false);
		Assert::IsTrue(calc->pOnLine(pMidOut1, s) == false);

		Assert::IsTrue(calc->pOnLine(pMidOut2, l) == false);
		Assert::IsTrue(calc->pOnLine(pMidOut2, rUp) == false);
		Assert::IsTrue(calc->pOnLine(pMidOut2, rDown) == false);
		Assert::IsTrue(calc->pOnLine(pMidOut2, s) == false);

		Assert::IsTrue(calc->pOnLine(p2, l));
		Assert::IsTrue(calc->pOnLine(p2, rUp));
		Assert::IsTrue(calc->pOnLine(p2, rDown));
		Assert::IsTrue(calc->pOnLine(p2, s));

		Assert::IsTrue(calc->pOnLine(pUp, l));
		Assert::IsTrue(calc->pOnLine(pUp, rUp));
		Assert::IsTrue(calc->pOnLine(pUp, rDown) == false);
		Assert::IsTrue(calc->pOnLine(pUp, s) == false);

		Assert::IsTrue(calc->pOnLine(pUpOut, l) == false);
		Assert::IsTrue(calc->pOnLine(pUpOut, rUp) == false);
		Assert::IsTrue(calc->pOnLine(pUpOut, rDown) == false);
		Assert::IsTrue(calc->pOnLine(pUpOut, s) == false);

		// TD & RL
		Line sTD(segment, 0, 1, 0, 100);
		Line rTD(radio, 0, -1, 0, 8);
		Line sRL(segment, 0, 1, 5, 1);
		Line rRL(radio, 0, 1, 3, 1);
		Point tdOut(0, -2);
		Point tdIn(0, 99);
		Point rlOut(-1, 1);
		Point rlIn(5, 1);
		Assert::IsTrue(calc->pOnLine(tdIn, sTD));
		Assert::IsFalse(calc->pOnLine(tdOut, sTD));
		Assert::IsTrue(calc->pOnLine(tdIn, rTD));
		Assert::IsFalse(calc->pOnLine(tdOut, rTD));
		Assert::IsFalse(calc->pOnLine(rlOut, sRL));
		Assert::IsTrue(calc->pOnLine(rlIn, sRL));
		Assert::IsFalse(calc->pOnLine(rlOut, rRL));
		Assert::IsTrue(calc->pOnLine(rlIn, rRL));
	}

	TEST_METHOD(inCircleTest) {
		Circle cBase(0, 0, 5);
		Point pIn1(0, 0);
		Point pIn2(2.999999, 4);
		Point pEdge(3, 4);
		Point pOut1(3.00000001, 4);
		Point pOut2(-3, -4.0000000000001);
		Calculator* cal = new Calculator();
		Assert::IsTrue(cal->pInCircle(pIn1, cBase));
		Assert::IsTrue(cal->pInCircle(pIn2, cBase));
		Assert::IsTrue(cal->pInCircle(pEdge, cBase) == false);
		Assert::IsTrue(cal->pInCircle(pOut1, cBase) == false);
		Assert::IsTrue(cal->pInCircle(pOut2, cBase) == false);
	}

	};

	TEST_CLASS(CalLAndLTest)
	{
	public:
		// test parallel
		TEST_METHOD(LinePrl)
		{
			Calculator* calc = new Calculator();
			char line = 'L';
			char radio = 'R';
			char segment = 'S';
			Line lTD(line, 1, 3, 2, 3);
			Line rTD(radio, 2, 5, 4, 5);
			Line sTD(segment, 51, 6, 24, 6);
			Calculator* cal = new Calculator();
			Assert::IsTrue(cal->isParallerl(lTD, rTD));
			Assert::IsTrue(cal->isParallerl(lTD, sTD));
			Assert::IsTrue(cal->isParallerl(rTD, sTD));

			Line l1(line, 3, 3, 5, 5);
			Line r1(radio, 6, 5, -100, -101);
			Line s1(segment, 0, 1, 100, 101);
			Assert::IsTrue(cal->isParallerl(l1, r1));
			Assert::IsTrue(cal->isParallerl(l1, s1));
			Assert::IsTrue(cal->isParallerl(r1, s1));
			Assert::IsFalse(cal->isParallerl(l1, sTD));
			Assert::IsFalse(cal->isParallerl(r1, sTD));
			Assert::IsFalse(cal->isParallerl(s1, rTD));
		}

		// TODO: function unfinished 
		TEST_METHOD(lineOverlap) {
			Line L1('L', 3, 5, 3, 9);
			Line L2('L', 3, 6, 3, 9);

			Line R1('R', 3, 7, 3, 10);
			Line R2('R', 3, 8, 3, 100);

			Line S1('S', 3, 5, 3, 10);
			Line S2('S', 3, 7, 3, 11);


		}

		//两条line的测试
		TEST_METHOD(lineParCount) {
			Calculator* calc = new Calculator();
			char line = 'L';
			char radio = 'R';
			char segment = 'S';
			Line lTD(line, 1, 3, 2, 3);
			Line rTD(radio, 2, 5, 4, 5);
			set<Point> nodeSet1;
			calc->haveIntersection(lTD, rTD, nodeSet1);
			Assert::AreEqual(nodeSet1.size(), (size_t)0);

			Line line12(radio, 3, 1, 3, 2);
			Line line22(segment, 2, 1, 2, 10);
			set<Point> nodeSet2;
			calc->haveIntersection(line12, line22, nodeSet2);
			Assert::AreEqual(nodeSet2.size(), (size_t)0);

			Line line13(line, 1, 1, 2, 2);
			Line line23(segment, 1, 2, 2, 3);
			set<Point> nodeSet3;
			calc->haveIntersection(line13, line23, nodeSet3);
			Assert::AreEqual(nodeSet3.size(), (size_t)0);

			//线段相离
			Line  s1('S', 0, 0, 4, 4);
			Line  s2('S', 0, 3, 2, 3);
			set<Point> nodeSet4;
			calc->haveIntersection(s1, s2, nodeSet4);
			Assert::AreEqual(nodeSet4.size(), (size_t)0);

			//射线相离
			Line r1('S', 0, 0, 1, 2);
			Line r2('S', 1, 1, 3, -10);
			set<Point> nodeSet5;
			calc->haveIntersection(r1, r2, nodeSet5);
			Assert::AreEqual(nodeSet5.size(), (size_t)0);

			//线段相交于端点
			Line s3('S', 0, 0, -1, 1);
			set<Point>nodeSet6;
			calc->haveIntersection(s1, s3, nodeSet6);
			Assert::AreEqual(nodeSet6.size(), (size_t)1);

			Line s4('S', 3, 3, 0, 1);
			set<Point>nodeSet7;
			calc->haveIntersection(s1, s4, nodeSet7);
			Assert::AreEqual(nodeSet7.size(), (size_t)1);

			//射线相交于端点
			Line r3('R', 0, 0, -2, -3);
			set<Point> nodeSet8;
			calc->haveIntersection(r1, r3, nodeSet8);
			Assert::AreEqual(nodeSet6.size(), (size_t)1);
		}


		// 多线相交于一点
		TEST_METHOD(LineCrossOne) {
			Calculator* calc = new Calculator();
			char line = 'L';
			char radio = 'R';
			char segment = 'S';
			int n = 3;
			Line line1(line, 1, 3, 2, 3);
			Line line2(line, 1, 3, 4, 5);
			Line line3(line, 1, 3, 10, 1);
			Line r1(radio, 0, 0, 1, 3);
			Line s1(segment, 1, 0, 1, 3);
			vector<Line> lvec;
			lvec.push_back(line1);
			lvec.push_back(line2);
			lvec.push_back(line3);
			lvec.push_back(r1);
			lvec.push_back(s1);
			set<Point> nodeSet;
			size_t i, j;
			for (i = 0; i < lvec.size(); i++) {
				for (j = i + 1; j < lvec.size(); j++) {
					calc->haveIntersection(lvec[i], lvec[j], nodeSet);
				}
			}
			Assert::AreEqual(nodeSet.size(), (size_t)1);
		}

		// line cross line regression test 2
		TEST_METHOD(LineCross2) {
			Calculator* calc = new Calculator();
			char line = 'L';
			char radio = 'R';
			char segment = 'S';
			Line line1(line, 0, 0, 2, 3);
			Line line2(line, 0, 0, 3, -5);
			Line line3(line, 5, 3, 5, 1);
			Line line4(line, 0, 200, 1, 200);
			vector<Line> lvec;
			lvec.push_back(line1);
			lvec.push_back(line2);
			lvec.push_back(line3);
			lvec.push_back(line4);
			set<Point> nodeSet;
			size_t i, j;
			for (i = 0; i < lvec.size(); i++) {
				for (j = i + 1; j < lvec.size(); j++) {
					calc->haveIntersection(lvec[i], lvec[j], nodeSet);
				}
			}
			Assert::AreEqual(nodeSet.size(), (size_t)6);
		}

		//随意组合
		TEST_METHOD(lineAllType1) {
			Calculator* calc = new Calculator();
			Line l1('L', -100, 14, 200, 14);
			Line l2('L', -3, 8, 5, 10);
			Line l3('L', -2, 4, 5, 8);
			Line s1('S', -4, 5, 2, 8);
			Line s2('S', 1, 3, 4, 9);
			Line s3('S', 5, 8, 5, 10);
			Line r1('R', 2, 8, 4, 12);
			Line r2('R', -4, 5, -2, 2);
			Line r3('R', 3, 12, 5, 8);
			vector<Line> lvec;
			lvec.push_back(l1);
			lvec.push_back(l2);
			lvec.push_back(l3);
			lvec.push_back(s1);
			lvec.push_back(s2);
			lvec.push_back(s3);
			lvec.push_back(r1);
			lvec.push_back(r2);
			lvec.push_back(r3);
			set<Point> nodeSet;
			size_t i, j;
			for (i = 0; i < lvec.size(); i++) {
				for (j = i + 1; j < lvec.size(); j++) {
					calc->haveIntersection(lvec[i], lvec[j], nodeSet);
				}
			}
			Assert::AreEqual(nodeSet.size(), (size_t)14);

		}
	};

	TEST_CLASS(CalLAndCTest)
	{
	public:
		//直线与圆的测试
		TEST_METHOD(LCtagency)
		{
			Calculator* calc = new Calculator();
			char line = 'L';
			Line line1(line, 1, 0, 1, 4);
			Line line2(line, 0, 1, 2, 1);
			Circle c(0, 0, 1);
			vector<Line> lvec;
			vector<Circle> cvec;
			lvec.push_back(line1);
			lvec.push_back(line2);
			cvec.push_back(c);
			set<Point> nodeSet;
			size_t i, j;
			for (i = 0; i < cvec.size(); i++) {
				for (j = 0; j < lvec.size(); j++) {
					calc->haveIntersection(cvec[i], lvec[j], nodeSet);
				}
			}
			Assert::AreEqual(nodeSet.size(), (size_t)2);
			//<0,1> <1,0>
			Point p1(0, 1);
			Point p2(1, 0);
			Assert::AreEqual(nodeSet.count(p1), (size_t)1);
			Assert::AreEqual(nodeSet.count(p2), (size_t)1);
		}

		TEST_METHOD(LCseparat)
		{
			Calculator* calc = new Calculator();
			char line = 'L';
			Line line1(line, 0, 9, 10, 0);
			Line line2(line, 0, -11, 20, -3);
			Circle c(0, 0, 1);
			vector<Line> lvec;
			vector<Circle> cvec;
			lvec.push_back(line1);
			lvec.push_back(line2);
			cvec.push_back(c);
			set<Point> nodeSet;
			size_t i, j;
			for (i = 0; i < cvec.size(); i++) {
				for (j = 0; j < lvec.size(); j++) {
					calc->haveIntersection(cvec[i], lvec[j], nodeSet);
				}
			}

			Assert::AreEqual(nodeSet.size(), (size_t)0);
			//<0,1> <1,0>
		}

		TEST_METHOD(LCintersect)
		{
			Calculator* calc = new Calculator();
			char line = 'L';
			Line line1(line, 2, 0, 0, 2);
			Line line2(line, -1, 0, -1, 100);
			Line line3(line, 100, -1, 1000, -1);
			Circle c(0, 0, 2);
			vector<Line> lvec;
			vector<Circle> cvec;
			lvec.push_back(line1);
			lvec.push_back(line2);
			lvec.push_back(line3);
			cvec.push_back(c);
			set<Point> nodeSet;
			size_t i, j;
			for (i = 0; i < cvec.size(); i++) {
				for (j = 0; j < lvec.size(); j++) {
					calc->haveIntersection(cvec[i], lvec[j], nodeSet);
				}
			}
			Assert::AreEqual(nodeSet.size(), (size_t)6);
			//<0,1> <1,0>
			Point p1(0, 2);
			Point p2(2, 0);
			Point p3(-1, sqrt(3));
			Point p4(-1, -sqrt(3));
			Point p5(-sqrt(3), -1);
			Point p6(sqrt(3), -1);
			Assert::AreEqual(nodeSet.count(p1), (size_t)1);
			Assert::AreEqual(nodeSet.count(p2), (size_t)1);
			Assert::AreEqual(nodeSet.count(p3), (size_t)1);
			Assert::AreEqual(nodeSet.count(p4), (size_t)1);
			Assert::AreEqual(nodeSet.count(p5), (size_t)1);
			Assert::AreEqual(nodeSet.count(p6), (size_t)1);
		}

		//射线与圆的测试
		TEST_METHOD(RCtagency)
		{
			Calculator* calc = new Calculator();
			Line line1('R', 1, 0, 1, 4);
			Line line2('R', 0, 1, 2, 1);
			Line line3('R', -1, -1, 1, -1);
			Circle c(0, 0, 1);
			vector<Line> lVec;
			vector<Circle> cVec;
			lVec.push_back(line1);
			lVec.push_back(line2);
			lVec.push_back(line3);
			cVec.push_back(c);
			set<Point> nodeSet;
			for (auto iterI = cVec.begin(); iterI != cVec.end(); iterI++) {
				for (auto iterJ = lVec.begin(); iterJ != lVec.end(); iterJ++) {
					calc->haveIntersection((Circle)* iterI, (Line)* iterJ, nodeSet);
				}
			}
			Assert::AreEqual(nodeSet.size(), (size_t)3);
			//<0,1> <1,0>
			Point p1(0, 1);
			Point p2(1, 0);
			Point p3(0, -1);
			Assert::AreEqual(nodeSet.count(p1), (size_t)1);
			Assert::AreEqual(nodeSet.count(p2), (size_t)1);
			Assert::AreEqual(nodeSet.count(p3), (size_t)1);
		}

		TEST_METHOD(RCseparat)
		{
			Calculator* calc = new Calculator();
			Line line1('R', 1, 1, 3, 3);
			Line line2('R', 0, -11, 20, -3);
			Circle c(0, 0, 1);
			vector<Line> lvec;
			vector<Circle> cvec;
			lvec.push_back(line1);
			lvec.push_back(line2);
			cvec.push_back(c);
			set<Point> nodeSet;
			size_t i, j;
			for (i = 0; i < cvec.size(); i++) {
				for (j = 0; j < lvec.size(); j++) {
					calc->haveIntersection(cvec[i], lvec[j], nodeSet);
				}
			}

			Assert::AreEqual(nodeSet.size(), (size_t)0);
		}

		TEST_METHOD(RCintersect)
		{
			Calculator* calc = new Calculator();

			Line line1('R', 0, 0, 0, 2);
			Line line2('R', -1, 0, -1, 100);
			Line line3('R', 100, -1, -1000, -1);
			Circle c(0, 0, 2);
			vector<Line> lvec;
			vector<Circle> cvec;
			lvec.push_back(line1);
			lvec.push_back(line2);
			lvec.push_back(line3);
			cvec.push_back(c);
			set<Point> nodeSet;
			size_t i, j;
			for (i = 0; i < cvec.size(); i++) {
				for (j = 0; j < lvec.size(); j++) {
					calc->haveIntersection(cvec[i], lvec[j], nodeSet);
				}
			}
			Assert::AreEqual(nodeSet.size(), (size_t)4);
			//<0,1> <1,0>
			Point p1(0, 2);
			Point p3(-1, sqrt(3));
			Point p5(-sqrt(3), -1);
			Point p6(sqrt(3), -1);
			Assert::AreEqual(nodeSet.count(p1), (size_t)1);
			Assert::AreEqual(nodeSet.count(p3), (size_t)1);
			Assert::AreEqual(nodeSet.count(p5), (size_t)1);
			Assert::AreEqual(nodeSet.count(p6), (size_t)1);
		}

		//线段与圆的关系
		TEST_METHOD(SCtagency)
		{
			Calculator* calc = new Calculator();
			Line line1('S', 1, 0, 1, 4);
			Line line2('S', -1, 1, 2, 1);
			Circle c(0, 0, 1);
			vector<Line> lvec;
			vector<Circle> cvec;
			lvec.push_back(line1);
			lvec.push_back(line2);
			cvec.push_back(c);
			set<Point> nodeSet;
			size_t i, j;
			for (i = 0; i < cvec.size(); i++) {
				for (j = 0; j < lvec.size(); j++) {
					calc->haveIntersection(cvec[i], lvec[j], nodeSet);
				}
			}
			Assert::AreEqual(nodeSet.size(), (size_t)2);
			//<0,1> <1,0>
			Point p1(0, 1);
			Point p2(1, 0);
			Assert::AreEqual(nodeSet.count(p1), (size_t)1);
			Assert::AreEqual(nodeSet.count(p2), (size_t)1);
		}

		TEST_METHOD(SCseparat)
		{
			Calculator* calc = new Calculator();
			Line line1('S', 0, 1, 0, 4);
			Line line2('S', 0, -11, 20, -100);
			Circle c(0, 0, 10);
			vector<Line> lvec;
			vector<Circle> cvec;
			lvec.push_back(line1);
			lvec.push_back(line2);
			cvec.push_back(c);
			set<Point> nodeSet;
			size_t i, j;
			for (i = 0; i < cvec.size(); i++) {
				for (j = 0; j < lvec.size(); j++) {
					calc->haveIntersection(cvec[i], lvec[j], nodeSet);
				}
			}
			Assert::AreEqual(nodeSet.size(), (size_t)0);
		}

		TEST_METHOD(SCintersect)
		{
			Calculator* calc = new Calculator();
			Line line1('S', 2, 0, 0, 2);
			Line line2('S', -1, 0, -1, 100);
			Line line3('S', -3, -1, 1, -1);
			Circle c(0, 0, 2);
			vector<Line> lvec;
			vector<Circle> cvec;
			lvec.push_back(line1);
			lvec.push_back(line2);
			lvec.push_back(line3);
			cvec.push_back(c);
			set<Point> nodeSet;
			size_t i, j;
			for (i = 0; i < cvec.size(); i++) {
				for (j = 0; j < lvec.size(); j++) {
					calc->haveIntersection(cvec[i], lvec[j], nodeSet);
				}
			}
			Assert::AreEqual(nodeSet.size(), (size_t)4);
			//<0,1> <1,0>
			Point p1(0, 2);
			Point p2(2, 0);
			Point p3(-1, sqrt(3));
			Point p5(-sqrt(3), -1);
			Assert::AreEqual(nodeSet.count(p1), (size_t)1);
			Assert::AreEqual(nodeSet.count(p2), (size_t)1);
			Assert::AreEqual(nodeSet.count(p3), (size_t)1);
			Assert::AreEqual(nodeSet.count(p5), (size_t)1);
		}
	};


	TEST_CLASS(CalCAndCTest)
	{
	public:
		// test finished (regression )
		TEST_METHOD(CCone)
		{//���� ����
			Calculator* calc = new Calculator();
			Circle c1 = Circle(0, 0, 1);
			Circle c2 = Circle(11, 0, 10);
			Circle c3 = Circle(4, 0, 3);
			set<Point> nodeSet;
			vector<Circle> cvec;
			cvec.push_back(c1);
			cvec.push_back(c2);
			cvec.push_back(c3);
			size_t i, j;
			for (i = 0; i < cvec.size(); i++) {
				for (j = 0; j < cvec.size(); j++) {
					calc->haveIntersection(cvec[i], cvec[j], nodeSet);
				}
			}
			Assert::AreEqual(nodeSet.size(), (size_t)1);
			Point p(1, 0);
			Assert::AreEqual(nodeSet.count(p), (size_t)1);
		}

		TEST_METHOD(CCtwo)
		{
			Calculator* calc = new Calculator();
			Circle c1 = Circle(0, 0, 2);
			Circle c2 = Circle(2, 2, 2);
			Circle c3 = Circle(0, 3, 1);
			set<Point> nodeSet;
			vector<Circle> cvec;
			cvec.push_back(c1);
			cvec.push_back(c2);
			cvec.push_back(c3);
			size_t i, j;
			for (i = 0; i < cvec.size(); i++) {
				for (j = 0; j < cvec.size(); j++) {
					calc->haveIntersection(cvec[i], cvec[j], nodeSet);
				}
			}
			Assert::AreEqual(nodeSet.size(), (size_t)3);
			Point p1(2, 0);
			Point p2(0, 2);
			Point p3(0.8, 3.6);
			Point p4(4 / 5, 18 / 5);
			Point p5(0, 3);
			Assert::AreEqual(nodeSet.count(p1), (size_t)1);
			Assert::AreEqual(nodeSet.count(p2), (size_t)1);
			Assert::AreEqual(nodeSet.count(p3), (size_t)1);
			Assert::IsTrue(p4 == p5);
		}
		TEST_METHOD(CCzero)
		{
			Calculator* calc = new Calculator();
			Circle c1 = Circle(0, 0, 5);
			Circle c2 = Circle(10, 2, 2);
			Circle c3 = Circle(0, 1, 1);
			Circle c4 = Circle(0, 3, 1);
			set<Point> nodeSet;
			vector<Circle> cvec;
			cvec.push_back(c1);
			cvec.push_back(c2);
			cvec.push_back(c3);
			cvec.push_back(c4);
			size_t i, j;
			for (i = 0; i < cvec.size(); i++) {
				for (j = 0; j < cvec.size(); j++) {
					calc->haveIntersection(cvec[i], cvec[j], nodeSet);
				}
			}
			Assert::AreEqual(nodeSet.size(), (size_t)1);

		}

	};

	TEST_CLASS(CalComplexTest)
	{
	public:
		TEST_METHOD(TestLineAndLine)
		{
			Calculator* calc = new Calculator();
			char line = 'L';
			Line l(line, -1, 4, 4, -1);
			Circle c1(1, 0, 2);
			Circle c2(3, -2, 6);
			Circle c3(2, 2, 1);
			vector<Circle> cvec;
			vector <Line> lvec;
			cvec.push_back(c1);
			cvec.push_back(c2);
			cvec.push_back(c3);
			set<Point> nodeSet;
			calc->countAllinsect(lvec, cvec, nodeSet);
			Point p(1, 2);
			Assert::AreEqual(nodeSet.size(), (size_t)2);
			Assert::AreEqual(nodeSet.count(p), (size_t)1);

			lvec.push_back(l);
			calc->countAllinsect(lvec, cvec, nodeSet);
			Assert::AreEqual(nodeSet.size(), (size_t)6);
			Assert::AreEqual(nodeSet.count(p), (size_t)1);
		}
	};

	TEST_CLASS(entiretyTest)
	{
	public:
		TEST_METHOD(TestBigData)
		{
			ifstream infile;
			ofstream outfile;
			/*
			infile.open("input_test.txt");
			outfile.open("output_test.txt");
			if (!infile.is_open()) {
				cout << "Can't open the input file!" << endl;
			}
			if (!outfile.is_open()) {
				cout << "Can't open the output file!" << endl;
			}

			vector<Line> lVec;//��ֱ��
			vector<Circle> cVec;//��Բ
			set<Point> nodeSet;
			double n;
			char type;
			double x1, y1, x2, y2, r;
			size_t i, j;

			infile >> n;
			for (i = 0; i < n; i++) {
				infile >> type;
				if (type == 'L') {
					infile >> x1 >> y1 >> x2 >> y2;
					Line line('L', x1, y1, x2, y2);
					lVec.push_back(line);
				}
				else {
					infile >> x1 >> y1 >> r;
					Circle circle(x1, y1, r);
					cVec.push_back(circle);
				}
			}

			//����ȫ������
			Calculator* cal = new Calculator();
			cal->countAllinsect(lVec, cVec, nodeSet);
			outfile << nodeSet.size();
			Assert::AreEqual(nodeSet.size(), (size_t)784375);
			*/
			infile.close();
			outfile.close();
		}

		TEST_METHOD(Testset)
		{
			Point p1(2.99999999999999, 4.00000000000002);
			Point p2(3, 4);
			Point p3(2.0001, 5);
			Point p4(2.00005, 10);
			Point p5(-0.00000000001, -1.0000000000002);
			Point p6(0, -1);
			Point p7(1.000000000099, 2.234344);
			Point p8(1.000000000008, 2.4535356);
			set<Point> nodeSet;
			nodeSet.insert(p1);
			nodeSet.insert(p2);
			nodeSet.insert(p3);
			nodeSet.insert(p4);
			nodeSet.insert(p5);
			nodeSet.insert(p6);
			nodeSet.insert(p7);
			nodeSet.insert(p8);
			Assert::AreEqual(nodeSet.size(), (size_t)6);
		}
	};
}
