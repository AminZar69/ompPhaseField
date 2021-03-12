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

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include<omp.h>
#include "../include/common.h"
#include "../include/setsolid.h"
#include "../include/initialization.h"
#include "../include/maxcal.h"
#include "../include/totalmass.h"
#include "../include/collision.h"
#include "../include/periodicpopulations.h"
#include "../include/propagation.h"
#include "../include/phical.h"
#include "../include/hydrocal.h"
#include "../include/output.h"

using namespace std;

//const int numThreads = 20;
const int tf = 15000;
const int step = 5000;
const double r = 30;
const double rhoL = 0.01;
const double rhoH = 1.;
const double drho3 = (rhoH - rhoL) / 3.;
const double tauH = 0.8;
const double tauL = 0.8;
const double sigma = 0.001;
const double w = 4.;
const double beta = 12. * sigma / w;
const double kappa = 1.5 * sigma*w;
const double m = 0.02;
const double w_c = 1. / (0.5 + 3.*m);


const int ex[9] = { 0, 1, 0,-1, 0, 1,-1,-1, 1 };
const int ey[9] = { 0, 0, 1, 0,-1, 1, 1,-1,-1 };
const double wa[9] = { 4. / 9., 1. / 9., 1. / 9., 1. / 9., 1. / 9., 1. / 36., 1. / 36., 1. / 36., 1. / 36. };

int t;
int is_solid_node[(nx + 2)][(ny + 2)];
double h[9][(nx + 2)][(ny + 2)], g[9][(nx + 2)][(ny + 2)];
double phi[(nx + 2)][(ny + 2)], p[nx+1][ny+1], mu[nx+1][ny+1], dphidx[nx+1][ny+1], dphidy[nx+1][ny+1];
double rho[nx+1][ny+1], ux[nx+1][ny+1], uy[nx+1][ny+1], ni[nx+1][ny+1], nj[nx+1][ny+1];




int main()
{


	//omp_set_num_threads(numThreads);
	
	double startTime2 = omp_get_wtime();

	//clock_t startTime = clock();

	SetSolid();
	
	Initialization();


	cout<<endl<<"==================================================="<<endl;
	//----------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------
	cout<<endl<< setw(4) << "Time" << setw(14) << "uxMax" << setw(14) << "uyMax" << setw(14)<< "massPhi"<< endl;
	//----------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------
	
	cout<<endl<<"==================================================="<<endl;

	for (t = 0; t <= tf; t++) {



		if (t % (step/5) == 0) {

			printf("\n %2.6i %15.4e %13.4e %13.6f \n", t, MaxCal(ux), MaxCal(uy), TotalMass(phi));


		}
		
		if (t % step == 0) {

			Output();

		}

		Collision();

		PeriodicPopulations(h);

		PeriodicPopulations(g);
		
		Propagation(h);
		
		Propagation(g);

		PhiCal();
		
		HydroCal();


	}

	//clock_t finishTime = clock();

	double finishTime2 = omp_get_wtime();

	cout<<endl<<"==================================================="<<endl;

	//cout<<endl<<" Elapsed Time:"<<setw(10)<<(finishTime-startTime) / double(CLOCKS_PER_SEC)<<endl;
	cout<<endl<<" Elapsed Time:"<<setw(10)<<(finishTime2-startTime2)<<endl;

	cout<<endl<<"==================================================="<<endl;



	return(0);

}