#include "algoGenetique.h"
#include <cstdlib>
#include <ctime>
#include <map>
#include <list>
#include <iostream>

int rand_0_n(int n) // fonction qui genere un entier aleatoire entre 0 et n-1 inclus
{
    return rand()%n;
}

double reel_rand(double a, double b) // genere un nombre random entre a et b (reel)
{
    return (rand()/(double)RAND_MAX) * (b-a) + a;
}

/////////////////////////////////// SELECTION PAR ROULETTE /////////////////////////////////////////////////

Population Population::selection_roulette()
{
    int p = popu.size();
    Population enfants(p);
    int parcours = 0;
    while (parcours < p)
    {
        srand(time(NULL));
        double S = 0;
        vector<Individu*>::iterator it=popu.begin();
        for(; it!=popu.end(); it++)
        {
            S+=(*it)->adaptation();
        }
        double r = reel_rand(0,S);
        double S_aux = 0;
        vector<Individu*>::iterator it2=popu.begin();
        while (S_aux < r || it2!=popu.end())
        {
            S_aux+=(*it2)->adaptation();
            it2++;
        }
        enfants.popu.push_back(*it2);
        parcours++;
    }
    return (enfants);
}

/////////////////////////////////// SELECTION PAR RANG /////////////////////////////////////////////////

Population Population::selection_rang()
{
    int p = popu.size();
    Population enfants(p);
    int parcours = 0;
    while (parcours < p)
    {
        double S = 0;
        int i = 0;
        multimap <double, Individu*> tripop; // permet de trier
        vector<Individu*>::iterator it=popu.begin();
        for(; it!=popu.end(); it++)
        {
            tripop.insert(make_pair(-((*it)->adaptation()),*it));
        }
        for (int k=0; k<p; k++)
        {
            S+=k+1;
        }
        double r = reel_rand(0,S);
        double S_aux = 0;
        multimap <double, Individu*>::iterator it2=tripop.begin();
        while (S_aux < r || it2!=tripop.end())
        {
            S_aux+=i+1;
            it2++;
            i++;
        }
        enfants.popu.push_back(it2->second);
        parcours++;
    }
    return (enfants);
}

/////////////////////////////////// SELECTION PAR TOURNOI /////////////////////////////////////////////////

Population Population::selection_tournoi(const double proba)
{
    Population enfant(taillePopulation) ;

    list <pair<Individu*,Individu*> > pair_ind ;
    // Initialisation des n paires de n individus d'une population

    srand(time(NULL));
    for (int i=0; i<taillePopulation ; i++)
    {
       pair_ind.push_back(std::make_pair(popu[i],popu[rand_0_n(taillePopulation)])) ;
    }

    // Parcours des paires et sélection
    list <pair<Individu*,Individu*> > ::iterator itl=pair_ind.begin() ;
    int i=0 ;
    for (; itl != pair_ind.end(); ++itl, i++)
    {
        // Meilleur fonction d'adaptation
        int best ;
        if ((itl->first)->adaptation() > (itl->second)->adaptation())
            best = 1 ;
        else
            best = 2 ;

        // Choix du meilleur
        double prb = reel_rand(0,1) ;
        if ((prb < proba && best==1) || (prb > proba && best==2))
            enfant.popu[i] = itl->first ;
        if ((prb < proba && best==2) || (prb > proba && best==1))
            enfant.popu[i] = itl->second ;
    }

    return (enfant) ;
}

//////////////////////////// SELECTION FINALE QUE LES ENFANTS ///////////////////////

Population Population::pop_finale_enfant(const Population parent, const Population enfant)
{
    return enfant ;
}

//////////////////////////// SELECTION FINALE ELITISME ///////////////////////

Population pop_finale_elitisme(int q, const Population parent, const Population enfant)
{
    int p = parent.popu.size();
    if (q > p || q < 0)
    {
        cout<<"Taille incompatible";
        exit(-1);
    }

    Population Pop_finale(p);
    multimap <double, Individu*> triParent; // permet de trier
    multimap <double, Individu*> triEnfant;

    vector<Individu*>::const_iterator it=parent.popu.begin();
    for(;it!=parent.popu.end(); it++)
    {
        triParent.insert(make_pair(-((*it)->adaptation()),*it));
    }

    vector<Individu*>::const_iterator it2=enfant.popu.begin();
    for(;it!=enfant.popu.end(); it2++)
    {
        triEnfant.insert(make_pair(-((*it2)->adaptation()),*it2));
    }

    int k = 0;
    int j = 0;
    multimap <double, Individu*>::iterator it3=triParent.begin();
    while (k < q)
    {
        Pop_finale.popu.push_back(it3->second);
        k++;
        it3++;
    }

    multimap <double, Individu*>::iterator it4=triEnfant.begin();
    while (j < p-q)
    {
        Pop_finale.popu.push_back(it4->second);
        j++;
        it3++;
    }

    return (Pop_finale);
}
