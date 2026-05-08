#include <omp.h>
#include "../include/common.h"
#include "../include/chemicalpotential.h"

void ChemicalPotential() {


#pragma omp parallel for schedule(static) 
    for (int x = 1; x < nx + 1; x++) {
        for (int y = 1; y < ny + 1; y++) {

            double phi_v = phi[x][y];

            // Isotropic Laplacian stencil (9-point D2Q9 weights)
            double d2phi =
                (phi[x - 1][y - 1] + phi[x + 1][y - 1] +
                    phi[x - 1][y + 1] + phi[x + 1][y + 1]
                    + 4.0 * (phi[x][y - 1] + phi[x - 1][y] +
                        phi[x + 1][y] + phi[x][y + 1])
                    - 20.0 * phi_v) / 6.0;

            mu[x][y] = 4.0 * beta * phi_v * (phi_v - 1.0) * (phi_v - 0.5)
                - kappa * d2phi;
        }
    }
}