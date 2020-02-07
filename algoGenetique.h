#ifndef ALGOGENETIQUE_H_INCLUDED
#define ALGOGENETIQUE_H_INCLUDED

using namespace std;
#include <vector>

class Individu
{
public :
    virtual ~Individu() {}; // destructeur virtuel

    virtual double adaptation()=0; //fonction d'adaptation virtuelle pure a ecrire concretement dans la classe chemin

    virtual Individu& flip()=0 ;

    virtual Individu* initialise_indiv()=0; // fonction d'initialisation d'individu virtuelle pure
};

class Population
{
public :
    int taillePopulation;
    Individu* bestIndividu;
    vector<Individu*> popu;

    Population(int p) {taillePopulation = p;}; // constructeur par defaut
    ~Population()                              // destructeur
    {for (int i=0 ; i<taillePopulation ; i++)
        delete [] popu[i] ;} ;

    // fonctions de selection des reproducteurs

    Population selection_roulette();
    Population selection_rang();
    Population selection_tournoi(const double proba) ;
};

Population pop_finale_enfants(const Population parent, const Population enfant);
Population pop_finale_elitisme(int q, const Population parent, const Population enfant);

int rand_0_n(int n); // fonction pour generer un entier aleatoire de 0 a (n-1)
double reel_rand(double a, double b); // genere un nombre random entre a et b (reel)

#endif // ALGOGENETIQUE_H_INCLUDED
