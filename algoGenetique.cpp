#include "algoGenetique.h"
#include <cstdlib>
#include <ctime>
#include <map>
#include <list>
#include <iostream>

int rand_0_n(int n) // fonction qui genere un entier aleatoire entre 0 et n-1 inclus, proba uniforme
{
    return rand() % n;
}

double reel_rand(double a, double b) // genere un nombre random entre a et b (reel), proba uniforme
{
    return (rand() / (double)RAND_MAX) * (b - a) + a;
}

// OPERATEUR = ET CONSTRUCTEUR PAR COPIE

Population::Population(const Population& pop)
{
    taillePopulation = pop.taillePopulation;
    popu.resize(taillePopulation);
    for (int i = 0; i < taillePopulation; i++)
    {
        if (pop.popu[i]==0){popu[i]=0;}
        else {popu[i] = pop.popu[i]->clone();}
    }
    if (pop.bestIndividu!=0)
    {
        bestIndividu=pop.bestIndividu->clone();
    }
    else{bestIndividu = 0;}
}

Population& Population::operator=(const Population& pop)
{
    clean();
    taillePopulation = pop.taillePopulation;
    popu.resize(taillePopulation);
    for (int i = 0; i < taillePopulation; i++)
    {
        if (pop.popu[i] == 0) {popu[i] = 0;}
        else {popu[i] = pop.popu[i]->clone();}
    }
    if (pop.bestIndividu != 0)
    {
        bestIndividu = pop.bestIndividu->clone();
    }
    else {bestIndividu = 0;}
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
        vector<Individu*>::iterator it = popu.begin();
        for (; it != popu.end(); it++)
        {
            S += (*it)->adaptation();            //somme de toutes les fonctions d'adaptation
        }
        double r = reel_rand(0, S);
        double S_aux = 0;
        vector<Individu*>::iterator it2 = popu.begin();
        while (S_aux < r && it2 != popu.end())
        {
            S_aux += (*it2)->adaptation();
            it2++;
        }
        if (it2 == popu.end())
        {
            enfants.popu.at(parcours) = (*popu.rbegin())->clone();
        }
        else
        {
            enfants.popu.at(parcours) = (*it2)->clone();
        }
        parcours++;
    }
    enfants.popu.at(0)=bestIndividu->clone(); //on place le meilleur individu en 0
    return (enfants);
}

/////////////////////////////////// SELECTION PAR RANG /////////////////////////////////////////////////

Population Population::selection_rang()
{
    int p = popu.size();
    Population enfants(p);
    int parcours = 0;
    double S = p * (p + 1) / 2;       //Somme de tous les rangs (de 1 a p)
    while (parcours < p)
    {
        int i = 0;
        multimap <double, Individu*> tripop; // permet de trier
        vector<Individu*>::iterator it = popu.begin();
        for (; it != popu.end(); it++)
        {
            tripop.insert(make_pair(-((*it)->adaptation()), *it));
        }
        double r = reel_rand(0, S);      //rang limite r selectionne entre 0 et S
        double S_aux = 0;
        multimap <double, Individu*>::iterator it2 = tripop.begin();
        while (S_aux < r && it2 != tripop.end())
        {
            S_aux += i + 1;
            it2++;
            i++;
        }
        if (it2 == tripop.end())
        {
            enfants.popu.at(parcours) = tripop.rbegin()->second->clone();
        }
        else
        {
            enfants.popu.at(parcours) = it2->second->clone();
        }
        parcours++;
    }
    enfants.popu.at(0)=bestIndividu->clone(); //on place le meilleur individu en 0
    return (enfants);
}

/////////////////////////////////// SELECTION PAR TOURNOI /////////////////////////////////////////////////

Population Population::selection_tournoi(const double proba)
{
    Population enfant(taillePopulation);

    list <pair<Individu*, Individu*> > pair_ind;
    // Initialisation des n paires de n individus d'une population

    for (int i = 0; i < taillePopulation; i++)
    {
        pair_ind.push_back(std::make_pair(popu[i], popu[rand_0_n(taillePopulation)]));
    }

    // Parcours des paires et sélection
    list <pair<Individu*, Individu*> > ::iterator itl = pair_ind.begin();
    int i = 0;
    for (; itl != pair_ind.end(); ++itl, i++)
    {
        // Meilleure fonction d'adaptation
        int best;
        if ((itl->first)->adaptation() < (itl->second)->adaptation())
            best = 1;
        else
            best = 2;

        // Choix du vainqueur
        double prb = reel_rand(0, 1);
        if ((prb < proba && best == 1) || (prb > proba && best == 2))
            enfant.popu[i] = itl->first->clone();
        else
            enfant.popu[i] = itl->second->clone();
    }

    enfant.popu.at(0)=bestIndividu->clone(); //on place le meilleur individu en 0
    return (enfant);
}

//////////////////////////// SELECTION FINALE QUE LES ENFANTS ///////////////////////

Population& pop_finale_enfants(const Population& parent, Population& enfant)
{
    std::vector<Individu*>::iterator it = enfant.popu.begin();
    double best = (parent.bestIndividu)->adaptation();
    enfant.bestIndividu = parent.bestIndividu->clone();
    double best_i;

    for (; it != enfant.popu.end(); it++) //on cherche le meilleur individu de enfant
    {
        best_i = (*it)->adaptation();
        if (best_i < best)
            {enfant.bestIndividu = (*it)->clone();
            best = best_i;}
    }

    return enfant;
}

//////////////////////////// SELECTION FINALE ELITISME ///////////////////////

Population pop_finale_elitisme(int q, const Population& parent, const Population& enfant)
{
    int p = parent.popu.size();
    if (q > p || q < 0)
    {
        cout << "Taille incompatible: q>p ou q<0";
        exit(-1);
    }

    Population Pop_finale(p);
    multimap <double, Individu*> triParent; // permet de trier dans l'ordre croissant avec insert()
    multimap <double, Individu*> triEnfant;

    vector<Individu*>::const_iterator it = parent.popu.begin();
    for (; it != parent.popu.end(); it++)
    {
        triParent.insert(make_pair(((*it)->adaptation()), *it));
    }

    vector<Individu*>::const_iterator it2 = enfant.popu.begin();
    for (; it2!= enfant.popu.end(); it2++)
    {
        triEnfant.insert(make_pair(((*it2)->adaptation()), *it2));
    }

    int k = 0;
    int j = 0;
    multimap <double, Individu*>::iterator it3 = triParent.begin();
    while (k < q)
    {
        Pop_finale.popu.at(k) = it3->second->clone();
        k++;
        it3++;
    }

    multimap <double, Individu*>::iterator it4 = triEnfant.begin();
    while (j < p - q)
    {
        Pop_finale.popu.at(j + q) = it4->second->clone();
        j++;
        it4++;
    }

    if (triEnfant.begin()->first < triParent.begin()->first)
        Pop_finale.bestIndividu = triEnfant.begin()->second->clone();
    else
        Pop_finale.bestIndividu = triParent.begin()->second->clone();

    return (Pop_finale);
}

// ------------------------------------ FONCTION ALGO GENETIQUE -------------------------------------------
Individu* algo_genetique(int iter, double proba, typeselection sel, typefinale fin, int taille, Individu* indiv0, int q)
{
    srand(time(NULL));
    int borne = 0;
    indiv0 = indiv0->initialise_indiv();

    if (taille % 2 != 0)
        taille += 1;

    // Generation de P_0
    Population pop_0(taille);
    for (int i = 0; i < taille; i++)
    {
        pop_0.popu.at(i) = indiv0->clone();
    }
    pop_0.bestIndividu = indiv0->clone();

    //
    while (borne < iter)
    {   // Generation des reproducteurs
        Population pop_tilde(taille);
        if (sel == roulette)
            pop_tilde = pop_0.selection_roulette();
        if (sel == rang)
            pop_tilde = pop_0.selection_rang();
        if (sel == tournoi)
            pop_tilde = pop_0.selection_tournoi(proba);

        // Hybridation & mutation
        Population pop_enfant(taille);
        for (int i = 0; i < taille; i += 2)
        {
            //-----------HYBRIDATION---------------------
            pair<Individu*, Individu*> cross_;
            cross_ = pop_tilde.popu.at(i)->crossover(*pop_tilde.popu.at(i + 1));
            pop_enfant.popu.at(i) = cross_.first;
            pop_enfant.popu.at(i + 1) = cross_.second;

            //-----------MUTATION---------------------
            pop_enfant.popu.at(i) = &pop_enfant.popu.at(i)->flip();
            pop_enfant.popu.at(i + 1) = &pop_enfant.popu.at(i + 1)->flip();
        }
        pop_enfant.popu.at(2)=pop_0.bestIndividu->clone();  //comme le meilleur etait en 0, 0 et 1 descendent du meilleur : on remplace plutot 2 par bestIndividu, pour le sauvegarder

        //-------------------------SELECTION----------------------
        Population new_pop(taille);
        if (fin == elite)
            new_pop = pop_finale_elitisme(q, pop_0, pop_enfant);
        if (fin == enfant)
            new_pop = pop_finale_enfants(pop_0, pop_enfant);

        if ((pop_0.bestIndividu)->adaptation() > (new_pop.bestIndividu)->adaptation())  //on veut garder la plus basse fonction d'adaptation
        {
            pop_0 = new_pop;
            borne = 0;
        }
        else
        {
            borne += 1;
        }

        cout << pop_0.bestIndividu->adaptation()<<endl;
    }
    return pop_0.bestIndividu;

}
