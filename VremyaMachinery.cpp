#include "VremyaMachinery.h"
#include <cmath>

int VremyaMachinery::skolkoDney(double km, double kmDen) {
    if (kmDen <= 0.001) return 999999;
    int res = (int)(km / kmDen);
    if (km / kmDen > res) res = res + 1;
    return res;
}

double VremyaMachinery::rasst(double x1, double y1, double x2, double y2) {
    double a = x1 - x2;
    double b = y1 - y2;
    return sqrt(a*a + b*b);
}
