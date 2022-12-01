#include <iostream>
#include <random>


#include "box.h"
#include "sphere.h"

/*
Utility functions for our algorithm
*/

void create_pbc(Box origin, std::vector<std::vector<std::vector<Box>>>& pbc){
    // Get size from original box and set sizes of sub boxes
    float dx = origin.get_extensions(0)/4; 
    float dy = origin.get_extensions(1)/4; 
    float dz = origin.get_extensions(2)/4; 
    
    for (int i = 0; i < pbc.size(); i++) {
        for (int j = 0; j < pbc[i].size(); j++) {
            for (int k = 0; k < pbc[i][j].size(); k++) {
                pbc[i][j][k].set_extension(dx, dy, dz);
            }
        }
    }

/*
    for (int i; i < sizeof(pbc)/sizeof(pbc[0]); i++) {
        pbc[i].set_extension(dx, dy, dz);
    }
*/
    // Adding the spheres to its belonging sub boxes
    for (auto i = begin (origin.particles); i != end(origin.particles); ++i){
        std::cout << (*i)[0].get_size();
    }
}
void monte_carlo(Box box1){}
void move_spheres(Box optimal_pos, int n){}
double rand_pos(double xlim, double ylim, double zlim){
    
}
float rand_num(float lower_lim, float upper_lim){
    std::uniform_real_distribution<> distr(lower_lim, upper_lim);
}

