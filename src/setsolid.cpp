#include <cstring>
#include "../include/common.h"
#include "../include/setsolid.h"

void SetSolid() {

    // memset to 0 in a single call 
    std::memset(is_solid_node, 0, sizeof(is_solid_node));

    	
    // for (int x = 0; x < nx + 2; x++) {
    //     for (int y = 0; y < ny + 2; y++) {

    //         is_solid_node[x][y] = 0;
    //     }
    // }

}