#include "graphe_chemin.hpp"
#include "algoGenetique.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

////////////////////////////////////////////////// CLASSE GRAPHE ///////////////////////////////////////////////////

Graphe::Graphe(int dim)
{
    nbvilles=dim;
    distances= new double[dim*dim];
    for (int k=0;k<dim*dim;k++) distances[k]=0;
}

Graphe & Graphe::operator=(const Graphe& G)
{
    if (this==&G) return *this;
    nbvilles=G.nbvilles;
    distances=new double [(G.nbvilles)*(G.nbvilles)];
    for (int k=0;k<((G.nbvilles)*(G.nbvilles));k++) distances[k]=G.distances[k];
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

Chemin & Chemin::operator = (const Chemin &C)
{
    graphe=C.graphe;
    villes.resize(C.villes.size());
    for (short unsigned int k=0;k<(short unsigned)(villes.size());k++)
        villes.at(k)=C.villes.at(k);
    return(*this);
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

pair<Individu*,Individu*> Chemin::crossover(const Individu& i_1)
{
    const Chemin &C1 = static_cast<const Chemin&>(i_1) ;
    Chemin* C=new Chemin(C1.graphe);
    Chemin* D=new Chemin(C1.graphe);
    int l = rand() % (C->villes.size()-1);
    for (int k=0;k<l+1;k++)
    {
        C->villes.at(k)=C1.villes.at(k);   //associer les l+1 premieres villes de C1 aux l+1 premieres villes de C
        D->villes.at(k)=villes.at(k);
    }
    int cd=0;
    int dd=0;
    for (unsigned short int k=l+1;k<(unsigned short)(C->villes.size());k++)
    {
        int d2=0;
        int d3=0;
        int j=0;
        while (d2==0 && j<l+1)
        {
            if (villes.at(k)==C->villes.at(j)){d2++;}
            j++;
        }
        if (d2==0)
        {
            C->villes.at(k-cd)=villes.at(k); //remplir les villes restantes de C2 en plus si pas deja dans C
        }
        cd+=d2;
        j=0;
        while (d3==0 && j<l+1)
        {
            if (C1.villes.at(k)==D->villes.at(j)){d3++;}
            j++;
        }
        if (d3==0)
        {
            D->villes.at(k-dd)=C1.villes.at(k); //remplir les villes restantes de C2 en plus si pas deja dans C
        }
        dd+=d3;
    }
    while (cd!=0)
    {
        int rep=0;
        unsigned short int i=0;
        while(rep==0) //reperer les indices de villes qui ne sont pas dans C
        {
            unsigned short int k=0;
            while ((unsigned short)(C->villes.at(k))!=i && k<(unsigned short)(C->villes.size()-cd))
            {
                k++;
            }
            if (k==C->villes.size()-cd) {rep++;}
            i++;
        }
        C->villes[C->villes.size()-cd]=i-1;    //ajouter les villes non remplies
        cd--;
    }
    while (dd!=0)
    {
        int rep=0;
        int i=0;
        while(rep==0) //reperer les indices de villes qui ne sont pas dans C
        {
            unsigned short int k=0;
            while (D->villes.at(k)!=i && k<D->villes.size()-dd)
            {
                k++;
            }
            if (k==(unsigned short)(D->villes.size()-dd)) {rep++;}
            i++;
        }
        D->villes[D->villes.size()-dd]=i-1;    //ajouter les villes non remplies
        dd--;
    }
    pair<Individu*,Individu*> cross;
    cross.first=C;
    cross.second=D;
    return cross;
}

Chemin& Chemin::flip()
{
    int l = (rand() % (villes.size()-1))+1;
    int k = rand() % (villes.size()-1);
    int ck=villes.at(k);
    int ck2=villes.at(k+1);
    int cl=villes.at(l);
    int cl2=villes.at(l-1);
    villes.at(l)=ck;
    villes.at(l-1)=ck2;
    villes.at(k+1)=cl2;
    villes.at(k)=cl;
    return *this;
}

Chemin* Chemin::initialise_indiv()
{
    Chemin* C = new Chemin(graphe);
    int n=villes.size();
    int d;
    double m;
    int t;
    int k;
    for (int i=0;i+1<n;i++)
    {
        m=100000;   //arbitraire : a changer eventuellement selon pb
        for (int j=0;j<n;j++)
        {
            if ((graphe->distances[n*C->villes.at(i)+j]!=-1) & (graphe->distances[n*C->villes.at(i)+j]<m))
            {
                t=0;
                k=0;
                while((t==0) & (k<i+1))
                {
                    if ((*C)(k)==j) t=1;
                    k++;
                }
                if (t==0)
                {
                    m=graphe->distances[n*C->villes.at(i)+j];
                    d=j;
                }
            }
        }
        (*C)(i+1)=d;
    }
    return C;
}

void Chemin::print(ostream& out)const
{
    out << (*this) ;
}
