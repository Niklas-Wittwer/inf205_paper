#include <iostream>
#include <random>


#include "box.h"
#include "sphere.h"

/*
Utility functions for our algorithm
*/

void create_pbc(Box origin, std::vector<std::vector<std::vector<Box>>>& pbc, int dim){
    /*
    This function copies the spheres from the original box to the sub boxes while inheriting the structure and logic with the components map and the 2d particles vector
    
    input:
    Box origin: Box to copy spheres from
    vector<<<spheres>>> pbc: 3d vector with box objects
    int dim: dimensions of the 3d vector
    */
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

void move_spheres(std::vector<std::vector<std::vector<Box>>>& pbc, int start, int end, double cube_len){
    /*
    Copying the position of the spheres from the start element in pbc to the following elements/boxes. 
    Start and end are translated to 3d coordinates assuming a 4x4x4 3d vector (sub cube/box)
    input:
    vector<<<spheres>>> pbc: 3d vector with box objects
    int start: start element to be translated to 3d, min 0 and max 63
    int end: End element to be translated to 3d
    double cube_len: length the sub box/cube
    */
   
        int z1 = (int)start/16;
        int y1 = (int)(start-z1*16)/4;
        int x1 = start-y1*4-z1*16;
    for (int i=start+1; i <end; i++){
        int z = (int)i/16;
        int y = (int)(i-z*16)/4;
        int x = i-y*4-z*16;
        pbc[z1][y1][x1].copy_spheres(pbc[z][y][x], cube_len*(z1-z), cube_len*(y1-y), cube_len*(x1-x));
    }

}

void monte_carlo(std::vector<std::vector<std::vector<Box>>>& pbc, double cube_len){
    /*
    This is our implementation of the monte carlo algorithm
    The first cube with n spheres will be optimized and the solution copied to the other cubes
    with an equal amount of spheres. From the allocation, it should be at most 4 (same amount as different radii spheres) different
    cubes
    input:
    vector<<<spheres>>> pbc: 3d vector with box objects
    double cube_len: length the sub box/cube
    */
    int x=1, y=0, z=0, x1=0, y1=0, z1=0;
    int start=0;
    int end=0;
    bool next=false;
    int ax[3] = {z1, y1, x1};
    pbc[0][0][0].optimize(ax, 200, cube_len);
    while (end <= std::pow(pbc.size(),3)){
        if (x1 == pbc.size()){
            y1++;
            x1 = 0;
        }
        if (y1 == pbc.size()){
            z1++;
            y1 = 0;
        }
        
        if (z1 == pbc.size()){
            std::cout << "\n so that just happened";
            move_spheres(pbc, start, end, cube_len);
            break;
        }
        if(pbc[z][y][x].check_sim(pbc[z1][y1][x1])){
                    end++;
                }
        else {
            if (start != end){
            // If there's only one sphere with a specific dimension no spheres need to be moved
            move_spheres(pbc, start, end, cube_len);
            start = end;
            }
            ax[0] = z1, ax[1]=y1, ax[2]=x1;
            x = x1, y=y1, z=z1;
            std::cout <<"zyx: "<<z <<y<<x;
            pbc[z][y][x].optimize(ax, 200, cube_len);
        
            
        }
       x1++;
        
    }
}


double rand_num_gen(double lower_lim, double upper_lim){
    /*
    This method for generatong random numbers is based on this code https://stackoverflow.com/a/7560564
    lower and upper limit are inclusive
    Input:
    double lower_lim: lower bound of the  generation
    double upper_lim: upper bound of the generation
    Output:
    double distr: random float/double between the lower and upper limit
    */
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_real_distribution<> distr(lower_lim, upper_lim); // define the range
    return distr(gen);
}
