#include <omp.h>
#include "../include/common.h"
#include "../include/collision.h"
#include "../include/viscousforcecal.h"

void Collision() {

#pragma omp parallel for schedule(static) 
    for (int x = 1; x < nx + 1; x++) {
        for (int y = 1; y < ny + 1; y++) {

            double phi_v = phi[x][y];
            double ux_v = ux[x][y];
            double uy_v = uy[x][y];
            double rho_v = rho[x][y];
            double p_v = p[x][y];
            double mu_v = mu[x][y];
            double dpdx_v = dphidx[x][y];
            double dpdy_v = dphidy[x][y];
            double ni_v = ni[x][y];
            double nj_v = nj[x][y];
            int solid = is_solid_node[x][y];

            double u2 = ux_v * ux_v + uy_v * uy_v;
            double phi_factor = (1.0 - 4.0 * (phi_v - 0.5) * (phi_v - 0.5)) / w;
            double tauu = tauL + phi_v * (tauH - tauL);
            double inv_tau = 1.0 / tauu;
            double one_minus_inv_tau = 1.0 - inv_tau;
            double fpx = -p_v * drho3 * dpdx_v;
            double fpy = -p_v * drho3 * dpdy_v;

            // Local arrays (stack, implicitly private per thread)
            double gaWa[9], ef[9], hlp[9], heq[9], geq[9], gneq[9], eu[9];

            // h collision and geq/gneq setup
            for (int z = 0; z < 9; z++) {
                eu[z] = ex[z] * ux_v + ey[z] * uy_v;
                gaWa[z] = wa[z] * (eu[z] * (3.0 + 4.5 * eu[z]) - 1.5 * u2);

                double gamma_z = gaWa[z] + wa[z];
                ef[z] = phi_factor * (ex[z] * ni_v + ey[z] * nj_v);
                hlp[z] = wa[z] * ef[z];
                heq[z] = phi_v * gamma_z - 0.5 * hlp[z];

                if (solid == 0) {
                    h[x][y][z] = h[x][y][z] * (1.0 - w_c) + heq[z] * w_c + hlp[z];
                }

                geq[z] = p_v * wa[z] + gaWa[z];
                gneq[z] = g[x][y][z] - geq[z];
            }

            // Force calculation
            double fmx, fmy;
            ViscousForceCal(tauu, dpdx_v, dpdy_v, gneq, fmx, fmy);

            double fx = mu_v * dpdx_v + fpx + fmx;
            double fy = mu_v * dpdy_v + fpy + fmy;

            // g collision 
            for (int z = 0; z < 9; z++) {
                ef[z] = ex[z] * fx + ey[z] * fy;
                hlp[z] = 3.0 * wa[z] * ef[z] / rho_v;
                geq[z] = p_v * wa[z] + gaWa[z] - 0.5 * hlp[z];

                if (solid == 0) {
                    g[x][y][z] = g[x][y][z] * one_minus_inv_tau + geq[z] * inv_tau + hlp[z];
                }
            }
        }
    }
}