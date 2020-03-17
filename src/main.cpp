#include "def.h"
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "Calculator.h"
#include <vector>
#include <set>

using namespace std;

/*
int main(){
    ifstream infile;
    ofstream outfile;
    
*/

int main(int argc, char *argv[]) {   

	// TODO: time calculator;

    ifstream infile;
    ofstream outfile;
	int cmd = -1;
	int i = 0;

	cin >> cmd;
	while (true) {
		if (cmd == 0) {
			// run & debug on VS
			infile.open("input.txt");
			outfile.open("output.txt");
			break;
		}
		else if (cmd == 1) {
			// TODO: exception;
			for (i = 0; i < argc; i++) {
				if (strcmp(argv[i], "-i") == 0) {
					infile.open(argv[i + 1]);
				}
				else if (strcmp(argv[i], "-o") == 0) {
					outfile.open(argv[i + 1]);
				}
			}
			break;
		}
		else {
			cout << "0 -> run & debug on VS" << endl
				<< "1 -> run on terminal/cmd" << endl
				<< "please give your choice" << endl;
		}
	}
 
	// TODO: exception;
    if (!infile.is_open()) {
        cout << "Can't open the input file!" << endl;
    }
    if (!outfile.is_open()) {
        cout << "Can't open the output file!" << endl;
    }

	vector<Line> lVec;//存直线
	vector<Circle> cVec;//存圆
	set<Point> nodeSet;
	// TODO: change DS like unordered_set to improve performance

    double n;
    char type;
    double x1, y1, x2, y2, r;

    infile >> n;
    for (i = 0; i < n; i++) {
        infile >> type;
        if (type == 'C') {
            infile >> x1 >> y1 >> r;
            Circle circle(x1, y1, r);
            cVec.push_back(circle);
		}
		else if (type == 'L' || type == 'R' || type == 'S') {
			infile >> x1 >> y1 >> x2 >> y2;
			Line line(type, x1, y1, x2, y2);
			lVec.push_back(line);
		}
		else {
			// exception
		}
    }

	Calculator* cal = new Calculator();
    cal->countAllinsect(lVec, cVec, nodeSet);
    outfile << nodeSet.size();
    /*
    cout << "node in Set" << endl;
    for (Point node:nodeSet) {
        cout << "<" << node.x<< "," << node.y << ">" << endl;
    }
    */
    infile.close();
    outfile.close();

    return 0; 
}


