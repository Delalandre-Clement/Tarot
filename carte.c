/* **********************************************************
Clément Delalandre - LP AII Nice
Projet : Tarot - LP AII

Fonctions liées aux cartes
************************************************************/
#include "carte.h"

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_MOUSEBUTTONUP:
                continuer = 0;
        }
    }
}

Carte *Generation_Cartes(void)
{
    int type_carte=5;
    int chiffre_carte =22;
    Carte *paquet = malloc(sizeof(Carte)); //Tête de la liste
    if(paquet!=NULL)
    {
        paquet->type=type_carte;        //Génere la première carte
        paquet->chiffre=chiffre_carte;
        paquet->recto = IMG_Load("Images/5-22.png");
        if(paquet->recto == NULL){exit(-1);}
        paquet->verso = IMG_Load("Images/verso.png");
        if(paquet->verso == NULL){exit(-1);}
        paquet->rectoy = IMG_Load("Images/5-22r.png");
        if(paquet->rectoy == NULL){exit(-1);}
        paquet->versoy = IMG_Load("Images/versor.png");
        if(paquet->versoy == NULL){exit(-1);}
        paquet->position.h=75;
        paquet->position.w=45;
        paquet->suivant=NULL;
        chiffre_carte--;

    }
    else exit(-1);



    //Création suite des cartes
    //Type := 1=Coeur 2=Trèfle 3=Pique 4=Carreau 5=Atout
    for(type_carte=5;type_carte>0;type_carte--)
    {
        if(type_carte==5)   //Atout ?
        {
            for(chiffre_carte=21;chiffre_carte>0;chiffre_carte--)
            {
                paquet=AjoutCarte(paquet,type_carte,chiffre_carte);     //Génère les atouts
            }
        }
        else
        {
            for(chiffre_carte=14;chiffre_carte>0;chiffre_carte--)
            {
                paquet=AjoutCarte(paquet,type_carte,chiffre_carte);     //Génère les autres carte (Trèfle, Coeur, Carreau, Pique)
            }
        }
    }
    return paquet;
}

Carte *AjoutCarte(Carte *carte_precedente,int type,int chiffre)     //Ajoute une carte à la liste chainée envoyée
{
    Carte *nouvelle_carte;
    nouvelle_carte=malloc(sizeof(Carte));
    char IDcarte[50] = "";
    NumeroCarte(IDcarte, type, chiffre);
    char IDcarter[50] = "";
    NumeroCarter(IDcarter, type, chiffre);

    if(nouvelle_carte!=NULL)
    {
        nouvelle_carte->type=type;    //Ajoute le type de carte
        nouvelle_carte->chiffre=chiffre;    //Ajoute le numero de carte
        nouvelle_carte->recto = IMG_Load(IDcarte);
        if(nouvelle_carte->recto == NULL){exit(-1);}
        nouvelle_carte->verso = IMG_Load("Images/verso.png");
        if(nouvelle_carte->verso == NULL){exit(-1);}
        nouvelle_carte->rectoy = IMG_Load(IDcarter);
        if(nouvelle_carte->rectoy == NULL){exit(-1);}
        nouvelle_carte->versoy = IMG_Load("Images/versor.png");
        if(nouvelle_carte->versoy == NULL){exit(-1);}
        nouvelle_carte->position.h=75;
        nouvelle_carte->position.w=45;
        nouvelle_carte->suivant=carte_precedente;
        carte_precedente=nouvelle_carte;
    }
    else exit(-1);
    return carte_precedente;
}

Carte *RegrouperCarte(Carte *Chien, Joueur *TableauJoueur, Carte *TasCarte)   //Recupere les cartes des joueurs + chien et les remet dans le tas
{
    int i=0;
    Carte *DerniereCarte;

    if((TableauJoueur+0)->Carte_Main!=NULL)
    {
        TasCarte=(TableauJoueur+0)->Carte_Main;   //Cartes du 1er joueur dans le paquet
        (TableauJoueur+0)->Carte_Main=NULL;

        for(i=0;i<3;i++)        //Cartes des autres joueurs dans le pacquet
        {
            DerniereCarte=ChercheDernierElement((TableauJoueur+i+1)->Carte_Main); //Recupere derniere carte de la liste
            DerniereCarte->suivant=TasCarte;
            TasCarte=(TableauJoueur+i+1)->Carte_Main;
            (TableauJoueur+i+1)->Carte_Main=NULL;
        }

        if(Chien->suivant!=NULL)
        {
            DerniereCarte=ChercheDernierElement(Chien); //Cartes du chien dans le pacquet
            DerniereCarte->suivant=TasCarte;
            TasCarte=Chien;
        }
    }
    else
    {
        TasCarte=(TableauJoueur+0)->PliGagne;   //Cartes du 1er joueur dans le paquet
        (TableauJoueur+0)->PliGagne=NULL;

        for(i=0;i<3;i++)        //Cartes des autres joueurs dans le pacquet
        {
            DerniereCarte=ChercheDernierElement((TableauJoueur+i+1)->PliGagne); //Recupere derniere carte de la liste
            DerniereCarte->suivant=TasCarte;
            TasCarte=(TableauJoueur+i+1)->PliGagne;
            (TableauJoueur+i+1)->PliGagne=NULL;
        }
    }
    return TasCarte;    //Retourne adresse du debut du tas
}

Carte *Melange_Cartes(Carte *Tas)
{
    Carte *ParcoursCarte;
    Carte *CartePrecedente;
    Carte *CarteExtraite;
    Carte *TasMelange;
    int nombre_carte=78;   //Nombre de carte dans le tas
    int nbr_aleatoire;
    srand(time(NULL)); // initialisation de rand

    for(nombre_carte=78;nombre_carte>0;nombre_carte--)    //Boucle pour mélanger toutes les cartes
    {
        nbr_aleatoire=rand()%nombre_carte+1;
        ParcoursCarte=Tas;      //Pour parcourir le tas à partir du début de la liste
        if(nbr_aleatoire==1)    //1er élément de la liste
        {
            Tas=Tas->suivant;
            ParcoursCarte->suivant=NULL;
            CarteExtraite=ParcoursCarte;

        }
        else if(nbr_aleatoire==nombre_carte)    //Dernier élément de la liste
        {
            while(ParcoursCarte->suivant!=NULL) //On va au dernier element de la liste
            {
                CartePrecedente=ParcoursCarte;
                ParcoursCarte=ParcoursCarte->suivant;
            }
            CartePrecedente->suivant=NULL;  //Avant dernier élément devient le dernier
            CarteExtraite=ParcoursCarte;    //L'ancien dernier élément est l'élément retiré de la liste
        }
        else    //Element du centre de la liste (!= 1er && !=dernier)
        {
            do
            {
                nbr_aleatoire--;
                ParcoursCarte=ParcoursCarte->suivant;
            }
            while(nbr_aleatoire>2);     //Boucle pour selectionner la carte portant le numero du nombre aleatoire -1

            CartePrecedente=ParcoursCarte;  //Enregistre la carte précédent la carte à retirer (pour ponter la liste)
            ParcoursCarte=ParcoursCarte->suivant;       //Passage a l'élément portant le numero du nombre aléatoire
            CarteExtraite=ExtraireElement(CartePrecedente,ParcoursCarte);   //Appel fonction permettant d'extraire l'élément
        }

        if(nombre_carte==78)    //Première carte mélangée
        {
            TasMelange=CarteExtraite;
            TasMelange->suivant=NULL;
        }
        else    //Eléments suivants
        {
            CarteExtraite->suivant=TasMelange;
            TasMelange=CarteExtraite;
        }
    }

    Tas=Detruire_Liste(Tas);
    return TasMelange;
}

Carte *TriCarte(Carte *ListeTrier)
{
    int nbrcarte=0, cpt1, poscarte, valeurmax, typemax, compteurpos;
    Carte *ParcoursCarte;
    Carte *CarteExtraite;
    Carte *NouvelleListe;

    ParcoursCarte=ListeTrier;
    while(ParcoursCarte != NULL)
    {
        ParcoursCarte=ParcoursCarte->suivant;
        nbrcarte++;
    }

    for(cpt1=0;cpt1<nbrcarte;cpt1++)
    {
        ParcoursCarte=ListeTrier;
        valeurmax=1;
        typemax=1;
        compteurpos=0;
        poscarte=0;
        while(ParcoursCarte!=NULL)
        {
            if(ParcoursCarte->type > typemax)
            {
                typemax=ParcoursCarte->type;
                valeurmax=ParcoursCarte->chiffre;
                poscarte=compteurpos;
            }
            if(ParcoursCarte->type == typemax)
            {
                if(ParcoursCarte->chiffre > valeurmax)
                {
                    valeurmax=ParcoursCarte->chiffre; //Nouvelle valuer max
                    poscarte=compteurpos;
                }
            }
            ParcoursCarte=ParcoursCarte->suivant;
            compteurpos++;
        }

        if(poscarte==0)    //1ère carte de la liste
        {
            CarteExtraite=ListeTrier;
            ListeTrier=ListeTrier->suivant;          //Second Element deviens premier
        }
        else{ CarteExtraite=ExtractionCarte(ListeTrier, poscarte+1);}   //Extraire carte de la main du joueur

        if(cpt1==0)
        {
            /* Premier Element extrait = Denrier element de la nouvelle chaine*/
            CarteExtraite->suivant=NULL;
            NouvelleListe=CarteExtraite;
        }
        else
        {
            /* Ajout de l'element */
            CarteExtraite->suivant=NouvelleListe;
            NouvelleListe=CarteExtraite;
        }
    }
    return NouvelleListe;
}


Carte *DistributionCarte(Carte *Pioche,Joueur *ListeJ)        //Distribue les cartes aux joueurs - Retourne le Chien
{
    int cpt,num_joueur,cpt_global=0;
    Carte *CarteSuivante;   //Sauvegarde la carte suivante
    Carte *Chien;
    int premiere_carte_chien=1; //TRUE
    while(Pioche!=NULL) //Distribue tans qu'il y a des cartes dans le tas
    {
        for(num_joueur=0;num_joueur<4;num_joueur++) //Fait le tour des joueur
        {
            for(cpt=0;cpt<3;cpt++)  //Distribue 3 cartes
            {
                CarteSuivante=Pioche->suivant;                  //Recupere l'adresse de la seconde carte du tas
                Pioche->suivant=ListeJ[num_joueur].Carte_Main;
                ListeJ[num_joueur].Carte_Main=Pioche;
                Pioche=CarteSuivante;
                cpt_global++;
            }
            if(num_joueur==1)   //Carte au chien
            {
                CarteSuivante=Pioche->suivant;
                if(premiere_carte_chien==1) //TRUE ?
                {
                    Pioche->suivant=NULL;
                    Chien=Pioche;
                    premiere_carte_chien=0; //Passe la variable a FALSE
                }
                else    //FALSE
                {
                    Pioche->suivant=Chien;
                    Chien=Pioche;
                }
                Pioche=CarteSuivante;
                cpt_global++;
            }
        }
    }
    return Chien;   //Retourne le chien
}

void EchangeChien(Joueur *ListeJoueur, Carte *Chien, int preneur, SDL_Surface *screen)
{
    Carte *DerniereCarteChien=ChercheDernierElement(Chien); //Recupere adrese derniere carte du chien
    int numero,cpt;     //Numero de la carte à mettre au chien et compteru de carte mise au chien

    SDL_Rect centre;
    InitialisationPosition(&centre, 390, 700, 80, 300);

    Afficher_ListeX(Chien, centre, screen, 50);
    CommencerJouer(screen, 465, 790);

    DerniereCarteChien->suivant=(ListeJoueur+preneur)->Carte_Main;      //Ajoute le chien à la main du joueur
    (ListeJoueur+preneur)->Carte_Main=Chien;
    SDL_FillRect(screen, &centre, SDL_MapRGB(screen->format, 42, 65, 47)); //Retire image du chien

    InitialisationPosition(&centre, 0, 0, 80, 700);
    ListeJoueur[preneur].Carte_Main=TriCarte(ListeJoueur[preneur].Carte_Main);  //Tri des cartes

    switch(preneur)
    {
    case 0:
        InitialisationPosition(&centre, 120, 965, 80, 900);
        SDL_FillRect(screen, &centre, SDL_MapRGB(screen->format, 42, 65, 47)); //Retire image du tas de carte
        InitialisationPosition(&centre, 10, 965, 80, 40);
        Afficher_ListeX(ListeJoueur[preneur].Carte_Main, centre, screen,43);
        break;
    case 1:
        InitialisationPosition(&centre, 10, 10, 1040, 80);
        SDL_FillRect(screen, &(ListeJoueur[preneur].position), SDL_MapRGB(screen->format, 42, 65, 47)); //Retire image du tas de carte
        InitialisationPosition(&centre, 10, 10, 40, 80);
        Afficher_ListeY(ListeJoueur[preneur].Carte_Main, centre, screen, 43);
        break;
    case 2:
        InitialisationPosition(&centre, 120, 10, 80, 900);
        SDL_FillRect(screen, &(ListeJoueur[preneur].position), SDL_MapRGB(screen->format, 42, 65, 47)); //Retire image du tas de carte
        InitialisationPosition(&centre, 10, 10, 80, 40);
        Afficher_ListeX(ListeJoueur[preneur].Carte_Main, centre, screen, 43);
        break;
    case 3:
        InitialisationPosition(&centre, 965, 120, 900, 75);
        SDL_FillRect(screen, &(ListeJoueur[preneur].position), SDL_MapRGB(screen->format, 42, 65, 47)); //Retire image du tas de carte
        InitialisationPosition(&centre, 965, 10, 40, 75);
        Afficher_ListeY(ListeJoueur[preneur].Carte_Main,centre, screen, 43);
        break;
    default:
        exit(-1);
        break;
    }
    SDL_Flip(screen);

    for(cpt=0;cpt!=6;cpt++)
    {
        numero = SelectionCarte(ListeJoueur, centre, preneur, 43);
        SDL_FillRect(screen, &ListeJoueur[preneur].effacecarte, SDL_MapRGB(screen->format, 42, 65, 47)); //Retire image du tas de carte
        MiseAuChien(ListeJoueur,preneur,numero);  //Retire la carte de la main du joueur et la place dans ses cartes de pli gagnées
        if(preneur == 0 || preneur == 2)
            Afficher_ListeX(ListeJoueur[preneur].Carte_Main, centre, screen, 43);
        else
            Afficher_ListeY(ListeJoueur[preneur].Carte_Main, centre, screen, 43);
    }
    ListeJoueur[preneur].Carte_Main=TriCarte(ListeJoueur[preneur].Carte_Main);  //Tri des cartes du meneur
    ClearCartes(screen);
    AfficheJeu(screen, ListeJoueur);
}

Carte *ExtractionCarte(Carte *ListeRecherche, int position)
{
    Carte *CarteExtraite;
    Carte *Memoire=NULL;
    while(position!=1)
    {
        Memoire=ListeRecherche;
        ListeRecherche=ListeRecherche->suivant;
        position--;
    }
    CarteExtraite=ListeRecherche;               //Recupère l'adresse de l'élément
    Memoire->suivant=ListeRecherche->suivant;   //Jonction de la liste
    CarteExtraite->suivant=NULL;                //Retire l'element de la liste
    return CarteExtraite;
}

void MiseAuChien(Joueur *ListeJoueur, int preneur, int num_carte)
{
    Carte *CarteRetirer;
    if(num_carte!=1)
    {
        CarteRetirer=ExtractionCarte(ListeJoueur[preneur].Carte_Main,num_carte); //Extraction de la carte que le joueur a choisie
    }
    else
    {
        CarteRetirer=(ListeJoueur+preneur)->Carte_Main;
        (ListeJoueur+preneur)->Carte_Main=(ListeJoueur+preneur)->Carte_Main->suivant;     //Nouvelle première carte
    }
    CarteRetirer->suivant=(ListeJoueur+preneur)->PliGagne;
    (ListeJoueur+preneur)->PliGagne=CarteRetirer;
}

Carte *ViderPli(Pli *PliActuel, Joueur *ListeJoueur, int gagnant)
{
    Carte *DerniereCarte=ChercheDernierElement(PliActuel->CartesPli);   //Recupere adresse de la dernière carte
    if(DerniereCarte!=NULL)
    {
        DerniereCarte->suivant=ListeJoueur[gagnant].PliGagne;   //Ajoute les cartes du pli au tas du joueur
        ListeJoueur[gagnant].PliGagne=PliActuel->CartesPli;  //Nouvelle premiere carte (tas de pli gagne par le joueur)
        PliActuel->CartesPli=NULL;      //Vide la liste de carte du pli
        return  ListeJoueur[gagnant].PliGagne;
    }
    else {exit(-1);}
}

Carte *RecuperationInfosCarte(Carte *Liste_Carte, int position)
{
    Carte *CarteExtraire=Liste_Carte;
    while(position!=0)
    {
        CarteExtraire=CarteExtraire->suivant;
        position--;
    }
    return CarteExtraire;
}

void ClearCartes(SDL_Surface *screen)   //Efface toutes les cartes
{
    SDL_Rect sclear;
    InitialisationPosition(&sclear, 0, 0, 90, 1050);
    SDL_FillRect(screen, &sclear, SDL_MapRGB(screen->format, 42, 65, 47));

    sclear.y=965;
    SDL_FillRect(screen, &sclear, SDL_MapRGB(screen->format, 42, 65, 47));

    InitialisationPosition(&sclear, 0, 5, 1050, 90);
    SDL_FillRect(screen, &sclear, SDL_MapRGB(screen->format, 42, 65, 47));

    sclear.x=965;
    SDL_FillRect(screen, &sclear, SDL_MapRGB(screen->format, 42, 65, 47));
}
