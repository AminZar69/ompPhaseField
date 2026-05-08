#include <cstring>
#include <omp.h>
#include "../include/common.h"
#include "../include/periodicpopulations.h"

void PeriodicPopulations(double f[(nx + 2)][(ny + 2)][9]) {

    // x-direction periodic boundaries (left and right)
    // For each y, copy the full z-strip (9 contiguous doubles)
#pragma omp parallel for schedule(static) 
    for (int y = 0; y < ny + 2; y++) {
        std::memcpy(f[0][y], f[nx][y], 9 * sizeof(double));  // left ghost  ← right interior
        std::memcpy(f[nx + 1][y], f[1][y], 9 * sizeof(double));  // right ghost ← left interior
    }

    // y-direction periodic boundaries (bottom and top)
#pragma omp parallel for schedule(static) 
    for (int x = 0; x < nx + 2; x++) {
        std::memcpy(f[x][0], f[x][ny], 9 * sizeof(double));  // bottom ghost ← top interior
        std::memcpy(f[x][ny + 1], f[x][1], 9 * sizeof(double));  // top ghost    ← bottom interior
    }
}