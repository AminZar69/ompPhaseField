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
#include "../include/periodicpopulations.h"


void PeriodicPopulations(double f[9][nx+2][ny+2]) {

	int x, y, z;
	#pragma omp parallel
	{
		#pragma omp for private(z) schedule(static) collapse(2)
			for (y = 0; y < ny+2; y++) {
				
				for (z = 0; z < 9; z++) {

					//--left and right boundaries
					f[z][0][y] = f[z][nx][y]; 	


					f[z][nx + 1][y] = f[z][1][y]; 	

				}
			}
		#pragma omp for private(z) schedule(static) collapse(2)
			for (x = 0; x < nx+2; x++) {
				
				for (z = 0; z < 9; z++) {

					//--bottom and top boundaries
					f[z][x][0] = f[z][x][ny];   


					f[z][x][ny + 1] = f[z][x][1];	
				}

			}

		}


}