/* **********************************************************
Clément Delalandre - LP AII Nice
Projet : Tarot - LP AII

Gestion de Fichiers
************************************************************/
#include "fichier.h"

void NouveauProfil()
{
    //Variables locales
    char nom_fichier[20];
    char chemin_acces[25]="Profils\\";
    char *presence_extension;
    char *lettres=calloc(3,sizeof(char));      //Allocation dynamique du tableau qui contiendra les valeurs à ecrire
    int ecriture=0;

    fflush(stdin);  //Vide le tempon d'entrée

    do
    {
        printf("Veuillez choisir votre pseudo (10 car. max.) :");
        gets(nom_fichier);
    }
    while(strlen(nom_fichier)>10);  //Verification nombre caractères saisis
    strcat(chemin_acces,nom_fichier);   //Ajoute le dossier répertoire au nom de fichier
    presence_extension=strstr(chemin_acces,".txt");  //Verifie si l'extension .txt est présente dans le nom de fichier
    if(presence_extension==NULL)
    {
        strcat(chemin_acces,".txt"); //Ajoute l'extension .txt si elle n'est pas saisie par l'utilisateur
    }
    fichier=fopen(chemin_acces,"w");
    if(fichier==NULL)       //Verifie si l'ouverture du fichier est réussie
    {
        printf("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    ecriture=fputs("0",fichier);    //Ecriture dans le fichier
    if(ecriture<0)      //Verification si l'ecriture s'est bien effectuée
    {
        printf("ERREUR ECRITURE");
        exit(EXIT_FAILURE);
    }
    free(lettres);  //Liberation Mémoire
}

void ChargerProfil()
{
    DIR* rep = NULL;
    long pos=2;
    int longueur=0,cpt=0;
    struct dirent* fichierLu = NULL; // Déclaration d'un pointeur vers la structure
    rep = opendir("Profils\\"); /* Ouverture d'un dossier */

    if (rep == NULL) /* Si le dossier n'a pas pu être ouvert */
        exit(1); /* (mauvais chemin par exemple) */

    seekdir(rep,pos);   //Place le curseur virtuel en position 2 (Evite le '.' et '..')
    printf("Profils existants :");

    while ((fichierLu = readdir(rep)) != NULL)
    {
        longueur=strlen(fichierLu->d_name)-5;
        printf("\n- ");
        cpt=0;
        while(cpt<=longueur)
        {
            printf("%c",fichierLu->d_name[cpt]);
            cpt++;
        }
    }

    if (closedir(rep) == -1) /* S'il y a eu un souci avec la fermeture */
        exit(-1);
}

void NumeroCarte(char *Tableau, int type, int chiffre)
{
    /* Chemin accès image carte*/
    fichier = fopen("Images/NumeroCarte.txt", "w+");  //Ouverture en écriture
    if (fichier == NULL){exit(-1);} //Erreur Fichier
    fprintf(fichier, "Images/%d-%d.png", type,chiffre); //Ecriture du nom de l'image à charger
    fclose(fichier);    //Fermeture fichier

    fichier = fopen("Images/NumeroCarte.txt", "r");  //Ouverture en lecture
    if(chiffre>=10){fgets(Tableau, 17, fichier);}
    else{fgets(Tableau, 15, fichier);}
    fclose(fichier);    //Fermeture fichier
}

void NumeroCarter(char *Tableau, int type, int chiffre)
{
    /* Chemin accès image carte*/
    fichier = fopen("Images/NumeroCarter.txt", "w+");  //Ouverture en écriture
    if (fichier == NULL){exit(-1);} //Erreur Fichier
    fprintf(fichier, "Images/%d-%dr.png", type,chiffre); //Ecriture du nom de l'image à charger
    fclose(fichier);    //Fermeture fichier

    fichier = fopen("Images/NumeroCarter.txt", "r");  //Ouverture en lecture
    if(chiffre>=10){fgets(Tableau, 18, fichier);}
    else{fgets(Tableau, 17, fichier);}
    fclose(fichier);    //Fermeture fichier
}
