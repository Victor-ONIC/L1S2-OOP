main : main.o vecteurs.o
	g++ -o main vecteurs.o main.o

main.o : vecteurs.h main.cpp
	g++ -c main.cpp

vecteurs.o : vecteurs.h vecteurs.cpp
	g++ -c vecteurs.cpp
