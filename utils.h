#ifndef UTILS_H
#define UTILS_H
#include "utils.cpp"
#include "box.h"
/*
Header file for functions related to our algorithm
*/

void create_pbc(Box origin, std::vector<std::vector<std::vector<Box>>>& pbc, int dim);

void monte_carlo(Box box1){};
void move_spheres(Box optimal_pos, int n){};

#endif