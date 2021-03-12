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
#include "../include/periodicphi.h"

void PeriodicPhi(double a[nx+2][ny+2]) {
	
	int x, y;

	#pragma omp parallel
	{
		#pragma omp for
		for (x = 0; x <= nx + 1; x++) {

			a[x][0] = a[x][ny];
			
			a[x][ny + 1] = a[x][1];  

		}
		#pragma omp for
		for (y = 0;y <= ny + 1;y++) {

			a[0][y] = a[nx][y]; 
			
			a[nx + 1][y] = a[1][y];  


		}
		
	}

}