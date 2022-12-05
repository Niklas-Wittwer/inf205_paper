#ifndef COLLISIONS_STRUCT_H
#define COLLISIONS_STRUCT_H

#include <cstddef>
/*
class for the spheres
Given by the benchmarking files from the lecturer
*/
class Sphere
{
public:
   Sphere(size_t ipid, double is, const double ix[3]) {
      this->set_particle_id(ipid);
      this->set_size(is);
      for(int d = 0; d < 3; d++) this->set_coordinate(d, ix[d]);
   }
   
   size_t get_particle_id() const { return this->particle_id; }
   double get_size() const { return this->size; }
   double get_coordinate(int axis) const;  /* axis = 0 for x, 1 for y, 2 for z */
   
   void set_particle_id(size_t i_pid) { this->particle_id = i_pid; }
   void set_size(double in_size);
   void set_coordinate(int axis, double in_coord);  /* axis = 0 for x, 1 for y, 2 for z */
   
   /*
    * is there an overlap between this sphere and another?
    * this method determines it (0: no overlap, 1: overlap, 8: soft shielding broken)
    */
   int check_overlap(const Sphere* other, const double box_size[3]) const;

private:
   size_t particle_id = 0;
   double size = 0.0;
   double coords[3] = {0.0, 0.0, 0.0};
};

#endif
