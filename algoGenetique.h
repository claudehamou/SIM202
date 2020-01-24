#ifndef ALGOGENETIQUE_H_INCLUDED
#define ALGOGENETIQUE_H_INCLUDED

using namespace std;
#include <vector>

class Individu
{
public :
    int tailleGenome;
    int * genome;

    void init(int n) {tailleGenome = n; genome = new int[n];}; //allocation
    void clearing() {delete genome;}; //desallocation

    // constructeurs / destructeur

    Individu(int n) {init(tailleGenome);}; //constructeur par defaut
    Individu(const Individu& ind); //constructeur par copie
    ~Individu();

    // surcharges operateurs

    double operator()(int i) const {return genome[i-1];}; // ieme coordonnee en lecteur
    double& operator()(int i) {return genome[i-1];}; // ieme coordonnee en ecriture

    virtual double & adaptation()=0; //fonction d'adaptation virtuelle pure a ecrire concretement dans la classe chemin
};

class Population
{
public :
    int taillePopulation p;
    Individu * popu;



};

#endif // ALGOGENETIQUE_H_INCLUDED
