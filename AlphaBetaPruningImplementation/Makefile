a.out: main.o  Tree.o
	g++ -Wall -pedantic -g -o a.out main.o  Tree.o 
Tree.o: Tree.cpp Tree.h
	g++ -Wall -pedantic -g -std=c++11 -c Tree.cpp
main.o: main.cpp  Tree.h
	g++ -Wall -pedantic -g -std=c++11 -c main.cpp
clean: 
	rm -f main.o Tree.o a.out
