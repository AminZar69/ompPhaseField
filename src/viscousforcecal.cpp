#include "../include/common.h"
#include "../include/viscousforcecal.h"
#include "../include/stresstensorcal.h"

void ViscousForceCal(double tauu, double dpdx, double dpdy,
    double gneq[9], double& fmx, double& fmy) {

    double sxx, sxy, syy;
    StressTensorCal(gneq, sxx, sxy, syy);


    double factor = (0.5 - tauu) / tauu * (rhoH - rhoL);

    fmx = factor * (sxx * dpdx + sxy * dpdy);
    fmy = factor * (sxy * dpdx + syy * dpdy);
}