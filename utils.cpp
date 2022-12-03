#include <iostream>
#include <random>


#include "box.h"
#include "sphere.h"

/*
Utility functions for our algorithm
*/
/*
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
*/
void monte_carlo(std::vector<std::vector<std::vector<Box>>>& pbc){
    Box temp_box;
    
}
void move_spheres(int start, int end){
    for (int i=start; i <end; i++){
        int z = (int)i/16;
        int y = (int)(i-z*16)/4;
        int x = i-y*4-z*16;
        
        std::cout << x<< " " << y << " "<< z<< "\n";
    }
}
//double rand_pos(double xlim, double ylim, double zlim){}
//float rand_num(float lower_lim, float upper_lim){std::uniform_real_distribution<> distr(lower_lim, upper_lim);}

main() {
    Box a;
    move_spheres(8, 20);
}
