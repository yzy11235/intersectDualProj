#pragma once
#include <Windows.h>
#include "Calculator.h"
#include <iostream>
#include <fstream>
#include <string>

#ifdef IMPORT_DLL
#else
#define IMPORT_DLL extern "C" _declspec(dllimport)
#endif

#define MAX_STR 64
#define DATA_BOUND 100000

using namespace std;

IMPORT_DLL int guiProcess(std::vector<std::pair<double, double>>* points,
	std::string msg);

IMPORT_DLL void cmdProcess(int argc, char* argv[]);

void cmdExcHandler(int argc, char* argv[], ifstream& input, ofstream& output);
void fileExcHandler(istream& input, vector<Line>& lVec, vector<Circle>& cVec);
void lineExcHandler(char* str, vector<Line>& lVec, vector<Circle>& cVec);
set<Point> getAllIntersect(vector<Line> lVec, vector<Circle> cVec);

char* readStr(char* str, int* pos); // throw file format exc;
int isInt(char* str); // throw file format exc;
bool endofStr(char* str); // throw file format exc;


