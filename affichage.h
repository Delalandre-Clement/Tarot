#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

#include"joueur.h"
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>

void Afficher_ListeX (Carte *, SDL_Rect, SDL_Surface *, int);
void Afficher_ListeY(Carte *, SDL_Rect , SDL_Surface *, int);
void Afficher_ListeXR(Carte *, SDL_Rect , SDL_Surface *, int);
void Afficher_ListeYR(Carte *, SDL_Rect , SDL_Surface *, int);
void AfficheTexte(SDL_Surface *, SDL_Rect *, int, char *);
void AfficheJeu(SDL_Surface *, Joueur *);
void EffacerPli(SDL_Surface *, Joueur *);
void AffichageTextePrise(SDL_Surface *, SDL_Rect, int);
int AttenteClicXI(int);
int AttenteClicYI(int);
int AttenteClicXII(int);
int AttenteClicYII(int);
void AffichagePoints(SDL_Surface *, Joueur *);

#endif // AFFICHAGE_H_INCLUDED
