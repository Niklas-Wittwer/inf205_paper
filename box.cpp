#include "box.h"
#include <cassert>

/*
This code is built upon the benchmarking files given by the lecturer
*/

void Box::in(std::istream* source)
{
   // first input size of the box
   double x, y, z;
   *source >> x >> y >> z;
   this->set_extension(x, y, z);
   
   size_t num_part_comp = 0;  // number of particles of a certain component
   long pid = 0;
   
   *source >> num_part_comp;  // input number of particles of component 0
   while(num_part_comp != 0)
   {
      // create new component
      double sphere_size = 0.0;
      *source >> sphere_size;
      this->add_component(sphere_size);
      
      // now read all the particles
      for(size_t i = 0; i < num_part_comp; i++)
      {
         // read the coordinates
         double x[3];
         for(int d = 0; d < 3; d++)
         {
            *source >> x[d];
            
            // apply periodic boundary condition
            while(x[d] < 0.0) x[d] += this->extension[d];
            while(x[d] > this->extension[d]) x[d] -= this->extension[d];
         }
         
         // insert new particle
         this->add_particle(pid++, sphere_size, x);
      }
      
      *source >> num_part_comp;  // input number of particles for next component
   }
}
std::istream& operator>>(std::istream& is, Box& b) {
   b.in(&is);
   return is;
}

void Box::out(std::ostream* target)
{
   *target << this->extension[0] << " " << this->extension[1] << " " << this->extension[2] << "\n";
   
   for(auto i = this->components.begin(); i != this->components.end(); i++)
   {
      *target << "\n" << this->particles[i->second].size() << " " << i->first << "\n";

      for(auto j = this->particles[i->second].begin(); j != this->particles[i->second].end(); j++)
         *target << j->get_coordinate(0) << "\t"
                 << j->get_coordinate(1) << "\t" << j->get_coordinate(2) << "\n";
   }
   *target << "\n0\n";
}
std::ostream& operator<<(std::ostream& os, Box& b) {
   b.out(&os);
   return os;
}

// count the number of overlaps between pairs of spheres
//
// normal overlaps count as 1, if the inner shielding is broken it counts as 8
//
long Box::count_overlaps()
{
   long overlaps = 0;
   
   // iterate over pairs of components A and B
   for(auto A = this->components.begin(); A != this->components.end(); A++)
      for(auto B = A; B != this->components.end(); B++)
      {
         if(A->second == B->second)  // same component: iterate over pairs of particles i and j
            for(auto i = this->particles[A->second].begin(); std::next(i) != this->particles[A->second].end(); i++)
               for(auto j = std::next(i); j != this->particles[B->second].end(); j++)
                  overlaps += i->check_overlap(&(*j), this->extension);

         else  // different components: iterate over pairs of particles i and j
            for(auto i = this->particles[A->second].begin(); i != this->particles[A->second].end(); i++)
               for(auto j = this->particles[B->second].begin(); j != this->particles[B->second].end(); j++)
                  overlaps += i->check_overlap(&(*j), this->extension);
      }
   
   return overlaps;
}

// Get original box extensions to create sub boxes
double Box::get_extensions(int axis) {
   assert((axis == 0) || (axis == 1) || (axis == 2));
   return this->extension[axis];
}

void Box::allocate_spheres(std::vector<std::vector<std::vector<Box>>>& pbc, int dim){
// Allocate spheres to the pbc with an approxiomate equal distribution of same sized spheres
    int x = 0, y = 0, z = 0;
    for (std::map<double,int>::iterator iter = this->components.begin(); iter != this->components.end(); ++iter){
        if (x == dim){
            y++;
            x = 0;
        }
        if (y == dim){
            z++;
            y = 0;
        }
        if (z == dim){
            z = 0;
        }
        pbc[x][y][z].particles.push_back(std::vector<Sphere>());
        int cid = pbc[x][y][z].particles.size();
        pbc[x][y][z].particles.push_back(this->particles[iter -> second]);
        x++;
    }
}

void Box::copy_spheres(Box* other){
   std::vector< std::vector<Sphere> >::iterator row;
   std::vector<Sphere>::iterator col;
    for (row = other->particles.begin(); row != other->particles.end(); row++) {
    for (col = row->begin(); col != row->end(); col++) {
        
    }
}
}


// create component, return cid
int Box::add_component(double sphere_size)
{
   int cid = this->particles.size();
   this->components.insert({sphere_size, cid});
   this->particles.push_back(std::vector<Sphere>());
   return cid;
}


   
// create particle, return cid
int Box::add_particle(size_t pid, double sphere_size, double q[3])
{
   this->N++;
      
   int cid = 0;
   auto comp = this->components.find(sphere_size);
   if(comp != this->components.end()) cid = comp->second;
   else cid = this->add_component(sphere_size);
         
   this->particles[cid].push_back(Sphere(pid, sphere_size, q));
   return cid;
}
