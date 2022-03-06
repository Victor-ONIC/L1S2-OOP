main : main.cpp matcomp.o complexe.o
	g++ -o main matcomp.o complexe.o main.cpp

matcomp.o : matcomp.h matcomp.cpp complexe.h
	g++ -c matcomp.cpp

complexe.o : complexe.h complexe.cpp
	g++ -c complexe.cpp
