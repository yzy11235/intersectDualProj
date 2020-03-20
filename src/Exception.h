#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>
#include <string.h>
using namespace std;

#define CMD_PAR_EXC -11
#define CMD_FILENAME_EXC -12
#define CMD_NOT_FOUND -13

#define FILE_FORMAT_ERROR -21
#define FILE_GRAPHSUM_ERROR -22
#define FILE_OPEN_ERROR -23

#define LINE_FORMAT_ERROR -31
#define LINE_INFINITE_INTERSECT -32

#define CIRCLE_FORMAT_ERROR -41
#define CIRCLE_INFINITE_INTERSECT -42

class cmdException : public exception
{
public:
	cmdException(int errorType) {
		type = errorType;
	}
	~cmdException() throw() {}

	const char* getUsage() {
		return "Usage: intersect.exe -i input.txt -o output.txt";
	}

	virtual const char* what() const throw () {
		if (type == CMD_PAR_EXC) {
			return "Option not found";
	    }
		else if (type == CMD_FILENAME_EXC) {
			return "FileName not found";
		}
		else if (type == CMD_NOT_FOUND) {
			return "Command not found";
		}
	}

private:
	int type;
};

class fileException : public exception {
public:
	fileException(int errorType) {
		type = errorType;
	}
	~fileException() throw() {}

	virtual const char* what() const throw() {
		if (type == FILE_FORMAT_ERROR) {
			return "Format error in file:\n"
				"Usage:\n"
				"For example: 'L 1 2 3 4' or 'C 1 2 3'";
		}
		else if (type == FILE_GRAPHSUM_ERROR) {
			return "Sum of graph is wrong\n"
				"Usage: (int N > 0)\n" 
				"N\n"
				"N times different lines or circles";
		}
		else if (type == FILE_OPEN_ERROR) {
			return "File open Error:\n"
				"'input.txt' not found,\n"
				"or 'output.txt' open error"; 
		}
	}

private:
	int type;
};

class lineException : public exception
{
public:
	lineException(int errorType) {
		type = errorType;
	}
	~lineException() throw () {}

	virtual const char* what() const throw() {
		if (type == LINE_FORMAT_ERROR) {
			return "Line format error: \n"
				"Usage: \n" 
				"'[lineType] x1 y1 x2 y2'\n"
				"lineType: 'L' / 'R' / 'S'\n"
				"(x1,y1) != (x2,y2) && in (-100000,100000)";
		}
		else if (type == LINE_INFINITE_INTERSECT) {
			return "Lines input error\n"
				"Lines have infinite intersections";
		}
	}

private:
	int type;
};

class CircleException : public exception
{
public:
	CircleException(int errorType) {
		type = errorType;
	}
	~CircleException() throw () {}

	virtual const char* what() const throw () {
		if (type == CIRCLE_FORMAT_ERROR) {
			return "Circle format error: \n"
				"Usage: \n"
				"'C x y r'\n"
				"x,y in (-100000,100000), r >= 1";
		}
		else if (type == CIRCLE_INFINITE_INTERSECT) {
			return "Circles input error\n"
				"Circles have infinite intersections";
		}
	}

private:
	int type;
};

#endif // !EXCEPTION_H_
