#ifndef IOINTERFACE_H_
#define IOINTERFACE_H_

#include "Calculator.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int guiProcess(std::vector<std::pair<double, double>>* points, std::string msg);
void cmdProcess(int argc, char* argv[]);

set<Point> getAllIntersect(vector<Line> lVec, vector<Circle> cVec);


#endif // !IOINTERFACE_H_
