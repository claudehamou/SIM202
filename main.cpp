#include <iostream>
#include <fstream>
#include <string.h>
#include "graphe_chemin.hpp"
#include "algoGenetique.h"
using namespace std;

int main()
{
    //////////////////// LECTURE D'UN FICHIER EDITE SUR MATLAB POUR INITIALISATION DU GRAPHE ///////////////

    ifstream mon_graphe("E:/ENSTA/2A/SIM/202/Matrice_distance.txt",ios::in) ; // Ouverture mode lecture

    string ligne ;
    double distance ;
    int nbr ;
    int i=0 ;

    getline(mon_graphe,ligne) ;      // Récupère la ligne avec le nombre de villes
    nbr = atoi(ligne.c_str()) ;      // Récupère et converti le nombre de villes en int
    Graphe mes_villes(nbr) ;

    if(mon_graphe)
    {
        while (getline(mon_graphe,ligne))       // Lecture de chaque ligne
        {
            distance = atof(ligne.c_str()) ;        // Conversion du caractère en double
            mes_villes.distances[i] = distance ;    // Initialisation du graphe
            i++ ;
        }
        cout << mes_villes ;
        mon_graphe.close() ;
    }
    else
    {
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }

    ///////////////////////////////// ALGORITHME GENETIQUE ///////////////////////////////////////////////
    Chemin chemin_0(&mes_villes);
    double proba = 0.4 ;
    int iter = 6000 ;
    int q = 3 ;
    vector<Individu*> best ;
    Individu* result ;

    for (int k=0 ; k<50; k++)
        result=algo_genetique(iter, proba, tournoi, elite, 1000, &chemin_0, q) ;
        best.push_back(result) ;

    double adaptation = 10000 ;
    vector<Individu*>::const_iterator it=best.begin() ;

    for (;it!=best.end();it++)
    {
        if ((*it)->adaptation() < adaptation)
            result = *it ;
    }
    
    result->print(cout) ;
    cout << endl ;

    ///////////////////////// ECRITURE D'UN FICHIER RENVOYANT LE CHEMIN OPTIMAL /////////////////////////

    ofstream mon_chemin("E:/ENSTA/2A/SIM/202/Chemin.txt") ;

    Chemin& finalite = static_cast<Chemin&>(*result) ;

    if (mon_chemin)
    {
        mon_chemin << finalite ;
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en écriture." << endl;
    }
    return 0 ;
}
