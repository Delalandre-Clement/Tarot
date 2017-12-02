/* **********************************************************
Clément Delalandre - LP AII Nice
Projet : Tarot - LP AII

Gestion du jeu
************************************************************/
#include "jeu_carte.h"

Partie *Initialisation_Partie()
{
    Partie *Infos=malloc(sizeof(Partie));       //Allocation Mémoire
    if (Infos==NULL){exit(-1);}                 // Verification allocation
    Infos->manche=1;
    Infos->tour_carte=1;
    Infos->preneur=-1;
    Infos->mise=0;
    return Infos;
}

void Choix_Preneur(Joueur *Liste_Joueur,Partie *Infos, SDL_Surface *ecran)  //Choix du joueur qui mène la partie
{
    SDL_Rect PosBouton, postxt;
    SDL_Surface *Bouton=NULL;
    int cpt,i,premier_choisir=Infos->distributeur+1, choix=0;

    /* Tri des cartes */
    for(cpt=0;cpt<4;cpt++)
    {
        (Liste_Joueur+cpt)->Carte_Main=TriCarte(Liste_Joueur[cpt].Carte_Main);
    }


    /* Choix du preneur */
    for(cpt=0;cpt<4;cpt++)
    {
        ClearCartes(ecran);
        for(i=0;i<4;i++)
        {
            if( i == 0 || i == 2)
            {
                Afficher_ListeXR(Liste_Joueur[i].Carte_Main, Liste_Joueur[i].position, ecran, 45);      //Cache les cartes en main
            }
            else
            {
                Afficher_ListeYR(Liste_Joueur[i].Carte_Main, Liste_Joueur[i].position, ecran, 45);       //Cache les cartes en main
            }
        }

        /* Initialisation position des boutons */
        switch(premier_choisir)
        {
        case 0:
            InitialisationPosition(&PosBouton, 270, 700, 120 ,50);
            InitialisationPosition(&postxt, 296, 713, 0 ,0);
            break;
        case 1:
            InitialisationPosition(&PosBouton, 300, 410, 120 ,50);
            InitialisationPosition(&postxt, 326, 423, 0 ,0);
            break;
        case 2:
            InitialisationPosition(&PosBouton, 270, 350, 120 ,50);
            InitialisationPosition(&postxt, 296, 363, 0 ,0);
            break;
        case 3:
            InitialisationPosition(&PosBouton, 700, 410, 120 ,50);
            InitialisationPosition(&postxt, 726, 423, 0 ,0);
            break;
        default:
            exit(-1);
            break;
        }

        /* Affichage Cartes */
        if(premier_choisir == 0 || premier_choisir == 2)
            Afficher_ListeX(Liste_Joueur[premier_choisir].Carte_Main, Liste_Joueur[premier_choisir].position, ecran, 45);       //Affiche les cartes en main
        else
            Afficher_ListeY(Liste_Joueur[premier_choisir].Carte_Main, Liste_Joueur[premier_choisir].position, ecran, 45);       //Affiche les cartes en main

        /* Affichage bouton + texte */
        for(i=0;i<4;i++)
        {
            Bouton = SDL_CreateRGBSurface(SDL_HWSURFACE, 120, 50, 32, 0, 0, 0, 0);
            SDL_FillRect(Bouton, NULL, SDL_MapRGB(ecran->format, 170, 170, 170));
            SDL_BlitSurface(Bouton, NULL, ecran, &PosBouton);
            if (premier_choisir == 0 || premier_choisir == 2)
                InitialisationPosition(&PosBouton, PosBouton.x+130, PosBouton.y, PosBouton.h, PosBouton.w);
            else
                InitialisationPosition(&PosBouton, PosBouton.x, PosBouton.y+60, PosBouton.h, PosBouton.w);
        }
        AffichageTextePrise(ecran, postxt, premier_choisir);

        switch(premier_choisir)
        {
        case 0:
            InitialisationPosition(&PosBouton, 270, 700, 120 ,50);
            InitialisationPosition(&postxt, 296, 713, 0 ,0);
            choix=AttenteClicXI(premier_choisir);
            break;
        case 1:
            InitialisationPosition(&PosBouton, 300, 410, 120 ,50);
            InitialisationPosition(&postxt, 326, 423, 0 ,0);
            choix=AttenteClicYI(premier_choisir);
            break;
        case 2:
            InitialisationPosition(&PosBouton, 270, 350, 120 ,50);
            InitialisationPosition(&postxt, 296, 363, 0 ,0);
            choix=AttenteClicXII(premier_choisir);
            break;
        case 3:
            InitialisationPosition(&PosBouton, 700, 410, 120 ,50);
            InitialisationPosition(&postxt, 726, 423, 0 ,0);
            choix=AttenteClicYII(premier_choisir);
            break;
        default:
            exit(-1);
            break;
        }

        /* Transfert infos si prise */
        if(choix != 0 && choix > Infos->mise)
        {
            Infos->preneur=premier_choisir;
            Infos->mise=choix;
        }

        /*Efface les bouton + texte */
        if(premier_choisir == 0 || premier_choisir == 2)
        {
            for(i=0;i<4;i++)
            {
                SDL_FillRect(Bouton, NULL, SDL_MapRGB(ecran->format, 42, 65, 47));
                SDL_BlitSurface(Bouton, NULL, ecran, &PosBouton);
                InitialisationPosition(&PosBouton, PosBouton.x+130, PosBouton.y, PosBouton.h, PosBouton.w);
            }
        }
        else
        {
            for(i=0;i<4;i++)
            {
                SDL_FillRect(Bouton, NULL, SDL_MapRGB(ecran->format, 42, 65, 47));
                SDL_BlitSurface(Bouton, NULL, ecran, &PosBouton);
                InitialisationPosition(&PosBouton, PosBouton.x, PosBouton.y+60, PosBouton.h, PosBouton.w);
            }
        }
        premier_choisir++;          //Incrémentation
        if(premier_choisir>3){premier_choisir=0;}   //Retourne au premier joueur si on est au dernier
    }
    ClearCartes(ecran);
    AfficheJeu(ecran, Liste_Joueur);
}

void Manche_Jeu(Joueur *TabJoueur,Partie *Infos, SDL_Surface *screen)
{
    int carte_a_jouer=0,compteur;
    Pli *InfosPli=malloc(sizeof(Pli));
    if(InfosPli==NULL){exit(-1);}        //Err Allocation
    InfosPli->meneur=(Infos->distributeur)+1;       //Personne qui pose la première carte
    InfosPli->tour_joueur=InfosPli->meneur;           //Meneur qui commence a jouer
    InfosPli->numero_pli=1;
    InfosPli->CartesPli=NULL;
    Carte *CarteJoue;
    Carte *Memoire;
    SDL_Rect Test;
    InitialisationPosition(&Test, 400, 400, 0, 0);

    for(Infos->tour_carte=1;Infos->tour_carte<=18;Infos->tour_carte++)  //Boucle pour faire une manche complète
    {
        for(compteur=0;compteur<4;compteur++)   //Boucle pour faire jouer tous les joueurs
        {
            SDL_FillRect(screen, &TabJoueur[InfosPli->tour_joueur].effacecarte, SDL_MapRGB(screen->format, 42, 65, 47)); //Retire les cartes
            if(InfosPli->tour_joueur == 0 || InfosPli->tour_joueur == 2)
                Afficher_ListeX(TabJoueur[InfosPli->tour_joueur].Carte_Main, TabJoueur[InfosPli->tour_joueur].position, screen, 45);
            else
                Afficher_ListeY(TabJoueur[InfosPli->tour_joueur].Carte_Main, TabJoueur[InfosPli->tour_joueur].position, screen, 45);

            /* Verification carte valide (Jouable ou non ?) */
            carte_a_jouer=Verification_Carte(InfosPli, TabJoueur, InfosPli->tour_joueur, carte_a_jouer);  // Verifie la carte choisie

            /* Extraction de la carte */
            if(carte_a_jouer==0)    //1ère carte de la liste
            {
                CarteJoue=TabJoueur[InfosPli->tour_joueur].Carte_Main;               //Recupere adresse de l'element a extraire
                TabJoueur[InfosPli->tour_joueur].Carte_Main=TabJoueur[InfosPli->tour_joueur].Carte_Main->suivant;     //Nouveau 1er élément
                CarteJoue->suivant=NULL;                //Casse la liste
            }
            else{CarteJoue=ExtractionCarte(TabJoueur[InfosPli->tour_joueur].Carte_Main, carte_a_jouer+1);}   //Extraire carte de la main du joueur

            /* Affiche la carte au centre du tapis */
            if(InfosPli->tour_joueur == 0 || InfosPli->tour_joueur == 2)
                Afficher_ListeX(CarteJoue, TabJoueur[InfosPli->tour_joueur].poscartejoue, screen, 45);
            else
                Afficher_ListeY(CarteJoue, TabJoueur[InfosPli->tour_joueur].poscartejoue, screen, 45);

            /* Place carte dans le pli */
            Memoire=InfosPli->CartesPli;
            InfosPli->CartesPli=CarteJoue;
            InfosPli->CartesPli->suivant=Memoire;

            /* Efface la carte et affiche les cartes (verso)*/
            SDL_FillRect(screen, &TabJoueur[InfosPli->tour_joueur].effacecarte, SDL_MapRGB(screen->format, 42, 65, 47));
            if(InfosPli->tour_joueur == 0 || InfosPli->tour_joueur == 2)
                Afficher_ListeXR(TabJoueur[InfosPli->tour_joueur].Carte_Main, TabJoueur[InfosPli->tour_joueur].position, screen, 45);
            else
                Afficher_ListeYR(TabJoueur[InfosPli->tour_joueur].Carte_Main, TabJoueur[InfosPli->tour_joueur].position, screen, 45);

            /* Compare la puissance de la carte */
            ComparaisonPuissanceCarte(InfosPli,compteur);

            /* Passage Joueur Suivant */
            if(InfosPli->tour_joueur==3){InfosPli->tour_joueur=0;}
            else{InfosPli->tour_joueur++;}
        }

        /* Efface cartes jouées */
        SDL_FillRect(screen, &TabJoueur[0].poscartejoue, SDL_MapRGB(screen->format, 42, 65, 47));
        SDL_FillRect(screen, &TabJoueur[1].poscartejoue, SDL_MapRGB(screen->format, 42, 65, 47));
        SDL_FillRect(screen, &TabJoueur[2].poscartejoue, SDL_MapRGB(screen->format, 42, 65, 47));
        SDL_FillRect(screen, &TabJoueur[3].poscartejoue, SDL_MapRGB(screen->format, 42, 65, 47));

        /* Transfère le pli au joueur gagnant
        TabJoueur[InfosPli->joueur_max].PliGagne=ViderPli(InfosPli, TabJoueur, InfosPli->joueur_max);
        if(InfosPli->joueur_max == 0 || InfosPli->joueur_max == 2){SDL_BlitSurface(TabJoueur[InfosPli->joueur_max].PliGagne->verso, NULL, screen, &TabJoueur[InfosPli->joueur_max].poschien);}
        else{SDL_BlitSurface(TabJoueur[InfosPli->joueur_max].PliGagne->versoy, NULL, screen, &TabJoueur[InfosPli->joueur_max].poschien);}
        SDL_Flip(screen);
        */

        /* Préparation de la manche suivante */
        InfosPli->tour_joueur=InfosPli->joueur_max;
        InfosPli->meneur=InfosPli->joueur_max;
        InfosPli->numero_pli++; //Incrémentation du numéro de manche
    }
    ComptagePoint(TabJoueur, Infos);
    AffichagePoints(screen, TabJoueur);

    free(InfosPli);  //Libération mémoire
}

int Verification_Carte(Pli *Info_Pli, Joueur *TabJoueur, int numjoueur, int carte_a_verifier)
{
    int valide=0;       //Carte valide
    //Carte *CarteRecuperer;
    do
    {
        carte_a_verifier = SelectionCarte(TabJoueur, TabJoueur[numjoueur].position, numjoueur, 45);
        //Carte *CarteRecuperer=RecuperationInfosCarte(TabJoueur[numjoueur].Carte_Main, carte_a_verifier-1);    //Récupere les données de la carte
        valide=CarteJouable(Info_Pli,TabJoueur[numjoueur].Carte_Main,carte_a_verifier,RecuperationInfosCarte(TabJoueur[numjoueur].Carte_Main, carte_a_verifier-1));
    }
    while(valide==0);
    carte_a_verifier--;     //Decrementation pour obtenir la position dans la liste chainée
    return carte_a_verifier;
}

int CarteJouable(Pli *PliActuel, Carte *MainJoueur, int numero, Carte *CarteTester)
{
    if (PliActuel->meneur == PliActuel->tour_joueur){return 1;} //Tour du meneur (aucune carte sur le tapis)
    if (CarteTester->chiffre == 22){return 1;}      //Excuse
    int couleurmene= PliActuel->couleur_meneur;
    int couleurmax= PliActuel->couleur_max;
    int valeurmax =PliActuel->valeur_max;
    int presence_atout=RechercheTypeCarte(MainJoueur, 5);
    int atout_max=RechercheAtoutMax(MainJoueur);
    int presence_type_meneur=RechercheTypeCarte(MainJoueur, PliActuel->couleur_meneur);

    if(couleurmene==5)       // Atout demandé
    {
        if(presence_atout==1)   // Joueur possède atout
        {
            if(CarteTester->type == 5)  //Joueur joue de l'atout
            {
                if(CarteTester->chiffre > PliActuel->valeur_max)    // Carte > Carte max actuelle (atout)
                {
                    return 1;       //Valide
                }
                if ((CarteTester->chiffre < PliActuel->valeur_max) && (atout_max > PliActuel->valeur_max))  // Carte < Carte max er joueur possède Carte > Carte max
                {
                    return 0;       //Non valide
                }
                else            // Carte < Carte max mais joueur ne possède pas d'atout > Carte max
                {
                    return 1;
                }
            }
            else            // Le joueur a de l'atout mais n'en joue pas
            {
                return 0;   //Non valide
            }
        }
        else            // Le joueur n'a pas d'atout
        {
            return 1;   //Carte valide
        }
    }

    if(couleurmene != 5 && presence_type_meneur == 1)     // Demande =/= Atout et joueur possède carte du type demandé
    {
        if(CarteTester->type==couleurmene)       // Couleur carte = Couleur demandée
        {
            return 1;   //Valide
        }
        if(CarteTester->type!=couleurmene)      // Couleur Carte =/= Couleur demandée
        {
            return 0;   //Non valide
        }
    }

    if(couleurmene != 5 && presence_type_meneur == 0) // Demande =/= Atout et joueur ne possède pas de carte du type demandé
    {
        if(presence_atout == 1)
        {
            if(CarteTester->type==5)
            {
                if(couleurmax == 5) //Atout qui mène
                {
                    if(CarteTester->chiffre > valeurmax)
                    {
                        return 1;
                    }
                    if(CarteTester->chiffre < valeurmax)
                    {
                        if(atout_max > valeurmax)
                        {
                            return 0;
                        }
                        else
                        {
                            return 1;
                        }
                    }
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 1;   //Valide (par défault)
        }
    }
    return 1;
}

int RechercheTypeCarte(Carte *ListeCarteRecherche, int typerecherche)
{
    int presence=0;
    while(ListeCarteRecherche->suivant!=NULL)
    {
        if(ListeCarteRecherche->type==typerecherche){presence=1;}   //presence carte liste
        ListeCarteRecherche=ListeCarteRecherche->suivant;
    }
    return presence;
}

void ComparaisonPuissanceCarte(Pli *InfosPli, int cpt)
{
    if (cpt==0 && InfosPli->CartesPli->chiffre!=22)      //1ère carte du pli et différente de l'excuse
    {
        InfosPli->couleur_meneur=InfosPli->CartesPli->type;     //Initialisation de la structure
        InfosPli->valeur_meneur=InfosPli->CartesPli->chiffre;
        InfosPli->couleur_max=InfosPli->couleur_meneur;
        InfosPli->valeur_max=InfosPli->valeur_meneur;
        InfosPli->joueur_max=InfosPli->tour_joueur;
    }
    else if (cpt!=0 && InfosPli->couleur_max==0)    //1ère carte posée == Excuse
    {
        InfosPli->couleur_meneur=InfosPli->CartesPli->type;     //Initialisation de la structure
        InfosPli->valeur_meneur=InfosPli->CartesPli->chiffre;
        InfosPli->couleur_max=InfosPli->couleur_meneur;
        InfosPli->valeur_max=InfosPli->valeur_meneur;
        InfosPli->joueur_max=InfosPli->tour_joueur;
    }
    else    //Pas la première carte du pli
    {
        if (InfosPli->CartesPli->type!=InfosPli->couleur_max && InfosPli->CartesPli->type==5)  //Couleur qui ne mène pas et carte == atout
        {
            InfosPli->couleur_max=InfosPli->CartesPli->type;    //Remplace le type de carte qui mène
            InfosPli->valeur_max=InfosPli->CartesPli->chiffre;  //Remplace la valeur de la carte qui mène
            InfosPli->joueur_max=InfosPli->tour_joueur;         //Change le numéro de joueur qui mène
        }
        else if(InfosPli->CartesPli->type==InfosPli->couleur_max)   //Carte du type qui mène
        {
            if(InfosPli->CartesPli->chiffre>InfosPli->valeur_max && InfosPli->CartesPli->chiffre!=22)
            {
                InfosPli->valeur_max=InfosPli->CartesPli->chiffre;  //Remplace la valeur de la carte qui mène
                InfosPli->joueur_max=InfosPli->tour_joueur;         //Change le numéro de joueur qui mène
            }
        }
    }
}

int RechercheAtoutMax(Carte *ListeCarte)    //Récupere la valeur max des atouts du joueur
{
    int valeur_max=0;
    while(ListeCarte->suivant!=NULL)
    {
        if( ListeCarte->type == 5 && ListeCarte->chiffre != 22)
        {
            if(valeur_max < ListeCarte->chiffre){valeur_max=ListeCarte->chiffre;}       //Nouvelle valuer max
        }
        ListeCarte=ListeCarte->suivant;
    }
    return valeur_max;
}

void ComptagePoint(Joueur *ListeJoueur, Partie *InfosPartie)
{
    int compteur=0,point_carte;
    int preneur=InfosPartie->preneur;
    int objectif;
    int i=0;
    //Afficher_Liste(ListeJoueur[InfosPartie->preneur].Carte_Main);

    /* Comptage des points du meneur */
    while(ListeJoueur[InfosPartie->preneur].Carte_Main != NULL)
    {
        if(ListeJoueur[InfosPartie->preneur].Carte_Main->type == 5 && ListeJoueur[InfosPartie->preneur].Carte_Main->chiffre != 1 && ListeJoueur[InfosPartie->preneur].Carte_Main->chiffre != 22 && ListeJoueur[InfosPartie->preneur].Carte_Main->chiffre != 21 )
        {
            compteur=compteur+0.5;
        }
        if(ListeJoueur[InfosPartie->preneur].Carte_Main->type == 5 && ListeJoueur[InfosPartie->preneur].Carte_Main->chiffre == 22)
        {
            compteur=compteur+4.5;
            InfosPartie->bout++;
        }
        if(ListeJoueur[InfosPartie->preneur].Carte_Main->type == 5 && ListeJoueur[InfosPartie->preneur].Carte_Main->chiffre == 21)
        {
            compteur=compteur+4.5;
            InfosPartie->bout++;
        }
        if(ListeJoueur[InfosPartie->preneur].Carte_Main->type == 5 && ListeJoueur[InfosPartie->preneur].Carte_Main->chiffre == 1)
        {
            compteur=compteur+4.5;
            InfosPartie->bout++;
        }
        if(ListeJoueur[InfosPartie->preneur].Carte_Main->type != 5 && ListeJoueur[InfosPartie->preneur].Carte_Main->chiffre < 11)
        {
            compteur=compteur+0.5;
        }
        if(ListeJoueur[InfosPartie->preneur].Carte_Main->type != 5 && ListeJoueur[InfosPartie->preneur].Carte_Main->chiffre == 11)
        {
            compteur=compteur+1.5;
        }
        if(ListeJoueur[InfosPartie->preneur].Carte_Main->type != 5 && ListeJoueur[InfosPartie->preneur].Carte_Main->chiffre == 12)
        {
            compteur=compteur+2.5;
        }
        if(ListeJoueur[InfosPartie->preneur].Carte_Main->type != 5 && ListeJoueur[InfosPartie->preneur].Carte_Main->chiffre == 13)
        {
            compteur=compteur+3.5;
        }
        if(ListeJoueur[InfosPartie->preneur].Carte_Main->type != 5 && ListeJoueur[InfosPartie->preneur].Carte_Main->chiffre == 14)
        {
            compteur=compteur+4.5;
        }
        ListeJoueur[InfosPartie->preneur].Carte_Main->suivant = ListeJoueur[InfosPartie->preneur].Carte_Main;   //Carte suivante
    }

    /* Verificaton de l'objectif de points */
    switch(InfosPartie->bout)
    {
    case 0:
        objectif=56;
    case 1:
        objectif=51;
        break;
    case 2:
        objectif=41;
        break;
    case 3:
        objectif=36;
        break;
    default:
        exit(-1);   //Error
    }

    point_carte=compteur-objectif;  //Comparaison à l'objectif

    /* Ajout des points de la mise */
    switch(InfosPartie->mise)
    {
        case 1:
            point_carte=point_carte+10;
            break;
        case 2:
            point_carte=point_carte+20;
            break;
        case 3:
            point_carte=point_carte+40;
            break;
        default:
            exit(-1);       //Error
    }

    /* Ajout ou retrait des points aux joueurs */
    for(i=0;i<5;i++)
    {
        if(i == preneur)    //Preneur
        {
            if(compteur < objectif){(ListeJoueur+preneur)->points=(-point_carte)*3;}
            else{(ListeJoueur+preneur)->points=(point_carte*3);}
        }
        else               //Autres joueurs
        {
            if(compteur > objectif){(ListeJoueur+i)->points=(-point_carte);}
            else{(ListeJoueur+i)->points=point_carte;}
        }
        /* Affichage points */
    }
}

int SelectionCarte(Joueur *TabJoueur, SDL_Rect depart, int numero, int ecart)
{
    SDL_Event event;
    SDL_Rect posclic, memoirepos;
    Carte *DebutListe;
    int continuer=1, compteur;

    memoirepos=depart;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_RIGHT)
            {
                compteur=0;
                depart=memoirepos;
                DebutListe=(TabJoueur+numero)->Carte_Main;  //Recuperation liste de carte
                posclic.x = event.button.x;
                posclic.y = event.button.y;
                while(DebutListe!=NULL)     //Parcours la liste
                {
                    if( posclic.x > depart.x  && posclic.x <= (depart.x+depart.w))  //Clic sur une carte de la liste ?
                    {
                        if(posclic.y > depart.y && posclic.y <= (depart.y+depart.h))
                        {
                            return compteur+1;
                        }
                    }
                    if(numero == 0 || numero == 2){depart.x=depart.x+ecart;}
                    else{depart.y=depart.y+ecart;}
                    DebutListe=DebutListe->suivant;
                    compteur++;
                }
            }
            break;
        }
    }
}

void CommencerJouer(SDL_Surface *ecran, int posx, int posy)
{
    /* Initialisation de la gestion d'évènement */
    SDL_Event event;
    SDL_Surface *Bouton_suivant=NULL;
    SDL_Rect pos_bouton, postxt, posclic;
    InitialisationPosition(&pos_bouton, posx, posy, 120, 60);
    InitialisationPosition(&postxt, posx+26, posy+13, 0, 0);
    int continuer=1;

    /* Affichage */
    Bouton_suivant = SDL_CreateRGBSurface(SDL_HWSURFACE, 120, 50, 32, 0, 0, 0, 0);
    SDL_FillRect(Bouton_suivant, NULL, SDL_MapRGB(ecran->format, 170, 170, 170));
    SDL_BlitSurface(Bouton_suivant, NULL, ecran, &pos_bouton);
    AfficheTexte(ecran, &postxt, 22, "START");
    SDL_Flip(ecran);

    /* Attente clic */
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_MOUSEBUTTONUP:
                posclic.x = event.button.x;
                posclic.y = event.button.y;
                break;
        }
        /* Clic sur le bouton ? */
        if(posclic.x >= pos_bouton.x && posclic.x <= (pos_bouton.x+pos_bouton.w))
        {
            if(posclic.y >= pos_bouton.y && posclic.y <= (pos_bouton.y+pos_bouton.w))
            {
                SDL_FillRect(ecran, &pos_bouton, SDL_MapRGB(ecran->format, 42, 65, 47));    //Efface le bouton
                SDL_FreeSurface(Bouton_suivant);
                SDL_Flip(ecran);
                continuer=0;
            }
        }
    }
}

int ContinuerJouer(SDL_Surface *ecran)
{
    /* Initialisation de la gestion d'évènement */
    SDL_Event event;
    SDL_Surface *Bouton_suivant=NULL;
    SDL_Surface *BoutonQuitter=NULL;
    SDL_Rect pos_bouton, posquitter, postxt, postxtquit, posclic;
    InitialisationPosition(&pos_bouton, 465, 275, 120, 60);
    InitialisationPosition(&posquitter, 465, 775, 120, 60);
    InitialisationPosition(&postxt, 465+26, 275+13, 0, 0);
    InitialisationPosition(&postxtquit, 465+26, 775+13, 0, 0);
    int continuer=1;

    /* Affichage */
    Bouton_suivant = SDL_CreateRGBSurface(SDL_HWSURFACE, 120, 50, 32, 0, 0, 0, 0);
    SDL_FillRect(Bouton_suivant, NULL, SDL_MapRGB(ecran->format, 170, 170, 170));
    SDL_BlitSurface(Bouton_suivant, NULL, ecran, &pos_bouton);
    AfficheTexte(ecran, &postxt, 22, "REJOUER");
    BoutonQuitter = SDL_CreateRGBSurface(SDL_HWSURFACE, 120, 50, 32, 0, 0, 0, 0);
    SDL_FillRect(BoutonQuitter, NULL, SDL_MapRGB(ecran->format, 170, 170, 170));
    SDL_BlitSurface(BoutonQuitter, NULL, ecran, &posquitter);
    AfficheTexte(ecran, &postxtquit, 22, "QUITTER");
    SDL_Flip(ecran);

    /* Attente clic */
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_MOUSEBUTTONUP:
                posclic.x = event.button.x;
                posclic.y = event.button.y;
                break;
        }
        /* Clic sur le bouton ? */
        if(posclic.x >= pos_bouton.x && posclic.x <= (pos_bouton.x+pos_bouton.w))
        {
            if(posclic.y >= pos_bouton.y && posclic.y <= (pos_bouton.y+pos_bouton.w))
            {
                SDL_FillRect(ecran, &pos_bouton, SDL_MapRGB(ecran->format, 42, 65, 47));    //Efface le bouton
                SDL_FreeSurface(Bouton_suivant);
                SDL_FillRect(ecran, &posquitter, SDL_MapRGB(ecran->format, 42, 65, 47));    //Efface le bouton
                SDL_FreeSurface(BoutonQuitter);
                SDL_Flip(ecran);
                return 1;
            }
        }
        if(posclic.x >= posquitter.x && posclic.x <= (posquitter.x+posquitter.w))
        {
            if(posclic.y >= posquitter.y && posclic.y <= (posquitter.y+posquitter.w))
            {
                SDL_FillRect(ecran, &posquitter, SDL_MapRGB(ecran->format, 42, 65, 47));    //Efface le bouton
                SDL_FreeSurface(Bouton_suivant);
                SDL_FillRect(ecran, &posquitter, SDL_MapRGB(ecran->format, 42, 65, 47));    //Efface le bouton
                SDL_FreeSurface(BoutonQuitter);
                SDL_Flip(ecran);
                return 0;
            }
        }
    }
}
