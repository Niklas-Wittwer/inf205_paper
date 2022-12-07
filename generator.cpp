#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "box.h"
/*
Generator from the benchmarking files given by the lecturer
*/
// ./generator <N> <packing_fraction> <outfile> <max_ratio>
//
// default for packing fraction is 7/9
// default for outfile is "benchmark-configuration.dat"
// default for max ratio is 10/3
//
int main(int argc, char** argv)
{
   assert(argc > 1);
   long N = std::atol(argv[1]);
   std::cout << "particle number N:\t" << N << "\n";
   
   double pfract = 7.0/9.0;
   if(argc >= 3) pfract = std::atof(argv[2]);
   std::cout << "packing fraction:\t" << pfract << "\n";
   
   std::string ofname = "benchmark-configuration.dat";
   if(argc >= 4) ofname = argv[3];
   std::cout << "output file name:\t" << ofname << "\n";
   
   double max_ratio = 10.0/3.0;
   if(argc >= 5) max_ratio = std::atof(argv[4]);
   std::cout << "max. size ratio:\t" << max_ratio << "\n";

   // random seed from chrono
   std::srand(
      std::chrono::duration_cast<std::chrono::nanoseconds>(
         std::chrono::high_resolution_clock::now().time_since_epoch()
      ).count()
   );

   long N_remaining = N;
   double V_occupied = 0.0;  // volume occupied by the spheres
   std::map<double, long, std::greater<double>> N_spheres;  // number of spheres to be generated for each diameter value
   
   for(double size = max_ratio; size > 1.0; size -= 1.0)
   {
      double s3 = size*size*size;
      N_spheres[size] = 2.0*N_remaining * std::rand()/(s3*RAND_MAX);  // normalize number of spheres by volume
      if(N_spheres[size] > N_remaining) N_spheres[size] = N_remaining;
      
      N_remaining -= N_spheres[size];
      V_occupied += 0.5235988 * N_spheres[size] * s3;
   }
   N_spheres[1.0] = N_remaining;
   V_occupied += 0.5235988 * N_remaining;
   N_remaining = 0;
   
   Box b;
   double a = std::pow(V_occupied/pfract, 1.0/3.0);  // cubic box with size a
   b.set_extension(a, a, a);
   long pid = 0;
   
   // loop over components
   //ensure that there are at least 1 sphere of each size for each sphere
   for(auto i = N_spheres.begin(); i != N_spheres.end(); i++)
   {
      if(!i->second) continue;
      std::cout << "\t\t\tgenerating " << i->second << " spheres with diameter "
               << i->first << " (occupied volume: " << 0.5235988 * i->second * i->first * i->first * i->first << ")\n";
      std::cout.flush();
      
      // loop over particles
      //ensure that there's at least 1 sphere of each size for each pbc cube
      // Should limit cubes rather than spheres (maybe adjust the fractionm instead)
      for(auto j = 0; j < std::max(i->second, (long)64); j++)
      {
         double q[3]{};
         for(int d = 0; d < 3; d++) q[d] = a*rand()/(double)RAND_MAX;
         b.add_particle(pid++, i->first, q);
      }
   }
   std::cout << "\n\t\t\t==\n\t\t\toccupied volume:\t" << V_occupied << "\n"
             << "\t\t\tvolume of the box:\t" << V_occupied/pfract << "\n"
             << "\t\t\tsize of the box:\t" << a << "\n";
   
   // file output
   std::ofstream fout(ofname);
   if(!fout) return EXIT_FAILURE;
   fout << b;
   fout.close();
   std::cout << "\nDone.\n\n";
}
