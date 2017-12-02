#include "liste_chainee.h"

Carte *Detruire_Liste (Carte *m)        //Fonction de libération de la mémoire
{
    Carte *o;
    int i = 0;
    while(m!=NULL)
    {
        i++;
        o=m->suivant;       //Recupération de l'adresse de l'élément suivant
        if (m != NULL)
        {
            free(m);        //Libération du pointeur
        }
        m=NULL;         //Adresse mise à NULL
        m=o;        //Passage à l'élément suivant
    }
    return(m);  //Retourne NULL dans le main
}

Carte *ExtraireElement (Carte *ElementPrecedent,Carte *ElementExtraire) //Extrait un element d'une liste chainée
{
    ElementPrecedent->suivant=ElementExtraire->suivant;
    ElementExtraire->suivant=NULL;

    return ElementExtraire;
}

Carte *ChercheDernierElement(Carte *ListeCarte) //Recupere le dernier element d'une liste chainée
{
    while(ListeCarte->suivant!=NULL)
    {
        ListeCarte=ListeCarte->suivant;
    }
    return ListeCarte;
}
