/* **********************************************************
Clément Delalandre - LP AII Nice
Projet : Tarot - LP AII

Fonctions concernant les joueurs
************************************************************/
#include "joueur.h"

void ChoixProfil()
{
    fflush(stdin);  //Vide le tempon d'entrée

    int choix=0;
    printf("1 - Utiliser un profil de joueur existant.\n");
    printf("2 - Creer un nouveau profil de joueur.\n");
    printf("Votre choix ? ");
    do
    {
        scanf("%d",&choix);
        switch(choix)
        {
            case 1:
                ChargerProfil();
                break;
            case 2:
                NouveauProfil();
                break;
            default:
                printf("Veuillez choisir une des options possibles [1,2] : ");
                break;
        }
    }
    while(choix!=1 && choix!=2);
}

Joueur *NewJoueur(SDL_Surface *ecran)
{
    char nom[30] = "";
    char textepoint[15]="";

    Joueur *Tableau=(Joueur *)calloc(4,sizeof(Joueur));
    if (Tableau!=NULL)
    {
        int i;
        for(i=0;i<4;i++)
        {
            sprintf(nom, "Joueur %d", i+1);
            sprintf(textepoint, "%d points", Tableau[i].points);
            Tableau[i].points=0;

            switch(i)
            {
            case 0:
                InitialisationPosition(&Tableau[i].position, 120, 965, 85, 40);
                InitialisationPosition(&Tableau[i].effacecarte, 0, 965, 85, 1050);
                InitialisationPosition(&Tableau[i].poschien, 487.5, 787.5, 0, 0);
                InitialisationPosition(&Tableau[i].pospseudo, 500, 920, 0, 0);
                InitialisationPosition(&Tableau[i].pospoint, 500, 940, 0, 0);
                InitialisationPosition(&Tableau[i].poscartejoue, 505, 625, 79, 40);
                AfficheTexte(ecran, &Tableau[i].pospseudo, 16, nom);
                AfficheTexte(ecran, &Tableau[i].pospoint, 16, textepoint);
                break;
            case 1:
                InitialisationPosition(&Tableau[i].position, 10, 120, 40, 89);
                InitialisationPosition(&Tableau[i].effacecarte, 0, 0, 1050, 89);
                InitialisationPosition(&Tableau[i].poschien, 487.5, 787.5, 0, 0);
                InitialisationPosition(&Tableau[i].pospseudo, 95, 510, 0, 0);
                InitialisationPosition(&Tableau[i].pospoint, 95, 530, 0, 0);
                InitialisationPosition(&Tableau[i].poscartejoue, 350, 505, 40, 79);
                AfficheTexte(ecran, &Tableau[i].pospseudo, 16, nom);
                AfficheTexte(ecran, &Tableau[i].pospoint, 16, textepoint);
                break;
            case 2:
                InitialisationPosition(&Tableau[i].position, 120, 10, 89, 40);
                InitialisationPosition(&Tableau[i].effacecarte, 0, 0, 90, 1050);
                InitialisationPosition(&Tableau[i].poschien, 487.5, 787.5, 0, 0);
                InitialisationPosition(&Tableau[i].pospseudo, 500, 90, 0, 0);
                InitialisationPosition(&Tableau[i].pospoint, 500, 110, 0, 0);
                InitialisationPosition(&Tableau[i].poscartejoue, 505, 350, 79, 40);
                AfficheTexte(ecran, &Tableau[i].pospseudo, 16, nom);
                AfficheTexte(ecran, &Tableau[i].pospoint, 16, textepoint);
                break;
            case 3:
                InitialisationPosition(&Tableau[i].position, 965, 120, 40, 89);
                InitialisationPosition(&Tableau[i].effacecarte, 965, 0, 1050, 85);
                InitialisationPosition(&Tableau[i].poschien, 487.5, 787.5, 0, 0);
                InitialisationPosition(&Tableau[i].pospseudo, 880, 510, 0, 0);
                InitialisationPosition(&Tableau[i].pospoint, 880, 530, 0, 0);
                InitialisationPosition(&Tableau[i].poscartejoue, 625, 505, 40, 79);
                AfficheTexte(ecran, &Tableau[i].pospseudo, 16, nom);
                AfficheTexte(ecran, &Tableau[i].pospoint, 16, textepoint);
                break;
            default:
                exit(-1);
            }
        }
    }
    else exit(-1);

    return Tableau;
}
