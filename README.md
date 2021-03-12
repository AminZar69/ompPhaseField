## Multiphase LBM solver parallelised by OpenMP
"ompPhaseField" is a multiphase LBM solver which has been speeded up by using the OpenMP API. The code models
the 2D case free droplet at equilibrium surrounded by an ambient immiscible phase. Using this code and adding suitable boundary conditions, more complex problems such as multiphase flow in porous media can be simulated. The corresponding functions for applying wettability condition and constant inlet/outlet pressure will be added in future commits. 
### Requirements
The g++ compiler is the only requirement for running this package. The "-fopenmp" flag has been added for compilation and linking in the Makefile. The output files are generated in the ascii VTK format readable by the paraview which is an open-source visualisation package found via <https://www.paraview.org/download/>.

### Build and execution
    make clean
    make
    cd bin
    ./ompPhasefield
    
### Example of use
The number of threads can be chosen via setting the environment variable OMP_NUM_THREADS to the desired as shown below:
    
    export OMP_NUM_THREADS=20

In order to change the domain size `nx` and `ny` in the `common.h` should be changed. Other simulation parameters can be modified through `main.cpp` source file.    