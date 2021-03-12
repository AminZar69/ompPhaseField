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
#include "../include/common.h"
#include "../include/setsolid.h"

void SetSolid() {
	
	int x, y;

	for (y = 0; y <= ny + 1; y++) {

		for (x = 0; x <= nx + 1; x++) {

			is_solid_node[x][y] = 0;

		}

	}

}