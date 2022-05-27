#include "tree.h"

#ifndef DICTIONNARY_H
#define DICTIONNARY_H

typedef struct cell
{
    char *word;
    struct cell *next;
    struct cell *previous;
    int index;
    float freq;
} cell;

typedef struct dico
{
    int first;
    int taille; // taille statique (non dynamique)
    cell **content;
} dico;

extern dico *init_dico();
extern void destroy_dico(dico *one_dico);
extern void print_dico(dico *one_dico);   // déplacement par index
extern void print_dico_p(dico *one_dico); // déplacement par pointeur
extern void maj_dico(dico *one_dico);
extern void suppr_dico(dico *one_dico, int i);
extern char *pop(dico *one_dico, int i);

#endif
