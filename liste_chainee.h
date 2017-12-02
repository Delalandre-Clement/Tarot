#ifndef LISTE_CHAINEE_H_INCLUDED
#define LISTE_CHAINEE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "carte.h"


/* Prototypes des fonctions */
Carte *Detruire_Liste (Carte *);
Carte *ExtraireElement (Carte *,Carte  *);
Carte *ChercheDernierElement(Carte *);
void pause(void);

#endif // LISTE_CHAINEE_H_INCLUDED
