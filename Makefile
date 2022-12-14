run: evaluate-confguration generator algo
	./generator 10200
	./evaluate-confguration benchmark-configuration.dat
	./algo benchmark-configuration.dat
	./evaluate-confguration algo-configuration.dat

generator: generator.o sphere.o box.o utils.o
	g++ -g3 -O1 -o generator generator.o sphere.o box.o utils.o

algo: algo.o sphere.o box.o utils.o
	g++ -g3 -O1 -o  algo algo.o sphere.o box.o utils.o

evaluate-confguration: evaluate-configuration.o sphere.o box.o utils.o
	g++ -g3 -O1 -o evaluate-confguration evaluate-configuration.o sphere.o box.o utils.o 
	

%.o: %.cpp
	g++ -g3 -O1 -c -std=c++17 -o $@ $<

clean:
	    del *.exe *.dat *.o algo evaluate-confguration generator
	
