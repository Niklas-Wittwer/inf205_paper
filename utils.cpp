#include <iostream>
#include <random>


#include "box.h"
#include "sphere.h"

/*
Utility functions for our algorithm
*/

void create_pbc(Box origin, std::vector<std::vector<std::vector<Box>>>& pbc, int dim){
    // Get size from original box and set sizes of sub boxes
    float dx = origin.get_extensions(0)/dim; 
    float dy = origin.get_extensions(1)/dim; 
    float dz = origin.get_extensions(2)/dim; 
    
    // Set extensions for sub boxes. Not strictly nessecary for the algorithm
    for (int i = 0; i < pbc.size(); i++) {
        for (int j = 0; j < pbc[i].size(); j++) {
            for (int k = 0; k < pbc[i][j].size(); k++) {
                pbc[i][j][k].set_extension(dx, dy, dz);
            }
        }
    }
    // Allocate spheres to the pbc with an approxiomate equal distribution of same sized spheres
    for (auto i = begin (origin.particles); i != end(origin.particles); ++i){
        int x = 0, y = 0, z = 0;
        double curr_size = 0, prev_size = 0;
        if (curr_size != prev_size){
            x = 0, y = 0, z = 0;
            prev_size = curr_size;
        }
        if (x == 4){
            y++;
            x = 0;
        }
        if (y == 4){
            z++;
            y = 0;
        }
        if (z == 4){
            z = 0;
        }
        pbc[x][y][z].particles.push_back(i[0]);
        x++;
    }

}
void monte_carlo(Box box1){}
void move_spheres(Box optimal_pos, int n){}
double rand_pos(double xlim, double ylim, double zlim){
    
}
float rand_num(float lower_lim, float upper_lim){
    std::uniform_real_distribution<> distr(lower_lim, upper_lim);
}

