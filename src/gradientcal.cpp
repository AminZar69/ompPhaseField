#include <omp.h>
#include "../include/common.h"
#include "../include/gradientcal.h"

void GradientCal() {

#pragma omp parallel for schedule(static)
    for (int x = 1; x < nx + 1; x++) {
        for (int y = 1; y < ny + 1; y++) {

            dphidx[x][y] =
                (phi[x + 1][y] - phi[x - 1][y]) * (1.0 / 3.0) +
                (phi[x + 1][y - 1] + phi[x + 1][y + 1] -
                    phi[x - 1][y - 1] - phi[x - 1][y + 1]) * (1.0 / 12.0);

            dphidy[x][y] =
                (phi[x][y + 1] - phi[x][y - 1]) * (1.0 / 3.0) +
                (phi[x - 1][y + 1] + phi[x + 1][y + 1] -
                    phi[x - 1][y - 1] - phi[x + 1][y - 1]) * (1.0 / 12.0);
        }
    }
}