#include "box.h"
#include <cassert>
#include <math.h>
#include "utils.h"

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

void Box::copy_spheres(Box* other, double dx=0, double dy=0, double dz=0){
   assert(this->particles.size() == other->particles.size());
   double dist[3] = {dx, dy, dz};    
   for (int i = 0; i < this->particles.size(); i++){
   for (int j = 0; j < this->particles[i].size(); j++){
      for (int k = 0; k < 3; k++){
         double coord = this->particles[i][j].get_coordinate(k) + dist[k];
         other->particles[i][j].set_coordinate(k, coord);
      } 
   }
   }
}

bool Box::check_sim(Box other){
   if (this->particles.size() != other.particles.size()){
      return false;
   }
   for (int i = 0; i < this->particles.size(); i++) {
   if (this->particles[i].size() != other.particles[i].size()){
      return false;
   }
   }
   return true;
}

void Box::optimize(int ax[3], int n_attempts, double cube_len){
// Copy spheres to the temporary container for the spheres
Box temp_container;
for (int i = 0; i < this->particles.size(); i++){
   temp_container.particles.push_back(std::vector<Sphere>());
   for (int j = 0; j < this->particles[i].size(); j++){
      double q[3] = {0, 0, 0};
      temp_container.particles[i].push_back(Sphere(0, this->particles[i][j].get_size(), q));
   }
   }
//Check overlaps with current positions
int curr_overlaps = this->count_overlaps();
for (int n = 0; n < n_attempts; n++){
   // Give each particle random positions within the limits of the sub cube
   for (int i = 0; i < temp_container.particles.size(); i++){
   for (int j = 0; j < temp_container.particles[i].size(); j++){
      for (int k = 0; k < 3; k++){
         double lower_lim = ax[k]*cube_len + this->particles[i][j].get_size()/2;
         double upper_lim = (ax[k]+1)*cube_len - this->particles[i][j].get_size()/2;
         temp_container.particles[i][j].set_coordinate(k, rand_num(lower_lim, upper_lim));
      }
   }
   }
   // Check if the new cube is a more optimal solution, if not go to next iteration
   if (temp_container.count_overlaps() > curr_overlaps){
      continue;
   }
   // Change position of original spheres if the container found a better solution
   temp_container.copy_spheres(this);
}
}

void Box::allocate_spheres(std::vector<std::vector<std::vector<Box>>>& pbc, int dim){
// Allocate spheres to the pbc with an approxiomate equal distribution of same sized spheres
    int x = 0, y = 0, z = 0, n = 0;
    for (int i = 0; i < this->particles.size(); i++){
      // Counter to iterate through the pbc, a virtual n_dim * n_dim * n_dim cube
      for (int i=0; i < pow(dim, 3); i++){
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
        // Adding an outer vector field to each sub cube for each sphere size
        pbc[x][y][z].particles.push_back(std::vector<Sphere>());
        x++;
        }
      x = 0, y = 0, z = 0;
      for (int j = 0; j < this->particles[i].size(); j++){
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
        // Adding all spheres of same size to the same inner vector
        pbc[x][y][z].particles[n].push_back(this->particles[i][j]);
        x++;
        }
      n++;
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
