#ifndef ALGOGENETIQUE_H_INCLUDED
#define ALGOGENETIQUE_H_INCLUDED

using namespace std;
#include <vector>
#include <iostream>

enum typeselection{roulette,rang,tournoi};
enum typefinale{elite,enfant};

class Individu
{
public :
    virtual ~Individu() {}; // destructeur virtuel

    virtual double adaptation()=0; //fonction d'adaptation virtuelle pure a ecrire concretement dans la classe chemin

    virtual Individu& flip()=0 ;

    virtual Individu* initialise_indiv()=0; // fonction d'initialisation d'individu virtuelle pure
    
    virtual Individu* clone()=0 ;   // fonction clone
    
    virtual pair<Individu*,Individu*> crossover(const Individu& ind_2)=0 ;
    
    virtual void print(ostream&) const =0;
};

class Population
{
public :
    int taillePopulation;
    Individu* bestIndividu;
    vector<Individu*> popu;

    Population(int p) {taillePopulation = p;popu.resize(p);bestIndividu=0;}; // constructeur par defaut
    Population(const Population& pop);
    void clean() {for (int i=0 ; i<taillePopulation ; i++) delete popu[i] ;} ;
    ~Population(){clean();}                              // destructeur

    // fonctions de selection des reproducteurs

    Population selection_roulette();
    Population selection_rang();
    Population selection_tournoi(const double proba) ;
    
    // operateur surcharge
    
    Population& operator=(const Population& pop);
};

// fonctions de choix de population finale (mix entre parents et enfants)

Population& pop_finale_enfants(const Population &parent, Population &enfant) ;
Population pop_finale_elitisme(int q, const Population &parent, const Population &enfant);

// fonctions auxiliaires generation de nombre aleatoire

int rand_0_n(int n); // fonction pour generer un entier aleatoire de 0 a (n-1)
double reel_rand(double a, double b); // genere un nombre random entre a et b (reel)

Individu* algo_genetique(int,double,typeselection,typefinale,int,Individu*,int);

#endif // ALGOGENETIQUE_H_INCLUDED
