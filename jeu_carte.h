/* **********************************************************
Clément Delalandre - LP AII Nice
Projet : Tarot - LP AII

Headers de la gestion du jeu
************************************************************/
#ifndef JEU_CARTE_H_INCLUDED
#define JEU_CARTE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "liste_chainee.h"
#include "structures.h"
#include "affichage.h"

Partie *Initialisation_Partie(void);
void Choix_Preneur(Joueur *,Partie *, SDL_Surface *);
void Manche_Jeu(Joueur *, Partie *, SDL_Surface *);
int Verification_Carte(Pli *, Joueur *, int, int);
int CarteJouable(Pli *, Carte *, int, Carte *);
int RechercheTypeCarte(Carte *, int);
void ComparaisonPuissanceCarte(Pli *, int);
int RechercheAtoutMax(Carte *);
void ComptagePoint(Joueur *, Partie *);
int SelectionCarte(Joueur *, SDL_Rect, int, int);
void CommencerJouer(SDL_Surface *, int ,int);
int ContinuerJouer(SDL_Surface *);

#endif // JEU_CARTE_H_INCLUDED
