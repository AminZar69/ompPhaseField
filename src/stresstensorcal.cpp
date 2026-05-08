#include "../include/common.h"
#include "../include/stresstensorcal.h"

void StressTensorCal(double gneq[9], double& sxx, double& sxy, double& syy) {

    sxx = 0.0;
    sxy = 0.0;
    syy = 0.0;

    // z = 0 is the rest direction: ex[0] = ey[0] = 0,
    // loop starts at z = 1.
    for (int z = 1; z < 9; z++) {

        double g_z = gneq[z];
        double ex_z = ex[z];
        double ey_z = ey[z];

        sxx += g_z * ex_z * ex_z;
        sxy += g_z * ex_z * ey_z;
        syy += g_z * ey_z * ey_z;
    }
}