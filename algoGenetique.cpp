#include "algoGenetique.h"

Individu::Individu(int n)
{
    init(n);
    for (int i=0;i<n;i++) genome[i]=i;
}

Individu::Individu(const Individu& ind)
{
    tailleGenome = ind.tailleGenome;
    for (int i=0;i<tailleGenome;i++) genome[i]=ind.genome[i];
}

Individu::~Individu()
{
    clearing();
}

