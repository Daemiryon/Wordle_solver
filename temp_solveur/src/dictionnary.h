#include "occurence_table.h"

#ifndef DICTIONNARY_H
#define DICTIONNARY_H

typedef struct cell{
    char* word;
    struct cell* next;
    struct cell* previous;
    int index;
    float freq;
} cell;

typedef struct dico{
    int first;
    int taille;
    cell** content;
} dico;

extern dico* init_dico(int n); 
extern void destroy_dico(dico* one_dico);
extern void print_dico(dico* one_dico); //déplacement par index
extern void print_dico_p(dico* one_dico); //déplacement par pointeur

#endif
