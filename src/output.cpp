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
#include "../include/common.h"
#include "../include/output.h"
using namespace std;

void Output() {

	
	string filename, form;
	int t2 = (int)(t/step);
	int x, y;

	switch(t2){
		case 0 ... 9:
			form = "xml_000000"+to_string(t2);
			break;
		case 10 ... 99:
			form = "xml_00000"+to_string(t2);
			break;
		case 100 ... 999:
			form = "xml_0000"+to_string(t2);
			break;
		case 1000 ... 9999:
			form = "xml_000"+to_string(t2);
			break;
		case 10000 ... 99999:
			form = "xml_00"+to_string(t2);
			break;
		case 100000 ... 999999:
			form = "xml_0"+to_string(t2);
			break;
		default:
			form = "xml_000000"+to_string(-1);
			break;

	}

	filename = form + ".vtr";

	ofstream file1;
		
		file1.open(filename, ios::out);

		file1<<"<?xml version='1.0'?>"<<endl;
		file1<<"<VTKFile type='RectilinearGrid' version='0.1' byte_order='LittleEndian'>"<<endl;
		file1<<"<RectilinearGrid WholeExtent='"<<"1"<< " " <<nx<< " " <<"1"<< " " <<ny<< " " << "1" << " " <<"1" << " " <<""<<"'>"<<endl;
		file1<<"<Piece Extent='"<<"1"<<" "<<nx<<" "<<"1"<<" "<<ny<<" "<<"1"<<" "<<"1"<< " " <<""<<"'>"<<endl;
		file1<<"<Coordinates>"<<endl;
		file1<<"<DataArray type='Float32' Name='X' NumberOfComponents='1' format='ascii'>"<<endl;

		for (x=1; x<nx+1; x++){

			file1<<x<<endl;
		}


		file1<<"</DataArray>"<<endl;


		file1<<"<DataArray type='Float32' Name='Y' NumberOfComponents='1' format='ascii'>"<<endl;
		for (y=1; y<ny+1; y++){

			file1<<y<<endl;
		}

		file1<<"</DataArray>"<<endl;

		file1<<"<DataArray type='Float32' Name='Z' NumberOfComponents='1' format='ascii'>"<<endl;


			file1<<1<<endl;


		file1<<"</DataArray>"<<endl;
		file1<<"</Coordinates>"<<endl;

		file1<<"<PointData>"<<endl;

		file1<<"<DataArray type='Float32' Name='Phi' NumberOfComponents='1' format='ascii'>"<<endl;

		for (y = 1; y < ny + 1; y++) {

			for (x = 1; x < nx + 1; x++) {

				file1<<phi[x][y]<<endl;
			}
		}


		file1<<"</DataArray>"<<endl;

		file1<<"<DataArray type='Float32' Name='Pressure' NumberOfComponents='1' format='ascii'>"<<endl;

		for (y = 1; y < ny + 1; y++) {

			for (x = 1; x < nx + 1; x++) {

				file1<<p[x][y]<<endl;
			}
		}


		file1<<"</DataArray>"<<endl;

		file1<<"<DataArray type='Float32' Name='Velocity' NumberOfComponents='3' format='ascii'>"<<endl;

		for (y = 1; y < ny + 1; y++) {

			for (x = 1; x < nx + 1; x++) {

				file1<<ux[x][y]<<setw(20)<<uy[x][y]<<setw(20)<<0<<endl;
			}
		}


		file1<<"</DataArray>"<<endl;

		file1<<"</PointData>"<<endl;

		file1<<"</Piece>"<<endl;
		file1<<"</RectilinearGrid>"<<endl;
		file1<<"</VTKFile>"<<endl;





	file1.close();
	

}