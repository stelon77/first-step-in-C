#include <stdio.h>
#include <stdlib.h>
#include "essai.h"
#include "tableaux.h"

void affichetableau (int tableau[], int tailletableau)
{
int i=0;

while (i < tailletableau)
    {
    printf("%d\n", tableau[i]);
    i++;
    }
}


int sommetableau (int tableau[], int tailletableau)
{
    int i = 0;
    int somme = 0;
    while (i < tailletableau)
    {
        somme = somme + tableau[i];
        i++;
    }
    return somme;
}


double moyennetableau (int tableau[], int tailletableau)
{
    int i = 0;
    int somme = 0;
    while (i < tailletableau)
    {
        somme = somme + tableau[i];
        i++;
    }
    return somme / tailletableau;
}


void copiertableau (int tableauoriginal[], int tableaucopie[], int tailletableau)
{
   int i = 0;
   while (i < tailletableau)
   {
       tableaucopie[i] = tableauoriginal[i];
       i++;
   }
}


void maximumtableau(int tableau[], int tailletableau, int valeurmax)
{
    int i = 0;
    while (i < tailletableau)
    {
        if (tableau[i] > valeurmax)
        {
            tableau[i] = 0;
            i++;
        }
        else
        {
            i++;
        }
    }
}


void ordonnertableau (int tableau[], int tailletableau)
{
    int i = 0;
    int valeurintermediaire = 0;
    int deuxiemecompteur = 0;

    while(i < tailletableau - 1)
    {
        deuxiemecompteur = i + 1;
        while (deuxiemecompteur <= tailletableau)
        {
            if (tableau[i] > tableau[deuxiemecompteur])
            {
            valeurintermediaire = tableau[i];
            tableau[i] = tableau[deuxiemecompteur];
            tableau[deuxiemecompteur] = valeurintermediaire;
            }
        deuxiemecompteur++;
        }
    i++;
    }
}
