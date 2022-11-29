#include<iostream>
#include<cmath>
#include "box.h"
#include "utils.h"
/*
Main runfile for the algorithm
*/


int main(Box original) {
    // Create pbc and assign their spheres
    int n_pbc = std::pow(4,3);
    Box *pbc = new Box[n_pbc];
    create_pbc(original, pbc);

    //monte carlo

    //move spheres in original box

    delete [] pbc;
}


