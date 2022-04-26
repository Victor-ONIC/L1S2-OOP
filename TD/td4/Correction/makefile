arbre_binaire_main : arbre_binaire_main.cpp arbre_binaire.o arbre_binaire.h
	g++ -o arbre_binaire_main arbre_binaire_main.cpp arbre_binaire.o
arbre_binaire.o : arbre_binaire.cpp arbre_binaire.h
	g++ -c arbre_binaire.cpp
clean :
	rm -f *.o
mrproper : clean
	rm -f arbre_binaire_main
