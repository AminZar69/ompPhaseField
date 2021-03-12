/* ============================== License GPLv3 ===================================
    ompPhaseField is a multiphase flow solver based on th lattice Boltzmann method accelerated by
	utilising OpenMP.
    Copyright (C) 2021 Amin Zar, aminpopjoury@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 ================================================================================ */

#include<omp.h>
#include "../include/common.h"
#include "../include/hydrocal.h"
#include "../include/periodicphi.h"
#include "../include/gradientcal.h"
#include "../include/chemicalpotential.h"
#include "../include/viscousforcecal.h"

void HydroCal() {

	int x, y, z;
	double gaWa[9], geq[9];
	double fpx, fpy, fmx, fmy, fx, fy, tauu, sum, u2;
	double gneq[9], eu[9];

	PeriodicPhi(phi);
	GradientCal();
	ChemicalPotential();

	#pragma omp parallel for private(x, z, fpx, fpy, gaWa, geq, gneq, tauu, fmx, fmy, fx, fy, u2, eu) schedule(static) collapse(2)
	for (y = 1; y < ny + 1; y++) {

		for (x = 1; x < nx + 1; x++) {
			
			

			p[x][y] = g[0][x][y] + g[1][x][y] + g[2][x][y] + g[3][x][y] + g[4][x][y] +\
								g[5][x][y] + g[6][x][y] + g[7][x][y] + g[8][x][y];


			fpx = -p[x][y] * drho3 * dphidx[x][y];
			fpy = -p[x][y] * drho3 * dphidy[x][y];

			
			u2 = ux[x][y] * ux[x][y] + uy[x][y] * uy[x][y];
	
			for (z = 0; z < 9; z++) {

				eu[z] = ex[z] * ux[x][y] + ey[z] * uy[x][y];

				gaWa[z] = wa[z] * (eu[z] * (3. + 4.5*eu[z]) - 1.5*u2);
		
				geq[z] = p[x][y] * wa[z] + gaWa[z];

				gneq[z] = g[z][x][y] - geq[z];
			}
			
			

			tauu = tauL + phi[x][y] * (tauH - tauL);

			ViscousForceCal(tauu, dphidx[x][y], dphidy[x][y], gneq, fmx, fmy);

		

			fx = mu[x][y] * dphidx[x][y] + fpx + fmx;
			fy = mu[x][y] * dphidy[x][y] + fpy + fmy;


			if (is_solid_node[x][y]==0) {

				ux[x][y] = (g[1][x][y] - g[3][x][y] + g[5][x][y] - g[6][x][y] - g[7][x][y] + g[8][x][y]) + (0.5*fx / rho[x][y]);
				uy[x][y] = (g[2][x][y] - g[4][x][y] + g[5][x][y] + g[6][x][y] - g[7][x][y] - g[8][x][y]) + (0.5*fy / rho[x][y]);

			}

			else {

				ux[x][y] = (g[1][x][y] - g[3][x][y] + g[5][x][y] - g[6][x][y] - g[7][x][y] + g[8][x][y]);
				uy[x][y] = (g[2][x][y] - g[4][x][y] + g[5][x][y] + g[6][x][y] - g[7][x][y] - g[8][x][y]);

			}


		}


	}


}