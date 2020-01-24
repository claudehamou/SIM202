#include "graphe_chemin.hpp"
#include <iostream>
using namespace std;

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
    for (int k=0;k<(G.nbvilles)^2;k++) distances[k]=G.distances[k];
    return *this;
}
