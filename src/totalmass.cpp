#include <omp.h>
#include "../include/common.h"
#include "../include/totalmass.h"

double TotalMass(double arr[(nx + 2)][(ny + 2)]) {

    double sum = 0.0;

#pragma omp parallel for schedule(static) reduction(+:sum)
    for (int x = 1; x < nx + 1; x++) {
        for (int y = 1; y < ny + 1; y++) {
            if (is_solid_node[x][y] == 0) {
                sum += arr[x][y];
            }
        }
    }

    return sum;
}