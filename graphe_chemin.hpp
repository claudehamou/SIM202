#ifndef GRAPHE_CHEMIN_HPP_INCLUDED
#define GRAPHE_CHEMIN_HPP_INCLUDED

#include "individu.h"
#include <iostream>
#include <cstdlib>
using namespace std;


////////////////////////////////////////////////// CLASSE GRAPHE ///////////////////////////////////////////////////

class Graphe
{
public :
    int nbvilles;   //nombre de villes
    double* distances;   //tableau des distances entre les villes

    Graphe(int);        //constructeur a partir du nombre de villes
    Graphe & operator = (const Graphe &);       //constructeur par copie
    double & operator () (int i,int j) {return distances[nbvilles*i+j];}         //acces non const a la distance entre les villes i et j
    double operator () (int i,int j) const {return distances[nbvilles*i+j];}     //acces const a la distance entre les villes i et j

    friend ostream & operator <<(ostream &, const Graphe&);
};

inline ostream & operator <<(ostream & out, const Graphe &G)
{
    for (int i=0;i<G.nbvilles;i++)
    {
        out<<"|";
        for (int j=0;j<G.nbvilles-1;j++)
        {
            out<<G(i,j)<<",";
        }
        out<<G(i,G.nbvilles-1)<<"|"<<"\n";
    }
    return out ;
}

////////////////////////////////////////////////// CLASSE CHEMIN ///////////////////////////////////////////////////

class Chemin : public Individu
{
public :
    Graphe *graphe;
    vector<int> villes;

    Chemin();
    Chemin(Graphe*);    //construction d'un chemin a partir d'un graphe
    Chemin & operator = (const Chemin &);       //constructeur par copie

    int operator()(int i) const {return villes.at(i);}; // ieme coordonnee en lecteur
    int& operator()(int i) {return villes.at(i);}; // ieme coordonnee en ecriture


    friend ostream & operator <<(ostream &, const Chemin&);

    double adaptation();    //calcule la fonction d'adaptation, ie le cout du chemin
    Chemin flip();      //procede a la mutation
    Chemin initialise_indiv();      //donne un chemin initial qui prend le plus proche voisin
};

Chemin* crossover(Chemin,Chemin);   //procede a l'hybridation de deux chemins

inline ostream & operator <<(ostream & out, const Chemin &C)
{
    for (unsigned short int i=0;i<(unsigned short)((C.villes).size()-1);i++)
    {
        out<<C(i)+1<<" ";
    }
    out<<C((C.villes).size()-1)+1;
    return out ;
}

#endif // GRAPHE_CHEMIN_HPP_INCLUDED
