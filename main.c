/* **********************************************************
Clément Delalandre - LP AII Nice
Projet : Tarot - LP AII

Fonction : Main
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "carte.h"
#include "joueur.h"
#include "liste_chainee.h"
#include "jeu_carte.h"
#include "affichage.h"
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>

void pause();

int main(int argc, char *argv[])
{
     /* Créatin des varaiables SDL */
    SDL_Surface *ecran=NULL, *tapisfond=NULL;
    SDL_Rect postapis, pospioche;

    /* Parametrage des position */
    InitialisationPosition(&postapis, 0, 0, 0, 0);
    InitialisationPosition(&pospioche, 720, 700, 75, 45);

    /* Demarrage de la SDL*/
   if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    /* Ouverture de la fenetre */
    ecran=SDL_SetVideoMode(1050, 1050, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    if (ecran == NULL)
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* Demarrage de la SDL_TTF */
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    /* Parametrage de la fenêtre */
    SDL_WM_SetIcon(IMG_Load("Images\\Icone.png"), NULL);
    SDL_WM_SetCaption("Tarot", NULL);

    /* Chargement du Tapis de fond */
    tapisfond = IMG_Load("Images/Tapis.jpg");
    if(tapisfond == NULL) {exit(-1);}
    SDL_BlitSurface(tapisfond, NULL, ecran, &postapis);

    /* Commencer a jouer */
    CommencerJouer(ecran,465,275);

    /*Initialisation Partie*/
    Partie *Infos_Partie=Initialisation_Partie();       //Initialisation de la structure des infos de la partie
    Joueur *TabJoueur=NewJoueur(ecran);                 //Creation Tableau contenant les infos des joueurs
    Carte *Paquet=Generation_Cartes();                  //Creation des cartes de jeu
    Carte *Chien;

    /* Affichage première carte */
    SDL_BlitSurface(Paquet->verso, NULL, ecran, &pospioche);

    do
    {
        do
        {
            if(Paquet->suivant==NULL)    //Cartes distribuée & pas de preneur => regrouper les cartes
            {
                    Paquet=RegrouperCarte(Chien,TabJoueur,Paquet);
                    Chien=NULL;
            }
            Paquet=Melange_Cartes(Paquet);                      //Melange des cartes
            Chien=DistributionCarte(Paquet,TabJoueur);   //Distribution des cartes
            SDL_FillRect(ecran, &pospioche, SDL_MapRGB(ecran->format, 42, 65, 47)); //Retire image du tas de carte
            SDL_Flip(ecran);

            Choix_Preneur(TabJoueur,Infos_Partie, ecran);

        }
        while(Infos_Partie->preneur==(-1));

        EchangeChien(TabJoueur,Chien,Infos_Partie->preneur, ecran);    //Preneur choisis les cartes du chien
        Chien=NULL; //RAZ du chien
        Manche_Jeu(TabJoueur,Infos_Partie, ecran); /* Jeu */
        Paquet=RegrouperCarte(Chien,TabJoueur,Paquet);
    }
    while(ContinuerJouer(ecran));

    /*Libération mémoire*/
    Detruire_Liste(Paquet);
    free(TabJoueur);
    Detruire_Liste(Chien);

    TTF_Quit();
    SDL_FreeSurface(tapisfond);
    SDL_Quit(); // Arrêt de la SDL

    return 0;
}

