#include <cmath>
#include <omp.h>
#include "../include/common.h"
#include "../include/interfacenormal.h"

void InterfaceNormal() {

#pragma omp parallel for schedule(static)
    for (int x = 1; x < nx + 1; x++) {
        for (int y = 1; y < ny + 1; y++) {

            double dpdx = dphidx[x][y];
            double dpdy = dphidy[x][y];

            // 1e-16 is below double precision noise for any real gradient
            // but prevents division by zero when both gradients are exactly 0.
            double tmp = std::sqrt(dpdx * dpdx + dpdy * dpdy + 1e-16);
            double inv_tmp = 1.0 / tmp;

            ni[x][y] = dpdx * inv_tmp;
            nj[x][y] = dpdy * inv_tmp;
        }
    }
}