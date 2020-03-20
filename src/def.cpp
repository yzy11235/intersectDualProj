#include "def.h"
#include "pch.h"

int doubleCmp(double a, double b) {
	if (fabs(a - b) < EPS) {
		return 0;
	}
	else if (a < b) {
		return -1;
	}
	else {
		return 1;
	}
}

