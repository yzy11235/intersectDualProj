#ifndef IOINTERFACE_H_
#define IOINTERFACE_H_

#include "Calculator.h"
#include <iostream>
#include <string>

int guiProcess(std::vector<std::pair<double, double>>* points, std::string msg);
void cmdProcess(int argc, char* argv[]);

class IOManager
{
public:
	static IOManager *getInstance();
	set<Point> getAllIntersect();
	void fileInProcess(ifstream input);

private:
	vector<Line> lVec;
	vector<Circle> cVec;
	static IOManager* IOinstance;
	IOManager();
};



#endif // !IOINTERFACE_H_
