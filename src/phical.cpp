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
#include "../include/phical.h"

void PhiCal() {
	
	int x, y;


	#pragma omp parallel for private(x) schedule(static) collapse(2)

	for (y = 1; y < ny + 1; y++) {

		for (x = 1; x < nx + 1; x++) {

			if (is_solid_node[x][y]==0) {


				phi[x][y] = h[0][x][y] + h[1][x][y] + h[2][x][y] + h[3][x][y] + h[4][x][y] +\
						h[5][x][y] + h[6][x][y] + h[7][x][y]+ h[8][x][y];



				rho[x][y] = rhoL + phi[x][y] * (rhoH - rhoL);
			}

		}
	}


}