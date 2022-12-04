#include <iostream>
#include <fstream>

#include <stdio.h>
#include <cmath>
#include "box.h"
#include "utils.h"
/*
Main runfile for the algorithm
*/


int main(int argc, char** argv) {
    Box original;
    // Get original box from the generator
    std::ifstream file_in(argv[1]);
    file_in >> original;
    file_in.close();

    // Create 3d vector for pbc 
    int dim_pbc = 4;
    std::vector<std::vector<std::vector<Box>>> pbc(dim_pbc, std::vector<std::vector<Box>>(dim_pbc, std::vector<Box>(dim_pbc, Box())));
    create_pbc(original, pbc, dim_pbc);
    std::cout <<"num overlaps in pbc1 " <<pbc[0][0][0].count_overlaps();
    //monte carlo algorithm
    monte_carlo(pbc, original.get_extensions(0)/dim_pbc);

    std::string output_name = "benchmark-configuration.dat";
    // file output for benchmarking
    std::ofstream fout(output_name);
    if(!fout) return EXIT_FAILURE;
    fout << original;
    fout.close();
    std::cout << "\nDone.\n\n";

}


