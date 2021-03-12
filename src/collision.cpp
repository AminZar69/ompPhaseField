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
#include "../include/collision.h"
#include "../include/interfacenormal.h"
#include "../include/viscousforcecal.h"


void Collision() {
	
	int x, y, z;

	double gamma[9], gaWa[9], heq[9], geq[9], hlp[9], ef[9], tauu;
	double fpx, fpy, fmx, fmy, fx, fy, u2;
	double gneq[9], eu[9];


	InterfaceNormal();
	
	#pragma omp parallel for private(x, z, u2, eu, gaWa, gamma, ef, hlp, heq, geq, gneq, fpx, fpy, tauu, fmx, fmy, fx, fy) schedule(static) collapse(2)
	for (y = 1; y < ny + 1; y++) {
		
		for (x = 1; x< nx + 1; x++) {


			
			
			u2 = ux[x][y] * ux[x][y] + uy[x][y] * uy[x][y];
	
			

			for (z = 0; z < 9; z++) {
				
				eu[z] = ex[z] * ux[x][y] + ey[z] * uy[x][y];

				gaWa[z] = wa[z] * (eu[z] * (3. + 4.5*eu[z]) - 1.5*u2);
			
				gamma[z] = gaWa[z] + wa[z];

				ef[z] = (1. - 4. * (phi[x][y] - 0.5) * (phi[x][y] - 0.5)) / w * (ex[z] * ni[x][y] + ey[z] * nj[x][y]);

				hlp[z] = wa[z] * ef[z];

				heq[z] = phi[x][y] * gamma[z] - 0.5 * hlp[z];

				if (is_solid_node[x][y] == 0) {


					h[z][x][y] = h[z][x][y] * (1. - w_c) + heq[z] * w_c + hlp[z];


				}

				geq[z] = p[x][y] * wa[z] + gaWa[z];

				gneq[z] = g[z][x][y] - geq[z];

			}


			fpx = -p[x][y] * drho3 * dphidx[x][y];
			fpy = -p[x][y] * drho3 * dphidy[x][y];

			tauu = tauL + phi[x][y] * (tauH - tauL);

			ViscousForceCal(tauu, dphidx[x][y], dphidy[x][y], gneq, fmx, fmy);


			fx = mu[x][y] * dphidx[x][y] + fpx + fmx ;
			fy = mu[x][y] * dphidy[x][y] + fpy + fmy;

			for (z = 0; z < 9; z++) {

				ef[z] = ex[z] * fx + ey[z] * fy;
				hlp[z] = 3. * wa[z] * ef[z] / rho[x][y];
				geq[z] = p[x][y] * wa[z] + gaWa[z] - 0.5 * hlp[z];



				if (is_solid_node[x][y]==0) {



					g[z][x][y] = g[z][x][y] * (1. - (1. / tauu)) + geq[z] * (1. / tauu) + hlp[z];



				}
				

			}


		}


	}


}