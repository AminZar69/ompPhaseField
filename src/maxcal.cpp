#include <omp.h>
#include <limits>
#include "../include/common.h"
#include "../include/maxcal.h"

double MaxCal(double arr[(nx + 2)][(ny + 2)]) {


    double maxNum = -std::numeric_limits<double>::max();


#pragma omp parallel for schedule(static) reduction(max:maxNum)
    for (int x = 1; x < nx + 1; x++) {
        for (int y = 1; y < ny + 1; y++) {
            if (is_solid_node[x][y] == 0) {
                double val = arr[x][y];
                if (val > maxNum){
                    maxNum = val;
                }
            }
        }
    }

    return maxNum;
}