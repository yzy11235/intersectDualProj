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
			Assert::IsTrue(calc->xmult(v1, v2, v3) == -5632);
			Assert::IsTrue(calc->xmult(v2, v3, v4) == -698737);
			Assert::IsTrue(calc->xmult(v3, v4, v5) == -2552040);
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
			Point pMidOut1(8, 55.00000000001);
			Point pMidOut2(7.99999999999999, 55);
			Point p2(9, 10);
			Point pUp(9, 100);
			Point pUpOut(9,10000);
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
			Assert::IsFalse(cal->isParallerl(l1, sTD) == false);
			Assert::IsFalse(cal->isParallerl(r1, sTD) == false);
			Assert::IsFalse(cal->isParallerl(s1, rTD) == false);
		}
		
		// TODO: functin unfinished 
		TEST_METHOD(lineOverlap) {

		}

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
		}

		// line cross line test1 regression
		TEST_METHOD(LineCrossOne) {
			Calculator* calc = new Calculator();
			char line = 'L';
			char radio = 'R';
			char segment = 'S';
			int n = 3;
			Line line1(line, 1, 3, 2, 3);
			Line line2(line, 1, 3, 4, 5);
			Line line3(line, 1, 3, 10, 1);
			vector<Line> lvec;
			lvec.push_back(line1);
			lvec.push_back(line2);
			lvec.push_back(line3);
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

		TEST_METHOD(lineAllType1) {

		}
	};

	TEST_CLASS(CalLAndCTest)
	{
	public:
		// regression test
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
