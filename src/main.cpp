#include "IOinterface.h"
#include "Exception.h"

using namespace std;

int main(int argc, char *argv[]) {   

	// TODO: time calculator;
	cmdProcess(argc, argv);

	/*
	ifstream input;
	ofstream output;
	input.open("input.txt");
	output.open("output.txt");

	if (!input.is_open() || !output.is_open()) {
		cout << "file open error" << endl;
	}

	int n; 
	input >> n;
	vector<Line> lVec;
	vector<Circle> cVec;
	char* str = (char*) malloc(MAX_STR * sizeof(char));
	input.getline(str, MAX_STR);
	try {
		for (int i = 0; i < n; i++) {
			input.getline(str, MAX_STR);
			lineExcHandler(str, lVec, cVec);
		}
		set<Point> points = getAllIntersect(lVec, cVec);
		cout << points.size() << endl;
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
	input.close();
	output.close();
	*/
    return 0; 
}


