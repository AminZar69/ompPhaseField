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
#include "../include/viscousforcecal.h"
#include "../include/stresstensorcal.h"


void ViscousForceCal(double tau, double dphidx, double dphidy, double gneq[9], double &fmx, double &fmy) {

	double sxx, sxy, syy;

		StressTensorCal(gneq, sxx, sxy, syy);
		
		fmx = (0.5 - tau) / tau * (sxx*dphidx + sxy * dphidy) * (rhoH - rhoL);
		fmy = (0.5 - tau) / tau * (sxy*dphidx + syy * dphidy) * (rhoH - rhoL);

}