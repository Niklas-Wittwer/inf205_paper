#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>

#include "box.h"
#include "sphere.h"

int main(int argc, char** argv)
{
   assert(argc > 1);
   
   Box b;
   auto t0 = std::chrono::high_resolution_clock::now();
   std::ifstream file_in(argv[1]);
   file_in >> b;
   file_in.close();
   auto t1 = std::chrono::high_resolution_clock::now();
   
   long overlaps = b.count_overlaps();
   auto t2 = std::chrono::high_resolution_clock::now();
   std::cout << "\n===\nPotential (overlaps):\t" << overlaps << "\n";
   
   auto delta_t01 = std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count();
   auto delta_t12 = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
   std::cout << "\nTime to read input:\t" << 1.0e-06*delta_t01 << " s\n";
   std::cout << "To compute overlaps:\t" << 1.0e-06*delta_t12 << " s\n";
   std::cout << "===\nOverall runtime:\t"  << 1.0e-06*(delta_t01+delta_t12) << " s\n";
}
