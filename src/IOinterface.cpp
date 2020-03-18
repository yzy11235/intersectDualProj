#include "IOinterface.h"

int guiProcess(std::vector<std::pair<double, double>>* points, 
	std::string msg) {
	return 0;
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

	vector<Line> lVec;
	vector<Circle> cVec;
	int n;
	infile >> n;
	char type;
	int x1, y1, x2, y2, r;
	for (int i = 0; i < n; i++) {
		infile >> type;
		if (type == 'C') {
			infile >> x1 >> y1 >> r;
			Circle c(x1, y1, r);
			cVec.push_back(c);
		}
		else if (type == 'L' || type == 'R' || type == 'S') {
			infile >> x1 >> y1 >> x2 >> y2;
			Line l(type, x1, y1, x2, y2);
			lVec.push_back(l);
		}
		else {
			//exp
		}
	}

	set<Point> intersections = getAllIntersect(lVec, cVec);
	outfile << intersections.size();
	infile.close();
	outfile.close();
}


set<Point> getAllIntersect(vector<Line> lVec, vector<Circle> cVec) {
	Calculator* cal = new Calculator();
	set<Point> intersections;
	cal->countAllinsect(lVec, cVec, intersections);
	return intersections;
}

