#ifndef BOX_H
#define BOX_H

#include <iostream>
#include <map>
#include <vector>

#include "sphere.h"

/*
Declaring the box class and its function
This code is build upon the code given by the lecturer through the benchmarking files, custom functions are added
*/
class Box
{
public:

   void in(std::istream* source);  // read from *source
   void out(std::ostream* target);  // write to *target
   
   long count_overlaps();  // count number of overlaps (if inner shielding is broken, it counts as eight overlaps)
   
   void set_extension(double x, double y, double z) {
      this->extension[0] = x;
      this->extension[1] = y;
      this->extension[2] = z;
   }

   double get_extensions(int axis);
   void allocate_spheres(std::vector<std::vector<std::vector<Box>>>& pbc, int dim);
   void deallocate_spheres(std::vector<std::vector<std::vector<Box>>>& pbc);
   void copy_spheres(Box* other, double dx, double dy, double dz);
   void optimize(int ax[3], int n_attempts, double cube_len);
   bool check_sim(Box other);

   int add_component(double sphere_size);  // create component, return cid
   int add_particle(size_t pid, double sphere_size, double q[3]);  // create particle, return cid
   int add_particle_pbc(Sphere sphere);
   void clear_particles();

private:
   double extension[3];  // size of the box
   size_t N = 0;  // total number of particles
   std::vector<std::vector<Sphere>> particles;  // maps each component ID to the spheres associated with that component
   //std::vector<std::vector<Sphere*>> particles2; // Vector of pointers to the original spheres to be altered
   std::map<double, int, std::greater<double>> components;  // component IDs (value) ordered by size (key)

};

std::istream& operator>>(std::istream& is, Box& b);
std::ostream& operator<<(std::ostream& os, Box& b);

#endif
