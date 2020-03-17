#include "IOinterface.h"

int guiProcess(std::vector<std::pair<double, double>>* points, 
	std::string msg) {

}

void cmdProcess(int argc, char* argv[]) {
	ifstream infile;
	ofstream outfile;
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-i") == 0) {
			infile.open(argv[i + 1]);
			if (!infile.is_open()) {
				// exp
			}
		}
		else if (strcmp(argv[i], "-o") == 0) {
			outfile.open(argv[i + 1]);
			if (!outfile.is_open()) {
				// exp
			}
		}
	}

	IOManager io = IOManager::getInstance();
	io.fileInProcess(infile);
	set<Point> intersections = getAllIntersect();
	outfile << intersections.size();
	infile.close();
	outfile.close();
}


IOManager::IOManager() {}
IOManager* IOManager::getInstance() {
	if (IOinstance == NULL) {
		IOinstance = new IOinstance();
	}
	return IOinstance;
}

set<Point> IOManager::getAllIntersect() {
	Calculator* cal = new Calculator();
	set<Point> intersections;
	cal->countAllinsect(lVec, cVec, intersections);
	return intersections;
}

void IOManager::fileInProcess(ifstream input) {
	int n;
	input >> n;
	if (n < 1) {
		// exp
	}
	char type;
	double x1, y1, x2, y2, r;
	for (int i = 0; i < n; i++) {
		input >> type;
		if (type == 'C') {
			input >> x1 >> y1 >> r;
			Circle circle(x1, y1, r);
			cVec.push_back(circle);
		}
		else if (type == 'L' || type == 'R' || type == 'S') {
			input >> x1 >> y1 >> x2 >> y2;
			Line line(type, x1, y1, x2, y2);
			lVec.push_back(line);
		}
		else {
			// exception
		}
	}
	input >> type;
	if (type != NULL) {
		// exp
	}
}
