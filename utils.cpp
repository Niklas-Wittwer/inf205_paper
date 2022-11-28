#include <iostream>
#include <random>


#include "box.h"
#include "sphere.h"

/*
Utility functions for our algorithm
*/

void create_pbc(Box origin){
    // TODO: This doesn't work!! Find a way to add 100 class objects and alter their extensions. Add ass components to original box?
    float dx = origin.get_extensions(0)/100; 
    float dy = origin.get_extensions(1)/100; 
    float dz = origin.get_extensions(2)/100; 
    for (int i; i < 100; i++) {
        Box a;
        a.set_extension(dx, dy, dz);
    }
}
void monte_carlo(Box box1){}
void move_spheres(Box optimal_pos, int n){}
double rand_pos(double xlim, double ylim, double zlim){
    
}
float rand_num(float lower_lim, float upper_lim){
    std::uniform_real_distribution<> distr(lower_lim, upper_lim);
}

