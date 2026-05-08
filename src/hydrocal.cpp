#include <omp.h>
#include "../include/common.h"
#include "../include/hydrocal.h"
#include "../include/periodicphi.h"
#include "../include/gradientcal.h"
#include "../include/chemicalpotential.h"
#include "../include/viscousforcecal.h"

void HydroCal() {

    PeriodicPhi(phi);
    GradientCal();
    ChemicalPotential();

#pragma omp parallel for schedule(static) 
    for (int x = 1; x < nx + 1; x++) {
        for (int y = 1; y < ny + 1; y++) {

            double phi_v = phi[x][y];
            double ux_v = ux[x][y];
            double uy_v = uy[x][y];
            double rho_v = rho[x][y];
            double mu_v = mu[x][y];
            double dpdx_v = dphidx[x][y];
            double dpdy_v = dphidy[x][y];
            int solid = is_solid_node[x][y];

            double p_v = 0.0;
            for (int z = 0; z < 9; z++) {
                p_v += g[x][y][z];
            }
            p[x][y] = p_v;

            double fpx = -p_v * drho3 * dpdx_v;
            double fpy = -p_v * drho3 * dpdy_v;
            double u2 = ux_v * ux_v + uy_v * uy_v;
            double tauu = tauL + phi_v * (tauH - tauL);

            // non-equilibrium part for stress tensor
            double gaWa[9], geq[9], gneq[9], eu[9];
            for (int z = 0; z < 9; z++) {
                eu[z] = ex[z] * ux_v + ey[z] * uy_v;
                gaWa[z] = wa[z] * (eu[z] * (3.0 + 4.5 * eu[z]) - 1.5 * u2);
                geq[z] = p_v * wa[z] + gaWa[z];
                gneq[z] = g[x][y][z] - geq[z];
            }

            // Force calculation
            double fmx, fmy;
            ViscousForceCal(tauu, dpdx_v, dpdy_v, gneq, fmx, fmy);

            double fx = mu_v * dpdx_v + fpx + fmx;
            double fy = mu_v * dpdy_v + fpy + fmy;

            // Velocity update 
            // Compute momentum sum once, then conditionally add force term.
            double mom_x = g[x][y][1] - g[x][y][3] + g[x][y][5]
                - g[x][y][6] - g[x][y][7] + g[x][y][8];

            double mom_y = g[x][y][2] - g[x][y][4] + g[x][y][5]
                + g[x][y][6] - g[x][y][7] - g[x][y][8];

            if (solid == 0) {
                double half_inv_rho = 0.5 / rho_v;
                ux[x][y] = mom_x + fx * half_inv_rho;
                uy[x][y] = mom_y + fy * half_inv_rho;
            }
            else {
                ux[x][y] = mom_x;
                uy[x][y] = mom_y;
            }
        }
    }
}