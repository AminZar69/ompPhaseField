#include <omp.h>
#include "../include/common.h"
#include "../include/propagation.h"


// Lives in the data segment, allocated once and reused across calls.
static double fnew[(nx)][(ny)][8];

void Propagation(double f[(nx + 2)][(ny + 2)][9]) {

    // pull from neighbours into fnew
#pragma omp parallel for schedule(static) 
    for (int x = 0; x < nx; x++) {
        for (int y = 0; y < ny; y++) {
            for (int z = 1; z < 9; z++) {
                int sx = x + 1 - ex[z];
                int sy = y + 1 - ey[z];
                fnew[x][y][z - 1] = f[sx][sy][z];
            }
        }
    }

    // write back into f
#pragma omp parallel for schedule(static) 
    for (int x = 0; x < nx; x++) {
        for (int y = 0; y < ny; y++) {
            for (int z = 1; z < 9; z++) {
                f[x + 1][y + 1][z] = fnew[x][y][z - 1];
            }
        }
    }
}