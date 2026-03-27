program: main.o kot.o baza.o
	g++ main.o kot.o baza.o -o program

main.o: main.cpp baza.h kot.h
	g++ -c main.cpp

Kot.o: Kot.cpp Kot.hpp
	g++ -c kot.c

BazaKotov.o: BazaKotov.cpp baza.h kot.h
	g++ -c baza.c

clean:
	rm -f *.o program

run:
	./program
