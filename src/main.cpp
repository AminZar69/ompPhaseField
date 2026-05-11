/* ============================== License GPLv3 ===================================
    ompPhaseField is a multiphase flow solver based on the lattice Boltzmann method
    accelerated by utilising OpenMP.
    Copyright (C) 2021 Amin Zar, aminpopjoury@gmail.com
    GPLv3 — see <https://www.gnu.org/licenses/>.
 ================================================================================ */

#include <iostream>
#include <iomanip>
#include <omp.h>
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


 // Simulation control 
const int    tf = 10000;
const int    step = 5000; // Determines when to write the result file

// Physical parameters
const double r = 30;
const double rhoL = 0.01;
const double rhoH = 1.0;
const double drho3 = (rhoH - rhoL) / 3.0;
const double tauH = 0.8;
const double tauL = 0.8;
const double sigma = 0.001;
const double w = 4.0;
const double beta = 12.0 * sigma / w;
const double kappa = 1.5 * sigma * w;
const double m = 0.02;
const double w_c = 1.0 / (0.5 + 3.0 * m);

// D2Q9 lattice constants
const int    ex[9] = { 0, 1, 0,-1, 0, 1,-1,-1, 1 };
const int    ey[9] = { 0, 0, 1, 0,-1, 1, 1,-1,-1 };
const double wa[9] = { 4.0 / 9.0,
                       1.0 / 9.0,  1.0 / 9.0,  1.0 / 9.0,  1.0 / 9.0,
                       1.0 / 36.0, 1.0 / 36.0, 1.0 / 36.0, 1.0 / 36.0 };

// ime step counter
int t;

// Solid node mask 
int is_solid_node[(nx + 2)][(ny + 2)];

// Distribution functions
double h[(nx + 2)][(ny + 2)][9];
double g[(nx + 2)][(ny + 2)][9];


double phi[(nx + 2)][(ny + 2)];
double p[(nx + 2)][(ny + 2)];
double mu[(nx + 2)][(ny + 2)];
double dphidx[(nx + 2)][(ny + 2)];
double dphidy[(nx + 2)][(ny + 2)];
double rho[(nx + 2)][(ny + 2)];
double ux[(nx + 2)][(ny + 2)];
double uy[(nx + 2)][(ny + 2)];
double ni[(nx + 2)][(ny + 2)];
double nj[(nx + 2)][(ny + 2)];


int main() {

    double startTime = omp_get_wtime();

    SetSolid();
    Initialization();

    std::cout << "\n===================================================\n";
    std::cout << std::setw(4) << "Time"
        << std::setw(14) << "uxMax"
        << std::setw(14) << "uyMax"
        << std::setw(14) << "massPhi" << "\n";
    std::cout << "===================================================\n";

    for (t = 0; t <= tf; t++) {

        if (t % (step / 5) == 0) {
            std::cout << std::setw(7) << t
                << std::setw(15) << std::scientific << std::setprecision(4) << MaxCal(ux)
                << std::setw(14) << MaxCal(uy)
                << std::setw(14) << std::fixed << std::setprecision(6) << TotalMass(phi)
                << "\n";
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

    double finishTime = omp_get_wtime();

    std::cout << "\n===================================================\n";
    std::cout << " Elapsed Time: " << std::setw(10) << (finishTime - startTime) << "\n";
    std::cout << "===================================================\n";

    return 0;
}