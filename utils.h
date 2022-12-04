#ifndef UTILS_H
#define UTILS_H
#include "utils.cpp"
#include "box.h"
/*
Header file for functions related to our algorithm
*/

void create_pbc(Box origin, std::vector<std::vector<std::vector<Box>>>& pbc, int dim);

void monte_carlo(std::vector<std::vector<std::vector<Box>>>& pbc, double cube_len);
void move_spheres(std::vector<std::vector<std::vector<Box>>>& pbc, int start, int end, double cube_len);

#endif