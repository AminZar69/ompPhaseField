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
#include "../include/propagation.h"

void Propagation(double f[9][nx+2][ny+2]) {
	int x, y, z;
	double fnew[8][nx][ny];

	#pragma omp parallel for private(y, z) schedule(static) collapse(2)
		for (x = 0; x < nx; x++) {

			for (y = 0; y < ny; y++) {

				for (z = 1; z < 9; z++) {


					fnew[z-1][x][y] = f[z][x+1 - ex[z]][y+1 - ey[z]];

				}
			}
	}
	#pragma omp parallel for private(y, z) schedule(static) collapse(2)
	for (x = 0; x < nx; x++) {

		for (y = 0; y < ny; y++) {

			for (z = 1; z < 9; z++) {

				f[z][x+1][y+1] = fnew[z-1][x][y];

			}
		}
	}


}