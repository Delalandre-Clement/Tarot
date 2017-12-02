#include "affichage.h"

void Afficher_ListeX(Carte *k, SDL_Rect placement, SDL_Surface *ecran, int ecart)       //Fonction d'affichage de la liste chainée
{
    int cpt=1;
    while(k!=NULL)      //Tant que l'on atteint pas le dernier élément de la liste chainée
    {
        SDL_BlitSurface(k->recto, NULL, ecran, &placement);
        k->position.x=placement.x;
        k->position.y=placement.y;
        placement.x=placement.x+ecart;
        k=k->suivant;       //Incrémentation à l'élément suivant
        cpt++;
    }
    SDL_Flip(ecran);
}

void Afficher_ListeY(Carte *k, SDL_Rect placement, SDL_Surface *ecran, int ecart)       //Fonction d'affichage de la liste chainée
{
    int cpt=1;
    while(k!=NULL)      //Tant que l'on atteint pas le dernier élément de la liste chainée
    {
        SDL_BlitSurface(k->rectoy, NULL, ecran, &placement);
        k->position.x=placement.x;
        k->position.y=placement.y;
        placement.y=placement.y+ecart;
        k=k->suivant;       //Incrémentation à l'élément suivant
        cpt++;
    }
    SDL_Flip(ecran);
}

void Afficher_ListeXR(Carte *k, SDL_Rect placement, SDL_Surface *ecran, int ecart)       //Fonction d'affichage de la liste chainée
{
    int cpt=1;
    while(k!=NULL)      //Tant que l'on atteint pas le dernier élément de la liste chainée
    {
        SDL_BlitSurface(k->verso, NULL, ecran, &placement);
        k->position.x=placement.x;
        k->position.y=placement.y;
        placement.x=placement.x+ecart;
        k=k->suivant;       //Incrémentation à l'élément suivant
        cpt++;
    }
    SDL_Flip(ecran);
}

void Afficher_ListeYR(Carte *k, SDL_Rect placement, SDL_Surface *ecran, int ecart)       //Fonction d'affichage de la liste chainée
{
    int cpt=1;
    while(k!=NULL)      //Tant que l'on atteint pas le dernier élément de la liste chainée
    {
        SDL_BlitSurface(k->versoy, NULL, ecran, &placement);
        k->position.x=placement.x;
        k->position.y=placement.y;
        placement.y=placement.y+ecart;
        k=k->suivant;       //Incrémentation à l'élément suivant
        cpt++;
    }
    SDL_Flip(ecran);
}

void AfficheTexte(SDL_Surface *screen, SDL_Rect *position, int taille, char *texte)
{
    TTF_Font *police = NULL;
    police = TTF_OpenFont("times.ttf", taille);
    if(police == NULL ){exit(-1);}
    SDL_Color couleurNoire = {0, 0, 0};

    SDL_Surface *message = TTF_RenderText_Blended(police, texte, couleurNoire);
    SDL_BlitSurface(message, NULL, screen, position);

    SDL_Flip(screen); /* Affichage */
    TTF_CloseFont(police);
}

void AfficheJeu(SDL_Surface *screen, Joueur *TableauJoueur)
{
    Afficher_ListeXR(TableauJoueur[0].Carte_Main, TableauJoueur[0].position, screen, 45);
    Afficher_ListeYR(TableauJoueur[1].Carte_Main, TableauJoueur[1].position, screen, 45);
    Afficher_ListeXR(TableauJoueur[2].Carte_Main, TableauJoueur[2].position, screen, 45);
    Afficher_ListeYR(TableauJoueur[3].Carte_Main, TableauJoueur[3].position, screen, 45);
}

void EffacerPli(SDL_Surface *screen, Joueur *TabJoueur)
{
    SDL_FillRect(screen, &TabJoueur[0].poscartejoue, SDL_MapRGB(screen->format, 42, 65, 47));
    SDL_FillRect(screen, &TabJoueur[1].poscartejoue, SDL_MapRGB(screen->format, 42, 65, 47));
    SDL_FillRect(screen, &TabJoueur[2].poscartejoue, SDL_MapRGB(screen->format, 42, 65, 47));
    SDL_FillRect(screen, &TabJoueur[3].poscartejoue, SDL_MapRGB(screen->format, 42, 65, 47));
    SDL_Flip(screen);
}

void AffichageTextePrise(SDL_Surface *ecran, SDL_Rect PosTxt, int numjoueur)
{
    if(numjoueur == 0 || numjoueur ==2)
    {
        AfficheTexte(ecran, &PosTxt, 22, "Passer");
        PosTxt.x=PosTxt.x+130;
        AfficheTexte(ecran, &PosTxt, 22, "Petite");
        PosTxt.x=PosTxt.x+130;
        AfficheTexte(ecran, &PosTxt, 22, "Pousse");
        PosTxt.x=PosTxt.x+130;
        AfficheTexte(ecran, &PosTxt, 22, "Garde");
    }
    else
    {
        AfficheTexte(ecran, &PosTxt, 22, "Passer");
        PosTxt.y=PosTxt.y+60;
        AfficheTexte(ecran, &PosTxt, 22, "Petite");
        PosTxt.y=PosTxt.y+60;
        AfficheTexte(ecran, &PosTxt, 22, "Pousse");
        PosTxt.y=PosTxt.y+60;
        AfficheTexte(ecran, &PosTxt, 22, "Garde");
    }
}

int AttenteClicXI(int premier_choisir)
{
    int continuer = 1;
    SDL_Event event;
    SDL_Rect posclic, posbouton;

    InitialisationPosition(&posbouton, 270, 700, 120 ,50);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                posclic.x = event.button.x;
                posclic.y = event.button.y;
                if(posclic.y > posbouton.y && posclic.y < (posbouton.y+50))
                {
                    if( posclic.x > 270  && posclic.x < 390)  //Clic sur une carte de la liste ?
                    {
                        return 0;
                    }
                    if( posclic.x > 400  && posclic.x < 520)  //Clic sur une carte de la liste ?
                    {
                        return 1;
                    }
                    if( posclic.x > 530  && posclic.x < 650)  //Clic sur une carte de la liste ?
                    {
                        return 2;
                    }
                    if( posclic.x > 660  && posclic.x < 780)  //Clic sur une carte de la liste ?
                    {
                        return 3;
                    }
                }
            }
            break;
        case SDL_QUIT:
            exit(-23);
        break;
        }
    }
    return 0;
}

int AttenteClicYI(int premier_choisir)
{
    int continuer = 1;
    SDL_Event event;
    SDL_Rect posclic, posbouton;

    InitialisationPosition(&posbouton, 300, 410, 120 ,50);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                posclic.x = event.button.x;
                posclic.y = event.button.y;
                if( posclic.x > 300  && posclic.x < 420)  //Clic sur une carte de la liste ?
                {
                    if(posclic.y > 410 && posclic.y < 460)
                    {
                        return 0;
                    }
                    if(posclic.y > 470 && posclic.y < 530)
                    {
                        return 1;
                    }
                    if(posclic.y > 540 && posclic.y < 590)
                    {
                        return 2;
                    }
                    if(posclic.y > 600 && posclic.y < 650)
                    {
                        return 3;
                    }
                }
            }
            break;
        case SDL_QUIT:
            exit(-23);
            break;
        }
    }
    return 0;
}

int AttenteClicXII(int premier_choisir)
{
    int continuer = 1;
    SDL_Event event;
    SDL_Rect posclic, posbouton;

    InitialisationPosition(&posbouton, 270, 350, 120 ,50);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                posclic.x = event.button.x;
                posclic.y = event.button.y;
                if(posclic.y > posbouton.y && posclic.y < (posbouton.y+50))
                {
                    if( posclic.x > 270  && posclic.x < 390)  //Clic sur une carte de la liste ?
                    {
                        return 0;
                    }
                    if( posclic.x > 400  && posclic.x < 520)  //Clic sur une carte de la liste ?
                    {
                        return 1;
                    }
                    if( posclic.x > 530  && posclic.x < 650)  //Clic sur une carte de la liste ?
                    {
                        return 2;
                    }
                    if( posclic.x > 660  && posclic.x < 780)  //Clic sur une carte de la liste ?
                    {
                        return 3;
                    }
                }
            }
            break;
        case SDL_QUIT:
            exit(-23);
        break;
        }
    }
    return 0;
}

int AttenteClicYII(int premier_choisir)
{
    int continuer = 1;
    SDL_Event event;
    SDL_Rect posclic, posbouton;

    InitialisationPosition(&posbouton, 700, 410, 120 ,50);


    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                posclic.x = event.button.x;
                posclic.y = event.button.y;
                if( posclic.x > 700  && posclic.x < 820)  //Clic sur une carte de la liste ?
                {
                    if(posclic.y > 410 && posclic.y < 460)
                    {
                        return 0;
                    }
                    if(posclic.y > 470 && posclic.y < 530)
                    {
                        return 1;
                    }
                    if(posclic.y > 540 && posclic.y < 590)
                    {
                        return 2;
                    }
                    if(posclic.y > 600 && posclic.y < 650)
                    {
                        return 3;
                    }
                }
            }
            break;
        case SDL_QUIT:
            exit(-23);
            break;
        }
    }
    return 0;
}

void AffichagePoints(SDL_Surface *screen, Joueur *TabJoueur)
{
    char textepoint[15]="";
    int i=0;

    SDL_FillRect(screen, &TabJoueur[0].pospoint, SDL_MapRGB(screen->format, 42, 65, 47));
    SDL_FillRect(screen, &TabJoueur[1].pospoint, SDL_MapRGB(screen->format, 42, 65, 47));
    SDL_FillRect(screen, &TabJoueur[2].pospoint, SDL_MapRGB(screen->format, 42, 65, 47));
    SDL_FillRect(screen, &TabJoueur[3].pospoint, SDL_MapRGB(screen->format, 42, 65, 47));
    for(i=0;i<4;i++)
    {
        sprintf(textepoint, "%d points", TabJoueur[i].points);
        AfficheTexte(screen, &TabJoueur[i].pospoint, 16, textepoint);
    }
}
