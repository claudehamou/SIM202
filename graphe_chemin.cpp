#include "graphe_chemin.hpp"
#include "individu.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

////////////////////////////////////////////////// CLASSE GRAPHE ///////////////////////////////////////////////////

Graphe::Graphe(int dim)
{
    nbvilles=dim;
    distances= new double[dim^2];
    for (int k=0;k<dim;k++) distances[k]=0;
}

Graphe & Graphe::operator=(const Graphe& G)
{
    if (this==&G) return *this;
    nbvilles=G.nbvilles;
    distances=new double [G.nbvilles^2];
    for (int k=0;k<((G.nbvilles)^2);k++) distances[k]=G.distances[k];
    return *this;
}

////////////////////////////////////////////////// CLASSE CHEMIN ///////////////////////////////////////////////////

Chemin::Chemin()
{
    Graphe G=Graphe(3); //initialise a un graphe "random" de 3 villes
    G(0,0)=-1;
    G(0,1)=2;
    G(0,2)=5;
    G(1,0)=2;
    G(1,1)=-1;
    G(1,2)=1;
    G(2,0)=5;
    G(2,1)=1;
    G(2,2)=-1;
    graphe=&G;
    villes.resize(3);
    villes.at(0)=0;
    villes.at(1)=1;
    villes.at(2)=2;
}


Chemin::Chemin(Graphe *G)
{
    graphe=G;
    villes.resize(G->nbvilles);
    for (int k=0;k<G->nbvilles;k++) {villes.at(k)=k;}  //initialisation au chemin dans l'ordre des indices des villes
}

double Chemin::adaptation()
{
    double adapt=0;
    int n=villes.size();
    for(int i=0;i<n-1;i++)
    {
        adapt+=graphe->distances[n*villes.at(i)+villes.at(i+1)];
    }
    adapt+=graphe->distances[n*villes.at(n-1)+villes.at(0)];
    return adapt;
}

Chemin crossover(Chemin C1,Chemin C2)
{
    Chemin C=Chemin(C1.graphe);
    srand (time(NULL));
    int l = rand() % C.villes.size();
    cout<<l<<endl;
    for (int k=0;k<l+1;k++)
    {
        C.villes.at(k)=C1.villes.at(k);   //associer les l+1 premieres villes de C1 aux l+1 premieres villes de C
    }
    int d=0;
    for (int k=l+1;k<C.villes.size();k++)
    {
        int d2=0;
        int j=0;
        while (d2==0 && j<l+1)
        {
            if (C2.villes.at(k)==C.villes.at(j)){d2++;}
            j++;
        }
        if (d2==0)
        {
            C.villes.at(k-d)=C2.villes.at(k); //remplir les villes restantes de C2 en plus si pas deja dans C
        }
        d+=d2;
    }
    while (d!=0)
    {
        int rep=0;
        int i=0;
        while(rep==0) //reperer les indices de villes qui ne sont pas dans C
        {
            int k=0;
            while (C.villes.at(k)!=i && k<C.villes.size()-d)
            {
                k++;
            }
            if (k==C.villes.size()-d) {rep++;}
            i++;
        }
        C.villes[C.villes.size()-d]=i-1;    //ajouter les villes non remplies
        d--;
    }
    return C;
}
