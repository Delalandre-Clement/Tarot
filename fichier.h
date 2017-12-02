/* **********************************************************
Clément Delalandre - LP AII Nice
Projet: Tarot - LP AII

Header Gestion de Fichiers (fichier.c)
************************************************************/

#ifndef FICHIER_H_INCLUDED
#define FICHIER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <dirent.h>
#include <errno.h>
#include "joueur.h"

FILE *fichier;

//Prototypes des fonctions
void NouveauProfil(void);
void ChargerProfil(void);
void NumeroCarte(char *, int, int);
void NumeroCarter(char *, int, int);

#endif // FICHIER_H_INCLUDED

#ifndef WIN32
    #include <sys/types.h>
#endif // WIN32

