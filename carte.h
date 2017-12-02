/* **********************************************************
Clément Delalandre - LP AII Nice
Projet : Tarot - LP AII

Header fonctions liées aux cartes
************************************************************/

#ifndef CARTE_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "joueur.h"
#include "structures.h"
#include "liste_chainee.h"
#include "jeu_carte.h"
#include "fichier.h"
#include "affichage.h"
#include <SDL/SDL.h>
#include <SDL_image.h>

//Prototype des fonctions
Carte *Generation_Cartes(void);   //Génère le tas de carte en début de partie
Carte *AjoutCarte(Carte *,int ,int ); //Ajoute carte à la liste chainée générée par Generaton_Carte
Carte *RegrouperCarte(Carte *,Joueur *,Carte *);     //Regroupe les carte si aucun joueur ne prend
Carte *Melange_Cartes(Carte *);     //Melange le tas de carte
Carte *TriCarte(Carte *);
Carte *DistributionCarte(Carte *,Joueur *);   //Distribue les cartes aux joueurs
void EchangeChien(Joueur *, Carte *, int, SDL_Surface *);    //Preneur peux echanger ses cartes avec le chien
Carte *ExtractionCarte(Carte *, int);
void MiseAuChien(Joueur *, int, int);
Carte *ViderPli(Pli *, Joueur *, int);
Carte *RecuperationInfosCarte(Carte *, int);
void ClearCartes(SDL_Surface *);

#define CARTE_H_INCLUDED
#endif // CARTE_H_INCLUDED


