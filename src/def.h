#ifndef DEF_H_
#define DEF_H_

#include "stdafx.h"
#include <iostream>
#include <cmath>

#define EPS  (1e-8)
#define doubleCmp(a, b) ((fabs((a) - (b)) < EPS) ? 0 : ((a) < (b)) ? - 1 : 1)


#endif // !DEF_H_

