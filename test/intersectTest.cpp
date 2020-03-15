#include "pch.h"
#include "CppUnitTest.h"
#include "..\src\Calculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace intersectTest
{
	TEST_CLASS(CalLAndLTest)
	{
	public:
		TEST_METHOD(LinePrl)
		{
			Calculator* calc = new Calculator();
			Line line11(1, 3, 2, 3);
			Line line21(2, 5, 4, 5);
			set<Point> nodeSet1;
			calc->haveIntersection(line11, line21, nodeSet1);
			Assert::AreEqual(nodeSet1.size(), (size_t)0);

			Line line12(3, 1, 3, 2);
			Line line22(2, 1, 2, 10);
			set<Point> nodeSet2;
			calc->haveIntersection(line12, line22, nodeSet2);
			Assert::AreEqual(nodeSet2.size(), (size_t)0);

			Line line13(1, 1, 2, 2);
			Line line23(1, 2, 2, 3);
			set<Point> nodeSet3;
			calc->haveIntersection(line13, line23, nodeSet3);
			Assert::AreEqual(nodeSet3.size(), (size_t)0);
		}

		TEST_METHOD(LineCrossOne)
		{
			Calculator* calc = new Calculator();
			int n = 3;
			Line line1(1, 3, 2, 3);
			Line line2(1, 3, 4, 5);
			Line line3(1, 3, 10, 1);
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

		TEST_METHOD(LineGeneral)
		{
			Calculator* calc = new Calculator();
			Line line1(0, 0, 2, 3);
			Line line2(0, 0, 3, -5);
			Line line3(5, 3, 5, 1);
			Line line4(0, 200, 1, 200);
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

	};

	TEST_CLASS(CalLAndCTest)
	{
	public:
		TEST_METHOD(LCtagency)
		{
			Calculator* calc = new Calculator();
			Line line1(1, 0, 1, 4);
			Line line2(0, 1, 2, 1);
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
			Line line1(0, 9, 10, 0);
			Line line2(0, -11, 20, -3);
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
			Line line1(2, 0, 0, 2);
			Line line2(-1, 0, -1, 100);
			Line line3(100, -1, 1000, -1);
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
		TEST_METHOD(CCone)
		{//外切 内切
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
			Line l(-1, 4, 4, -1);
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

			vector<Line> lVec;//存直线
			vector<Circle> cVec;//存圆
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
					Line line(x1, y1, x2, y2);
					lVec.push_back(line);
				}
				else {
					infile >> x1 >> y1 >> r;
					Circle circle(x1, y1, r);
					cVec.push_back(circle);
				}
			}

			//计算全部交点
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
