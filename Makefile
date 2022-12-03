run: evaluate-confguration generator
	./generator 65536
	./evaluate-confguration benchmark-configuration.dat

generator: generator.o sphere.o box.o algo.o utils.o
	g++ -g3 -O1 -o generator generator.o sphere.o box.o algo.o utils.o

evaluate-confguration: evaluate-configuration.o sphere.o box.o 
	g++ -g3 -O1 -o evaluate-confguration evaluate-configuration.o sphere.o box.o

%.o: %.cpp
	g++ -g3 -O1 -c -std=c++17 -o $@ $<

clean:
	rm -f *.o evaluate-confguration generator benchmark-configuration.dat
