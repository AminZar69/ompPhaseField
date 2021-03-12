project := ompPhasefield
cc := g++
cxxflags := -fopenmp
srcdir := src
objdir := obj
bindir := bin
objects	:= $(objdir)/main.o $(objdir)/initialization.o $(objdir)/periodicphi.o $(objdir)/gradientcal.o $(objdir)/interfacenormal.o $(objdir)/chemicalpotential.o $(objdir)/setsolid.o $(objdir)/output.o $(objdir)/periodicpopulations.o $(objdir)/collision.o $(objdir)/propagation.o $(objdir)/stresstensorcal.o $(objdir)/viscousforcecal.o $(objdir)/phical.o $(objdir)/hydrocal.o $(objdir)/maxcal.o $(objdir)/totalmass.o  

all: $(project)

####Linking####
$(project): $(objects) 
	$(cc) $(objects) -o $(bindir)/$(project) $(cxxflags)
	
####Compilation####	
$(objdir)/initialization.o: $(srcdir)/initialization.cpp
	$(cc) -c $(srcdir)/initialization.cpp -o $(objdir)/initialization.o $(cxxflags)
	
$(objdir)/periodicphi.o: $(srcdir)/periodicphi.cpp
	$(cc) -c $(srcdir)/periodicphi.cpp -o $(objdir)/periodicphi.o $(cxxflags)
	
$(objdir)/gradientcal.o: $(srcdir)/gradientcal.cpp
	$(cc)  -c $(srcdir)/gradientcal.cpp -o $(objdir)/gradientcal.o $(cxxflags)
	
$(objdir)/interfacenormal.o: $(srcdir)/interfacenormal.cpp
	$(cc)  -c $(srcdir)/interfacenormal.cpp -o $(objdir)/interfacenormal.o $(cxxflags)
	
$(objdir)/chemicalpotential.o: $(srcdir)/chemicalpotential.cpp
	$(cc)  -c $(srcdir)/chemicalpotential.cpp -o $(objdir)/chemicalpotential.o $(cxxflags)
	
$(objdir)/setsolid.o: $(srcdir)/setsolid.cpp
	$(cc)  -c $(srcdir)/setsolid.cpp -o $(objdir)/setsolid.o $(cxxflags)
	
$(objdir)/output.o: $(srcdir)/output.cpp
	$(cc)  -c $(srcdir)/output.cpp -o $(objdir)/output.o $(cxxflags)
	
$(objdir)/periodicpopulations.o: $(srcdir)/periodicpopulations.cpp
	$(cc)  -c $(srcdir)/periodicpopulations.cpp -o $(objdir)/periodicpopulations.o $(cxxflags)
	
$(objdir)/collision.o: $(srcdir)/collision.cpp
	$(cc)  -c $(srcdir)/collision.cpp -o $(objdir)/collision.o $(cxxflags)
	
$(objdir)/propagation.o: $(srcdir)/propagation.cpp
	$(cc)  -c $(srcdir)/propagation.cpp -o $(objdir)/propagation.o $(cxxflags)
	
$(objdir)/stresstensorcal.o: $(srcdir)/stresstensorcal.cpp
	$(cc)  -c $(srcdir)/stresstensorcal.cpp -o $(objdir)/stresstensorcal.o $(cxxflags)
	
$(objdir)/viscousforcecal.o: $(srcdir)/viscousforcecal.cpp
	$(cc)  -c $(srcdir)/viscousforcecal.cpp -o $(objdir)/viscousforcecal.o $(cxxflags)
	
$(objdir)/phical.o: $(srcdir)/phical.cpp
	$(cc)  -c $(srcdir)/phical.cpp -o $(objdir)/phical.o $(cxxflags)
	
$(objdir)/hydrocal.o: $(srcdir)/hydrocal.cpp
	$(cc)  -c $(srcdir)/hydrocal.cpp -o $(objdir)/hydrocal.o $(cxxflags)
	
$(objdir)/maxcal.o: $(srcdir)/maxcal.cpp
	$(cc)  -c $(srcdir)/maxcal.cpp -o $(objdir)/maxcal.o $(cxxflags)
	
$(objdir)/totalmass.o: $(srcdir)/totalmass.cpp
	$(cc)  -c $(srcdir)/totalmass.cpp -o $(objdir)/totalmass.o $(cxxflags)
	
$(objdir)/main.o: $(srcdir)/main.cpp
	$(cc)  -c $(srcdir)/main.cpp -o $(objdir)/main.o $(cxxflags)
	
########
	
clean:	
	
	rm -f $(objdir)/*
	rm -f $(bindir)/*
	
	
	