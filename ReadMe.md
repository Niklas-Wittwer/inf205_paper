# Minimizing overlap between spheres
This project uses a combination of PBC and monte carlo to reduce the number of overlaps of spheres in a finite volume.
## Usage
This project runs on c++, and the algorithm is intended run through make in terminal (executes configurations in the MakeFile)

for MakeFile clean
if on linux use:
```toml
    rm -f *.o *.dat algo evaluate-confguration generator
```
if on windows use:
```toml
    del *.exe *.dat *.o algo evaluate-confguration generator
```
The random generator is seeded with a random number
To reproduce same results, set the seed in random_num_generator() in utils.cpp (ln118)

