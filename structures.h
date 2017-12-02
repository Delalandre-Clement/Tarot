/* **********************************************************
Cl�ment Delalandre - LP AII Nice
Projet : Tarot - LP AII

Headers des structures
************************************************************/

#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <SDL_image.h>


typedef struct carte Carte; //Carte de jeu
struct carte
{
    unsigned int type;      //Type de la carte (Pique, carreau, coeur, tr�fle ou atout)
    unsigned int chiffre;   //Chiffre sur la carte ( 1...10 V C D R // 1...21)
    SDL_Surface *recto;
    SDL_Surface *verso;
    SDL_Surface *rectoy;
    SDL_Surface *versoy;
    SDL_Rect position;
    struct carte *suivant;  //Pointeur sur la carte suivante dans lea liste
};


typedef struct Joueur Joueur;   //Joueur
struct Joueur
{
    char pseudo[20];    //pseudo du joueur
    int points;//Points du joueur
    SDL_Rect position;
    SDL_Rect effacecarte;
    SDL_Rect poschien;
    SDL_Rect pospseudo;
    SDL_Rect pospoint;
    SDL_Rect poscartejoue;
    Carte *Carte_Main;  //Cartes du joueur
    Carte *PliGagne;    //Tas de cartes gagn�e dans la manche
};

typedef struct partie Partie;
struct partie
{
    int manche;         //Num�ro de Manche
    int preneur;        //Personne qui souhaite prendre
    int mise;           //Mise du preneur
    int bout;           //Nombre de bout du preneur
    int distributeur;   //Personne qui distribue les cartes
    int tour_carte;     //Num�ro du pli de la manche
};

typedef struct pli Pli;
struct pli
{
    int meneur;         //Personne qui pose la premi�re carte � chaque pli
    int couleur_meneur; //Couleur pos�e par le meneur
    int valeur_meneur;  //Valeur de la carte du meneur
    int couleur_max;    //Couleur qui m�ne actuellement la partie
    int valeur_max;     //Valeur de la carte qui m�ne la partie
    int joueur_max;     //Numero de joueru possedant la meilleure carte
    int tour_joueur;    //Joueur qui doit jouer
    int numero_pli;     //Numero du pli en cours
    Carte *CartesPli;   //Cartes jou�e pendant le pli
};

void InitialisationPosition(SDL_Rect *, int, int, int, int);

#endif // STRUCTURES_H_INCLUDED
