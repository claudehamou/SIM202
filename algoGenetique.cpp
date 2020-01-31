#include "algoGenetique.h"
#include <cstdlib>
#include <ctime>

int rand_0_n(int n) // fonction qui genere un entier aleatoire entre 0 et n-1 inclus
{
    return rand()%n;
}

double reel_rand(double a, double b) // genere un nombre random entre a et b (reel)
{
    return (rand()/(double)RAND_MAX) * (b-a) + a;
}

Individu*& Population::selection_roulette()
{
    srand(time(NULL));
    double S = 0;
    vector<Individu*>::iterator it=popu.begin();
    for(;it!=popu.end();it++)
    {
        S+=(*it).adaptation();
    }
    double r = reel_rand(0,S);
    double S_aux = 0;
    vector<Individu*>::iterator it2=popu.begin();
    while (S_aux < r || it2!=popu.end())
    {
        S_aux+=(*it2).adaptation();
        it2++;
    }
    return (*it2)
}

Individu*& Population::selection_rang()
{
    int p = popu.size();
    int i = 0;
    int j = 0;
    vector<Individu*>::iterator it=popu.begin();
    for(;it!=popu.end();it++,i++)
    {
        double adapt = (*it).adaptation();
        vector<Individu*>::iterator it2=it;
        for(;it2!=popu.end();it2++,j++)
        {
            if ((*it2).adaptation() < adapt)
            {
                adapt = (*it2).adaptation();
                popu.at(j)
            }
        }
    }
}
