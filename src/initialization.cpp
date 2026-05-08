#include <cmath>
#include <cstdlib>
#include "../include/common.h"
#include "../include/periodicphi.h"
#include "../include/chemicalpotential.h"
#include "../include/gradientcal.h"
#include "../include/interfacenormal.h"

void Initialization() {

    const double half_nx = nx / 2.0;
    const double half_ny = ny / 2.0;
    const double inv_w = 1.0 / w;

    // Initialise phi, zero h and g in one loop 
    for (int x = 0; x <= nx + 1; x++) {
        for (int y = 0; y <= ny + 1; y++) {

            double dx = x - half_nx;
            double dy = y - half_ny;
            double ri = std::sqrt(dx * dx + dy * dy);

            phi[x][y] = 0.5 + 0.5 * std::tanh(2.0 * (r - ri) * inv_w);

            for (int z = 0; z < 9; z++) {
                h[x][y][z] = 0.0;
                g[x][y][z] = 0.0;
            }
        }
    }

    // Boundary and derived field setup
    PeriodicPhi(phi);
    ChemicalPotential();
    GradientCal();
    InterfaceNormal();

    // set macroscopic fields and distribution functions
    for (int y = 1; y < ny + 1; y++) {
        for (int x = 1; x < nx + 1; x++) {

            // Caching global lookups used multiple times and
            // preventing register reuse
            double phi_v = phi[x][y];
            double ni_v = ni[x][y];
            double nj_v = nj[x][y];

            rho[x][y] = rhoL + phi_v * (rhoH - rhoL);
            p[x][y] = 0.0;
            ux[x][y] = 0.0;
            uy[x][y] = 0.0;



            // depends only on phi, not z
            double phi_factor = (1.0 - 4.0 * (phi_v - 0.5) * (phi_v - 0.5)) * inv_w;

            for (int z = 0; z < 9; z++) {
                double wa_z = wa[z];
                double ef_z = phi_factor * (ex[z] * ni_v + ey[z] * nj_v);

                // gamma[z] = wa[z] (since gaWa = 0 when u = 0)
                // h = phi * gamma - 0.5 * wa * ef
                h[x][y][z] = phi_v * wa_z - 0.5 * wa_z * ef_z;

                // g = p * wa + gaWa = p * wa (since gaWa = 0 when u = 0)
                g[x][y][z] = p[x][y] * wa_z;
            }
        }
    }
}