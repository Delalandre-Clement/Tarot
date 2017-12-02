/* **********************************************************
Clément Delalandre - LP AII Nice
Projet : Tarot - LP AII

Header de joueur.c
************************************************************/
#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "carte.h"
#include "affichage.h"
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>

//Prototypes des fonctions
void ChoixProfil(void);
void NouveauProfil(void);
void ChargerProfil(void);
Joueur *NewJoueur(SDL_Surface *);

#endif // JOUEUR_H_INCLUDED
