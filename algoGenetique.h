#ifndef ALGOGENETIQUE_H_INCLUDED
#define ALGOGENETIQUE_H_INCLUDED

using namespace std;
#include <vector>

class Individu
{
public :
    virtual ~Individu() {}; // destructeur virtuel

    virtual double adaptation()=0; //fonction d'adaptation virtuelle pure a ecrire concretement dans la classe chemin

    virtual flip() ;

    virtual Individu* initialise_indiv()=0; // fonction d'initialisation d'individu virtuelle pure
};

class Population
{
public :
    int taillePopulation;
    Individu* bestIndividu;
    vector<Individu*> popu;

    Population(int p) {taillePopulation = p;}; // constructeur par defaut

    // fonctions de selection des reproducteurs

    Individu* selection_roulette();
    Individu* selection_rang();
    Population selection_tournoi(const double proba) ;
};

int rand_0_n(int n); // fonction pour generer un entier aleatoire de 0 a (n-1)
double reel_rand(double a, double b); // genere un nombre random entre a et b (reel)

#endif // ALGOGENETIQUE_H_INCLUDED
