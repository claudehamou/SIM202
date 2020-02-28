#include <iostream>
#include "graphe_chemin.hpp"
#include "individu.h"
using namespace std;

int main()
{
    Graphe G=Graphe(3);
    G(0,0)=-1;
    G(0,1)=2;
    G(0,2)=5;
    G(1,0)=2;
    G(1,1)=-1;
    G(1,2)=1;
    G(2,0)=5;
    G(2,1)=1;
    G(2,2)=-1;
    cout<<"Graphe :\n"<<G;
    Chemin C=Chemin(&G);
    C(0)=0;
    C(1)=2;
    C(2)=1;
    cout<<"Chemin : "<<C<<endl;
    cout<<"La fonction d'adaptation de C est "<<C.adaptation()<<"."<<endl;
    C=C.initialise_indiv();
    cout<<C<<endl;

    G=Graphe(6);
    C=Chemin(&G);
    Chemin D=Chemin(&G);
    D(0)=5;
    D(1)=3;
    D(2)=1;
    D(3)=0;
    D(4)=2;
    D(5)=4;
    Chemin* K=crossover(C,D);
    cout<<C<<D<<K[0]<<K[1]<<endl;
    C=C.flip();
    cout<<C<<endl;
    return 0;
}
