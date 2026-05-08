#include <omp.h>
#include "../include/common.h"
#include "../include/phical.h"

void PhiCal() {

    double drho = rhoH - rhoL;

#pragma omp parallel for schedule(static) 
    for (int x = 1; x < nx + 1; x++) {
        for (int y = 1; y < ny + 1; y++) {
            if (is_solid_node[x][y] == 0) {

                double sum = 0.0;
                for (int z = 0; z < 9; z++) {
                    sum += h[x][y][z];
                }

                phi[x][y] = sum;
                rho[x][y] = rhoL + sum * drho;
            }
        }
    }
}