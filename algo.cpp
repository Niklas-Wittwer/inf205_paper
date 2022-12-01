#include <iostream>
#include <stdio.h>
#include <cmath>
#include "box.h"
#include "utils.h"
/*
Main runfile for the algorithm
*/


int main(Box original) {
    // Get limits from the box
    // Create 3d vector for pbc 
    int dim_pbc = 4;
    std::vector<std::vector<std::vector<Box>>> pbc(dim_pbc, std::vector<std::vector<Box>>(dim_pbc, std::vector<Box>(dim_pbc, Box())));
    create_pbc(original, pbc, dim_pbc);
    std::cout <<"num overlaps in pbc1 " <<pbc[0][0][0].count_overlaps();
    //monte carlo

    //move spheres in original box

}


