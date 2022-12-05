#include <iostream>
#include <fstream>
#include <chrono>
#include <stdio.h>
#include <cmath>

#include "utils.h"
#include <cassert>
/*
	./evaluate-confguration benchmark-configuration.dat

Main runfile for the algorithm

*/


int main(int argc, char** argv) {

    Box original;
    // Get original box from the generator
    assert(argc > 1);
    std::ifstream file_in(argv[1]);
    file_in >> original;
    file_in.close();
    auto t0 = std::chrono::high_resolution_clock::now();

    // Create 3d vector for pbc 
    int dim_pbc = 4;
    std::vector<std::vector<std::vector<Box>>> pbc(dim_pbc, std::vector<std::vector<Box>>(dim_pbc, std::vector<Box>(dim_pbc, Box())));
    create_pbc(original, pbc, dim_pbc);
    //monte carlo algorithm
    monte_carlo(pbc, original.get_extensions(0)/dim_pbc);
    //clear original box and deallocate spheres
    original.clear_particles();
    original.deallocate_spheres(pbc);

    auto t1 = std::chrono::high_resolution_clock::now();
    auto delta_t01 = std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count();
    std::cout << "Runtime algorithm:\t" << 1.0e-06*delta_t01 << " s\n";
    std::string output_name = "algo-configuration.dat";

    // file output for benchmarking
    std::ofstream fout(output_name);
    if(!fout) return EXIT_FAILURE;
    fout << original;
    fout.close();
    std::cout << "\nDone.\n\n";

}


