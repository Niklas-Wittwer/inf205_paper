#include <cassert>
#include <iostream>

#include "sphere.h"
/*
Functions related to the sphere object
Given by the benchmarking files from the lecturer
*/
double Sphere::get_coordinate(int axis) const
{
   assert((axis == 0) || (axis == 1) || (axis == 2));
   return this->coords[axis];
}

void Sphere::set_size(double in_size)
{
   assert(in_size > 0.0);
   this->size = in_size;
}

void Sphere::set_coordinate(int axis, double in_coord)
{
   assert((axis == 0) || (axis == 1) || (axis == 2));
   this->coords[axis] = in_coord;
}

// is there an overlap between this sphere and another?
//
// return value:
//    0, if there is no overlap
//    1, if there is an overlap, i.e., distance is smaller than the sum of radii
//    8, if the distance is even smaller than half the sum of radii (soft shielding)
//
int Sphere::check_overlap(const Sphere* other, const double box_size[3]) const
{
   // square distance between the centre of i and the centre of j
   double square_distance = 0.0;
   for(int d = 0; d < 3; d++)
   {
      double dist_d = other->coords[d] - this->coords[d];
      
      // apply minimum image convention
      if(dist_d > 0.5*box_size[d]) dist_d -= box_size[d];
      else if(dist_d < -0.5*box_size[d]) dist_d += box_size[d];
      
      square_distance += dist_d*dist_d;
   }
   
   /*
    * is the square distance smaller than the square of the sum of radii?
    */
   double sum_of_radii = 0.5 * (this->size + other->size);
   int overlap = 0;
   if(square_distance < 0.25*sum_of_radii*sum_of_radii) overlap = 8;  // soft shielding
   else if(square_distance < sum_of_radii*sum_of_radii) overlap = 1;  // normal overlap
   
   /*
   if(overlap) // debug_output
   {
      std::cout << "\t\toverlap (potential = " << overlap
                << ") between " << this->particle_id << " (" << this->coords[0] << "/"
                << this->coords[1] << "/" << this->coords[2] << "),\tsize " << this->size
                << ",\t\tand " << other->particle_id << " (" << other->coords[0] << "/"
                << other->coords[1] << "/" << other->coords[2] << "),\tsize " << other->size << "\n";
   }
    */
   return overlap;
}
