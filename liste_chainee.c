#include "liste_chainee.h"

Carte *Detruire_Liste (Carte *m)        //Fonction de lib�ration de la m�moire
{
    Carte *o;
    int i = 0;
    while(m!=NULL)
    {
        i++;
        o=m->suivant;       //Recup�ration de l'adresse de l'�l�ment suivant
        if (m != NULL)
        {
            free(m);        //Lib�ration du pointeur
        }
        m=NULL;         //Adresse mise � NULL
        m=o;        //Passage � l'�l�ment suivant
    }
    return(m);  //Retourne NULL dans le main
}

Carte *ExtraireElement (Carte *ElementPrecedent,Carte *ElementExtraire) //Extrait un element d'une liste chain�e
{
    ElementPrecedent->suivant=ElementExtraire->suivant;
    ElementExtraire->suivant=NULL;

    return ElementExtraire;
}

Carte *ChercheDernierElement(Carte *ListeCarte) //Recupere le dernier element d'une liste chain�e
{
    while(ListeCarte->suivant!=NULL)
    {
        ListeCarte=ListeCarte->suivant;
    }
    return ListeCarte;
}
