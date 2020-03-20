#include "IOinterface.h"
#include "Exception.h"
#include <stdlib.h>
#include <ctype.h>

using namespace std;

int guiProcess(std::vector<std::pair<double, double>>* points, 
	std::vector<string> msg) {
	return 0;
}

void cmdProcess(int argc, char* argv[]) {
	ifstream infile;
	ofstream outfile;
	try{
	    cmdExcHandler(argc, argv, infile, outfile);
	    vector<Line> lVec;
	    vector<Circle> cVec;
		fileExcHandler(infile, lVec, cVec);
		set<Point> intersections = getAllIntersect(lVec, cVec);
		outfile << intersections.size();
	}
	catch (cmdException& cmdError) {
		cout << cmdError.what() << endl;
		cout << cmdError.getUsage() << endl;
	}
	catch (fileException& fileError) {
		cout << fileError.what() << endl;
	}
	catch (lineException& lineError) {
		cout << lineError.what() << endl;
	}
	catch (CircleException& circleError) {
		cout << circleError.what() << endl;
	}
	infile.close();
	outfile.close();
}

void cmdExcHandler(int argc, char* argv[], ifstream& input, ofstream& output) {
	if (argc != 5) {
		throw cmdException(CMD_NOT_FOUND);
	}
	else if (strcmp(argv[0], "intersect.exe") != 0) {
		throw cmdException(CMD_NOT_FOUND);
	}
	else if (strcmp(argv[1], "-i") != 0) {
		throw cmdException(CMD_PAR_EXC);
	}
	else if (strcmp(argv[2], "input.txt") != 0) {
		throw cmdException(CMD_FILENAME_EXC);
	}
	else if (strcmp(argv[3], "-o") != 0) {
		throw cmdException(CMD_PAR_EXC);
	}
	else if (strcmp(argv[4], "output.txt") != 0) {
		throw cmdException(CMD_FILENAME_EXC);
	}
	input.open(argv[2]);
	output.open(argv[4]);
	if (!input.is_open() || !output.is_open()) {
		throw fileException(FILE_OPEN_ERROR);
	}
}

void fileExcHandler(ifstream& input, vector<Line>& lVec, vector<Circle>& cVec) {
	char* str = (char*)malloc(MAX_STR * sizeof(char));
	input.getline(str, MAX_STR);
	int n;
	int* pos = (int*)malloc(sizeof(int));
	if ((n = isInt(readStr(str, pos))) < 1) {
		throw fileException(FILE_GRAPHSUM_ERROR);
	}
	char* type;
	int x1, y1, x2, y2, r;
	int i = 0;
	while (!input.eof()) {
		input.getline(str, MAX_STR);
		type = readStr(str, pos);
		str = str + *pos;
		x1 = isInt(readStr(str, pos));
		str = str + *pos;
		y1 = isInt(readStr(str, pos));
		str = str + *pos;
		if (strcmp(type, "C") == 0) {
			if (x1 >= DATA_BOUND || x1 <= -DATA_BOUND
				|| y1 >= DATA_BOUND || y1 <= -DATA_BOUND) {
				throw CircleException(CIRCLE_FORMAT_ERROR);
			}
			r = isInt(readStr(str, pos));
			str += *pos;
			if (r < 1 || r >= DATA_BOUND) {
				throw CircleException(CIRCLE_FORMAT_ERROR);
			}
			endofStr(str);
			Circle c(x1, y1, r);
			cVec.push_back(c);
		}
		else if (strcmp(type, "L") == 0 || strcmp(type, "R") == 0
			|| strcmp(type, "S") == 0) {
			if (x1 >= DATA_BOUND || x1 <= -DATA_BOUND
				|| y1 >= DATA_BOUND || y1 <= -DATA_BOUND) {
				throw lineException(LINE_FORMAT_ERROR);
			}
			x2 = isInt(readStr(str, pos));
			str += *pos;
			y2 = isInt(readStr(str, pos));
			str += *pos;
			if (x2 >= DATA_BOUND || x2 <= -DATA_BOUND
				|| y2 >= DATA_BOUND || y2 <= -DATA_BOUND) {
				throw lineException(LINE_FORMAT_ERROR);
			}
			else if (x1 == x2 && y1 == y2) {
				throw lineException(LINE_FORMAT_ERROR);
			}
			endofStr(str);
			Line l(*type, x1, y1, x2, y2);
			lVec.push_back(l);
		}
		else {
			throw fileException(FILE_FORMAT_ERROR);
		}
		i++;
		if (i > n) {
			throw fileException(FILE_GRAPHSUM_ERROR);
		}
	}
	if (i != n) {
		throw fileException(FILE_GRAPHSUM_ERROR);
	}
}

char* readStr(char* str, int* pos) {
	char ch;
	int i = 0, j = 0;
	while (*(str + i) < 33) {
		if (*(str + i) == 0) {
			// no str when needed
			throw fileException(FILE_FORMAT_ERROR);
		}
		i++;
	}
	char* retStr = (char*)malloc(16 * sizeof(char));
	while (*(str + i) > 32) {
		retStr[j] = *(str + i);
		i++;
		j++;
	} 
	retStr[j] = 0;
	*pos = i;
	return retStr;
}

// is int & no format like 001;
int isInt(char* str) {
	bool isPos = true;
	if (*str == '-') {
		isPos = false;
		str += 1;
	}
	int num = 0;
	int n = strlen(str);
	if (*str == '0' && n != 1) {
		// remove numbers like 001;
		throw fileException(FILE_FORMAT_ERROR);
	}
	else if (*str == 0) {
		// no number
		throw fileException(FILE_FORMAT_ERROR);
	}
	for (int i = 0; *(str + i) != 0; i++) {
		if (*(str + i) < '0' || *(str + i) > '9') {
			// remove str like 3856-16
			throw fileException(FILE_FORMAT_ERROR);
		}
		num = num * 10 + *(str + i) - '0';
	}
	return (isPos) ? num : -num;
}

bool endofStr(char* str) {
	int i = 0;
	while (*(str + i) != 0) {
		if (*(str + i) > 32) {
			throw fileException(FILE_FORMAT_ERROR);
		}
		i++;
	}
	return true;
}

set<Point> getAllIntersect(vector<Line> lVec, vector<Circle> cVec) {
	Calculator* cal = new Calculator();
	set<Point> intersections;
	cal->countAllinsect(lVec, cVec, intersections);
	return intersections;
}

