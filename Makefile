program: main.o kot.o baza.o
	g++ main.o kot.o baza.o -o program

main.o: main.cpp kot.h baza.h
	g++ -c main.cpp

kot.o: kot.cpp kot.h
	g++ -c kot.cpp

baza.o: baza.cpp baza.h kot.h
	g++ -c baza.cpp

clean:
	rm -f *.o program

run:
	./program
