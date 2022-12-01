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
    // Create pbc 
    std::vector<std::vector<std::vector<Box>>> pbc(4, std::vector<std::vector<Box>>(4, std::vector<Box>(4, Box())));
    create_pbc(original, pbc);

    //monte carlo

    //move spheres in original box

}


