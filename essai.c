#include <stdio.h>
#include <stdlib.h>
#include "essai.h"
#include "tableaux.h"

double airerectangle(double largeur, double hauteur)
{
    return largeur * hauteur;
}

void heuresminutes (int  *heures, int *minutes)
{
    *heures = *minutes / 60 + *heures;
    *minutes = *minutes % 60;
}

int longueurschaine(const char chaine[])
{
    int compteur = 0;

    while(chaine[compteur] != '\0')
    {
        compteur++;
	printf("le compteur est à %d", compteur);
    }
    return compteur;
}
