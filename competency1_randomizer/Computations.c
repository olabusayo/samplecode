#include "Computations.h"

double Computations_calculateArea (double r) {
    double a = 0;
    if( r < sqrt(DBL_MAX)) {
        a = M_PI * (r*r);
        if( a < 0 || a > DBL_MAX ) {
            printf("Issue computing area; Number too large\n");
        }
    }
    return a;
}

double Computations_calculateVolumeCube (double a) {
    double v = 0;
    if( a < cbrt(DBL_MAX) ) {
        v = a * a * a;
    }
    return v;
}
