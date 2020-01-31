#ifndef ALGOGENETIQUE_H_INCLUDED
#define ALGOGENETIQUE_H_INCLUDED

using namespace std;
#include <vector>

class Individu
{
public :
    virtual double  adaptation()=0; //fonction d'adaptation virtuelle pure a ecrire concretement dans la classe chemin
};

class Population
{
public :
    int taillePopulation p;
    Individu * popu;



};

#endif // ALGOGENETIQUE_H_INCLUDED
