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
    //Distribute spheres to the pbc
    origin.allocate_spheres(pbc, dim);

}

void monte_carlo(std::vector<std::vector<std::vector<Box>>>& pbc, double cube_len){
    int x=1, y=0, z=0, x1=0, y1=0, z1=0;
    int start=0;
    int end=0;
    bool next=false;
    int ax[3] = {x, y, z};
    pbc[0][0][0].optimize(ax, 100, cube_len);
    while (end <= std::pow(pbc.size(),3)){
        if (x1 == pbc.size()){
            y1++;
            x = 0;
        }
        if (y1 == pbc.size()){
            z1++;
            y1 = 0;
        }
        
        if (z1 == pbc.size()){
            move_spheres(pbc, start, end, cube_len);
            break;
        }
        if(pbc[x][y][z].check_sim(pbc[x1][y1][z1])){
                    end++;
                }
        else {
            move_spheres(pbc, start, end, cube_len);
            start = end;
            x = x1, y=y1, z=z1;
            pbc[x][y][z].optimize(ax, 100, cube_len);
        }
        x1++;
    }
}

void move_spheres(std::vector<std::vector<std::vector<Box>>>& pbc, int start, int end, double cube_len){
        int z1 = (int)start/16;
        int y1 = (int)(start-z1*16)/4;
        int x1 = start-y1*4-z1*16;
    for (int i=start+1; i <end; i++){
        int z = (int)i/16;
        int y = (int)(i-z*16)/4;
        int x = i-y*4-z*16;
        pbc[x1][y1][z1].copy_spheres(&pbc[x][y][z], cube_len*(x1-x), cube_len*(y1-y), cube_len*(z1-z));
    }
}
float rand_num(float lower_lim, float upper_lim){
    /*
    This method for generatong random numbers is based on this code https://stackoverflow.com/a/7560564
    */
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_real_distribution<> distr(lower_lim, upper_lim); // define the range
    return distr(gen);
}

main() {
}
