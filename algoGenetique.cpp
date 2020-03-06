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

// OPERATEUR = ET CONSTRUCTEUR PAR COPIE

Population::Population(const Population& pop)
{
    taillePopulation=pop.taillePopulation;
     popu.resize(pop.taillePopulation);
     for (int i=0;i<taillePopulation;i++)
     {
         popu[i]=pop.popu[i]->clone();
     };
}

Population& Population::operator=(const Population& pop)
{
     clean();
     taillePopulation=pop.taillePopulation;
     popu.resize(pop.taillePopulation);
     for (int i=0;i<taillePopulation;i++)
     {
         if (pop.popu[i]==0)
            popu[i] = 0 ;
         else
            popu[i]=pop.popu[i]->clone();
     }
     return(*this);

}

/////////////////////////////////// SELECTION PAR ROULETTE /////////////////////////////////////////////////

Population Population::selection_roulette()
{
    int p = popu.size();
    Population enfants(p);
    int parcours = 0;
    while (parcours < p)
    {
        double S = 0;
        vector<Individu*>::iterator it=popu.begin();
        for(; it!=popu.end(); it++)
        {
            S+=(*it)->adaptation();
        }
        double r = reel_rand(0,S);
        double S_aux = 0;
        vector<Individu*>::iterator it2=popu.begin();
        while (S_aux < r && it2!=popu.end())
        {
            S_aux+=(*it2)->adaptation();
            it2++;
        }
        if (it2==popu.end())
            enfants.popu.at(parcours)=(*popu.rbegin())->clone();
        else
            enfants.popu.at(parcours)=(*it2)->clone();
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
    double S=p*(p+1)/2 ;       //Somme de tous les rangs (de 1 a p)
    while (parcours < p)
    {
        int i = 0;
        multimap <double, Individu*> tripop; // permet de trier
        vector<Individu*>::iterator it=popu.begin();
        for(; it!=popu.end(); it++)
        {
            tripop.insert(make_pair(-((*it)->adaptation()),*it));
            cout << (*it)->adaptation() << endl;        // IL Y PASSE n CARRE FOIS
        }
        double r = reel_rand(0,S);      //rang limite r selectionne entre 0 et S
        double S_aux = 0;
        multimap <double, Individu*>::iterator it2=tripop.begin();
        while (S_aux < r && it2!=tripop.end())
        {
            S_aux+=i+1;
            it2++;
            i++;
        }
        if (it2==tripop.end())
        {
            enfants.popu.at(parcours)=tripop.rbegin()->second->clone();
        }
        else
        {
            enfants.popu.at(parcours)=it2->second->clone();     //it2->second est l'Individu* de la multimap au "rang" it
        }
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
            enfant.popu[i] = itl->first->clone() ;
        if ((prb < proba && best==2) || (prb > proba && best==1))
            enfant.popu[i] = itl->second->clone() ;
    }

    return (enfant) ;
}

//////////////////////////// SELECTION FINALE QUE LES ENFANTS ///////////////////////

Population& pop_finale_enfants(const Population &parent, Population &enfant)
{
    std::vector<Individu*>::iterator it=enfant.popu.begin() ;
    double best=parent.bestIndividu->adaptation() ;
    enfant.bestIndividu = parent.bestIndividu ;

    for (;it!=enfant.popu.end();it++)
        {
            double best_i = (*it)->adaptation() ;
            if (best_i > best)
                enfant.bestIndividu = (*it) ;
                best = best_i ;
        }
    return enfant ;
}

//////////////////////////// SELECTION FINALE ELITISME ///////////////////////

Population pop_finale_elitisme(int q, const Population &parent, const Population &enfant)
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
    
    if (triEnfant.begin()->first < triParent.begin()->first)
        Pop_finale.bestIndividu = triEnfant.begin()->second;
    else
        Pop_finale.bestIndividu = triParent.begin()->second;

    return (Pop_finale);
}

// ------------------------------------ FONCTION ALGO GENETIQUE -------------------------------------------
Population algo_genetique(int iter, double proba, typeselection sel, typefinale fin, int taille, Individu* indiv0, int q)
{
    srand(time(NULL));
    int borne=0 ;
    indiv0 = indiv0->initialise_indiv() ;

    // Generation de P_0
    Population pop_0(taille) ;
    for(int i=0 ; i<taille ; i++)
    {
        pop_0.popu.at(i) = indiv0 ;
    }
    pop_0.bestIndividu = indiv0 ;

    //
    while (borne < iter)
    {
        // Generation des reproducteurs
        Population pop_tilde(taille) ;
      if (sel == roulette)
            pop_tilde = pop_0.selection_roulette() ;
        if (sel == rang)
            pop_tilde = pop_0.selection_rang() ;
        if (sel == tournoi)
            pop_tilde = pop_0.selection_tournoi(proba) ;

        // Hybridation & mutation
        Population pop_enfant(taille) ;
        for (int i=0 ; i<taille ; i+=2)
        {
            //-----------HYBRIDATION---------------------
            pair<Individu*,Individu*> cross_ ;
            cross_ = pop_tilde.popu.at(i)->crossover(*pop_tilde.popu.at(i+1)) ;
            pop_enfant.popu.at(i) = cross_.first ;
            pop_enfant.popu.at(i+1) = cross_.second ;

            //-----------MUTATION---------------------
            pop_enfant.popu.at(i) = &pop_enfant.popu.at(i)->flip() ;
            pop_enfant.popu.at(i+1) = &pop_enfant.popu.at(i+1)->flip() ;
        }

        //-------------------------SELECTION----------------------
        Population new_pop(taille) ;
        if (fin==elite)
            new_pop = pop_finale_elitisme(q,pop_0,pop_enfant) ;
        if (fin==enfant)
            new_pop = pop_finale_enfants(pop_0,pop_enfant) ;

    }
    return pop_0 ;

}
