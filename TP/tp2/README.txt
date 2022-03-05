###############################################################################
#
#   Voici quelques précisions par rapoort à mon travail:
#
#   -> Dans le makefile:
#       Ce makefile est similaire à celui que j'avais écrit pour mon
#       mini-projet au premier semestre. Il ne vient pas de nulle part.
#       Il paraît compliqué mais permet de garder le même makefile pour
#       n'importe quel nombre de fichiers .cpp.
#       Accélerer le programme (question 9): > make OPT=-O3
#
#   -> Dans les fichiers Point.cpp et col_Points.cpp:
#       Les constructeurs utilisent des listes d'initialisations. Cela n'a
#       pas été vu en cours, mais c'est un concept que j'avais déjà utilisé
#       pour, encore une fois, mon mini-projet.
#       Je les utilise également pour des raisons de régularité, afin de
#       prendre de bonnes habitudes.
#
#   -> Dans le fichier principal.cpp:
#       Afin de compter combien de temps s'écoule pendant la recherche du
#       point, j'utilise la librairie <chrono>. Cela est dû au fait que le
#       sujet demande le temps de recherche dans un tableau de 100, 1.000,
#       10.000 et 1.000.000. Cette recherche prend moins d'une seconde sur
#       certaines machines, alors l'utilisation de <ctime> n'est pas possible.
#       Afin d'arriver à un temps de recherche supérieur à une seconde, j'ai
#       créé une boucle allant jusqu'à 100.000.000 de Points. Si cela prend
#       trop de temps sur votre machine, utilisez la commande donnée au-dessus.
#
#
#   ---------------------------------- TL;DR ----------------------------------
#   _ J'ai bien écrit ce makefile, même s'il parâit compliqué.
#   _ J'utilise des listes d'initialisations dans les constructeurs pour 
#   prendre de bonnes habitudes.
#   _ <chrono> est importée pour mesurer des durées inférieures à une seconde.
#   _ utilisez '> make OPT=-O3' pour accélérer le programme.
#   ---------------------------------------------------------------------------
#
###############################################################################
