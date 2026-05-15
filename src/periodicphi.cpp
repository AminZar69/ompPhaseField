#include <omp.h>
#include "../include/common.h"
#include "../include/periodicphi.h"

void PeriodicPhi(double a[(nx + 2)][(ny + 2)]) {

    // x-direction periodic boundaries (left and right)
#pragma omp parallel for schedule(static)
    for (int y = 0; y <= ny + 1; y++) {
        a[0][y] = a[nx][y];    // left ghost  <= right interior
        a[nx + 1][y] = a[1][y];     // right ghost <= left interior
    }

    // y-direction periodic boundaries (bottom and top)
#pragma omp parallel for schedule(static)
    for (int x = 0; x <= nx + 1; x++) {
        a[x][0] = a[x][ny];    // bottom ghost <= top interior
        a[x][ny + 1] = a[x][1];     // top ghost    <= bottom interior
    }
}