#include <iostream>
#include <fstream>
#include <string.h>
#include "graphe_chemin.hpp"
#include "algoGenetique.h"
using namespace std;

int main()
{
    //////////////////// LECTURE D'UN FICHIER EDITE SUR MATLAB POUR INITIALISATION DU GRAPHE ///////////////

    ifstream mon_graphe("C:/.../Matrice_distance.txt", ios::in); // A modifier /Ouverture mode lecture

    string ligne;
    double distance;
    int nbr;
    int i = 0;

    getline(mon_graphe, ligne);      // Recupere la ligne avec le nombre de villes
    nbr = atoi(ligne.c_str());      // Recupere et convertit le nombre de villes en int
    Graphe mes_villes(nbr);         // initialise un graphe de taille nbr

    if (mon_graphe)
    {
        while (getline(mon_graphe, ligne))       // Lecture de chaque ligne
        {
            distance = atof(ligne.c_str());        // Conversion du caractère en double
            mes_villes.distances[i] = distance;    // remplissage du graphe
            i++;
        }
        cout << mes_villes;     //affichage du graphe
        mon_graphe.close();
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }

    ///////////////////////////////// ALGORITHME GENETIQUE ///////////////////////////////////////////////

    Chemin chemin_0(&mes_villes);   //initialisation du chemin par la methode du plus proche voisin

        // PARAMETRES MODIFIABLES
    int iter = 50;                  //nombre d'iterations sans changement accepte
    double proba = 0.8;             //probabilite de victoire dans tournoi
    int q = 700;                    //nombre de parents conserves dans elite
    int taille = 1000;              //taille de la population
    int tours=1;                    //nombre de repetitions de l'algorithme
    typeselection sel = tournoi;    //fonction de selection des reproducteurs : tournoi, rang ou roulette
    typefinale fin = elite;         //fonction de selection de la popu finale : elite ou enfant

    vector<Individu*> best;     //pour conserver les resultats de tous les tours
    best.resize(tours);
    Individu* result;

    for (int k = 0; k < tours; k++)
        {result = algo_genetique(iter, proba, sel, fin, taille, &chemin_0, q);   //calcule le meilleur chemin possible
        best.at(k)=result->clone();}    //range la solution dans le vecteur best

    double adaptation = 10000;
    vector<Individu*>::const_iterator it = best.begin();

    for (int k=0; k<tours; k++)
    {
        //cout<<best.at(k)->adaptation()<<" "; //afficher les distances finales de chaque tour
        if (best.at(k)->adaptation() < adaptation)
        {
            adaptation = best.at(k)->adaptation();
            result = best.at(k)->clone();
        }
    }
    cout<<endl;

    result->print(cout);                        //afficher le chemin final
    cout << endl;
    cout << result->adaptation() <<endl;        //afficher la longueur du chemin final

    //cout << chemin_0.adaptation() <<endl;     //afficher la fonction d'adaptation du chemin initial

    ///////////////////////// ECRITURE D'UN FICHIER RENVOYANT LE CHEMIN OPTIMAL /////////////////////////

    ofstream mon_chemin("C:/.../Chemin.txt");   //A modifier

    Chemin& finalite = static_cast<Chemin&>(*result);

    if (mon_chemin)
    {
        mon_chemin << finalite;
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en écriture." << endl;
    }
    return 0;
}
