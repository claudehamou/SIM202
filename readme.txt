OBJECTIF : Determiner avec la plus grande precision possible le chemin le plus court permettant de relier les villes donnees

Ouvrir les fichiers "graphe_chemin.hpp", "graphe_chemin.cpp", "algoGenetique.h", "algoGenetique.cpp" et "main.cpp"
Dans main.cpp
	Modifier les lignes 12 et 82 en rentrant le chemin vers les fichiers "Matrice_distance.txt" et "Chemin.txt" :
		ifstream mon_graphe("..../Matrice_distance.txt",ios::in) ;
		ofstream mon_chemin("..../Chemin.txt") ;
	Modifier les variables des lignes 44 à 50 selon les tests que vous souhaitez effectuer :
		- iter le nombre d'iterations sans changement de meilleur individu pour arreter l'algorithme genetique
		- proba la probabilite de victoire du meilleur individu dans la selection par tournoi
		- q le nombre de parents gardes dans la selection par elitisme /!\ 0<=q<=taille
		- tours le nombre d'executions de l'algorithme genetique
		- sel la fonction de selection des reproducteurs (tournoi, rang, roulette)
		- fin la fonction de selection de la population finale (elite, enfant)
Dans graphe_chemin.cpp (pour les plus aventureux)
	/!\ Pour travailler avec des villes eloignees de plus de 100000 (impossible avec notre carte),
	modifier l.182 avec un nombre > max d, ou d la distance entre deux villes.


///AVEC INTERFACE MATLAB
Ouvrir les fichiers "voyageur.m", "affiche_chemin.m" et "voyageur_2.m"
Executer "voyageur.m"
	Selectionner des points sur la carte a l'aide de la souris, appuyer sur Entree quand le nombre de points est suffisant
	/!\ Laisser ouverts les fichiers Matlab pour ne pas perdre l'information nbr_villes


///SANS INTERFACE MATLAB
Fournir un fichier Matrice_distance.txt (graphe du probleme) de la forme suivante :
int nbr_villes
double distance00
double distance01
...		(nbr_villes^2 termes en tout)
double distanceNN	/!\ il faut que chaque distanceii et chaque chemin impratiquable affiche -1, et sinon distanceij>0


Executer le fichier "main.cpp"
	Valeurs affichees dans le terminal :
	- graphe du probleme
	- meilleure fonction d'adaptation a la fin de chaque generation de l'algorithme genetique
	- chemin final
	- fonction d'adaptation du chemin final

Executer le fichier "voyageur_2.m"