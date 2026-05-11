project := ompPhasefield
CXX     := g++

srcdir := src
objdir := obj
bindir := bin

# Build mode: debug (default), release, or profile
# Override with: make BUILD=release   or   make release / make profile
BUILD ?= debug

# Common flags
cxxflags_common := -fopenmp -Wall -Wextra -std=c++17 -MMD -MP

# Mode-specific flags 
cxxflags_release := -O3 -DNDEBUG -march=native -flto
cxxflags_debug   := -O0 -g -DDEBUG
cxxflags_profile := -O3 -g -DNDEBUG -march=native -fno-omit-frame-pointer -flto

ifeq ($(BUILD),debug)
    cxxflags := $(cxxflags_common) $(cxxflags_debug)
else ifeq ($(BUILD),profile)
    cxxflags := $(cxxflags_common) $(cxxflags_profile)
else
    cxxflags := $(cxxflags_common) $(cxxflags_release)
endif

# Sources and objects 
sources := main.cpp initialization.cpp periodicphi.cpp gradientcal.cpp \
           interfacenormal.cpp chemicalpotential.cpp setsolid.cpp \
           output.cpp periodicpopulations.cpp collision.cpp propagation.cpp \
           stresstensorcal.cpp viscousforcecal.cpp phical.cpp hydrocal.cpp \
           maxcal.cpp totalmass.cpp

objects := $(sources:%.cpp=$(objdir)/%.o)
deps    := $(objects:.o=.d)

# Targets 
.PHONY: all clean debug release profile

all: $(bindir)/$(project)

debug:
	$(MAKE) BUILD=debug

release:
	$(MAKE) BUILD=release

profile:
	$(MAKE) BUILD=profile

# ---- Linking ----
$(bindir)/$(project): $(objects) | $(bindir)
	$(CXX) $(objects) -o $@ $(cxxflags)

# Compilation 
$(objdir)/%.o: $(srcdir)/%.cpp | $(objdir)
	$(CXX) -c $< -o $@ $(cxxflags)

# Ensure output directories exist
$(objdir):
	mkdir -p $(objdir)

$(bindir):
	mkdir -p $(bindir)

# Clean 
clean:
	rm -f $(objdir)/*.o $(objdir)/*.d
	rm -f $(bindir)/*

# Include auto-generated header dependencies
-include $(deps)