#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "../include/common.h"
#include "../include/output.h"

void Output() {

    int t2 = t / step;

    std::string num = std::to_string(t2);
    std::string padded = std::string(std::max(0, 7 - (int)num.length()), '0') + num;
    std::string filename = "xml_" + padded + ".vtr";

    std::ofstream file1(filename);

    // VTK header 
    file1 << "<?xml version='1.0'?>\n";
    file1 << "<VTKFile type='RectilinearGrid' version='0.1' byte_order='LittleEndian'>\n";
    file1 << "<RectilinearGrid WholeExtent='1 " << nx << " 1 " << ny << " 1 1'>\n";
    file1 << "<Piece Extent='1 " << nx << " 1 " << ny << " 1 1'>\n";

    // Coordinates
    file1 << "<Coordinates>\n";

    file1 << "<DataArray type='Float32' Name='X' NumberOfComponents='1' format='ascii'>\n";
    for (int x = 1; x < nx + 1; x++) file1 << x << '\n';
    file1 << "</DataArray>\n";

    file1 << "<DataArray type='Float32' Name='Y' NumberOfComponents='1' format='ascii'>\n";
    for (int y = 1; y < ny + 1; y++) file1 << y << '\n';
    file1 << "</DataArray>\n";

    file1 << "<DataArray type='Float32' Name='Z' NumberOfComponents='1' format='ascii'>\n";
    file1 << 1 << '\n';
    file1 << "</DataArray>\n";

    file1 << "</Coordinates>\n";

    // PointData
    file1 << "<PointData>\n";

    file1 << "<DataArray type='Float32' Name='Phi' NumberOfComponents='1' format='ascii'>\n";
    for (int y = 1; y < ny + 1; y++)
        for (int x = 1; x < nx + 1; x++)
            file1 << phi[x][y] << '\n';
    file1 << "</DataArray>\n";

    file1 << "<DataArray type='Float32' Name='Pressure' NumberOfComponents='1' format='ascii'>\n";
    for (int y = 1; y < ny + 1; y++)
        for (int x = 1; x < nx + 1; x++)
            file1 << p[x][y] << '\n';
    file1 << "</DataArray>\n";

    file1 << "<DataArray type='Float32' Name='Velocity' NumberOfComponents='3' format='ascii'>\n";
    for (int y = 1; y < ny + 1; y++)
        for (int x = 1; x < nx + 1; x++)
            file1 << ux[x][y] << std::setw(20) << uy[x][y] << std::setw(20) << 0 << '\n';
    file1 << "</DataArray>\n";

    file1 << "</PointData>\n";
    file1 << "</Piece>\n";
    file1 << "</RectilinearGrid>\n";
    file1 << "</VTKFile>\n";

    file1.close();
}