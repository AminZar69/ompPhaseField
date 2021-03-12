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

#include <cmath>
#include <cstdlib>
#include "../include/common.h"
#include "../include/periodicphi.h"
#include "../include/chemicalpotential.h"
#include "../include/gradientcal.h"
#include "../include/interfacenormal.h"

void Initialization() {

int x, y, z;
double gamma[9], gaWa[9], heq[9], geq[9], hlp[9], ef[9], u2, eu[9];
double ri;

	for (y = 0; y <= (ny + 1); y++) {
		for (x = 0; x <= (nx + 1); x++) {

			ri = sqrt(((x - nx/2.) * (x - nx/2.)) + ((y - nx/2.) * (y - nx/2.)));
			
			phi[x][y] = 0.5 + 0.5 * tanh((2. * (r - ri)) / w);	
		   
		}
	}

	for (x = 0; x < nx+2; x++) {
		for (y = 0; y < ny+2; y++) {
			for (z = 0; z < 9; z++) {
				h[z][x][y] = 0;
				g[z][x][y] = 0;
			}
		}
	}
	
	
	PeriodicPhi(phi);
	ChemicalPotential();
	GradientCal();
	InterfaceNormal();

	for (y= 1; y < ny + 1; y++) {
		for (x= 1; x < nx + 1; x++) {

			rho[x][y] = rhoL + phi[x][y] * (rhoH - rhoL);
			p[x][y] = 0.;//p[x][y] + phi[x][y] * sigma/r /(rho[x][y]/3.);
			ux[x][y] =0.;
			uy[x][y] =0.;
		

		
			u2 = ux[x][y] * ux[x][y] + uy[x][y] * uy[x][y];
	
			for (z = 0; z < 9; z++) {
				
				eu[z] = ex[z] * ux[x][y] + ey[z] * uy[x][y];

				gaWa[z] = wa[z] * (eu[z] * (3. + 4.5*eu[z]) - 1.5*u2);

				gamma[z] = gaWa[z] + wa[z];

		

				ef[z] = (1. - 4. * (phi[x][y] - 0.5) * (phi[x][y] - 0.5)) / w * (ex[z] * ni[x][y] + ey[z] * nj[x][y]);

				hlp[z] = wa[z] * ef[z];

				h[z][x][y] = phi[x][y] * gamma[z] - 0.5 * hlp[z];

				

				g[z][x][y] = p[x][y] * wa[z] + gaWa[z];
		
				
				
			}
		
		}
	
	}
	
}