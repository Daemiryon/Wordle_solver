#include "occurence_table.h"

#ifndef DICTIONNARY_H
#define DICTIONNARY_H

typedef struct cell{
    char* word;
    struct cell* next;
    struct cell* previous;
    int index;
} cell;

//Question pour moi : comment gérer le fonctionnement de liste contigue ???

extern cell* init_dico(int n); 
extern void dico_add(cell* dico, char* word); //Fonction auxiliaire, ajoute un mot dans le dico
extern void print_dico(cell* dico);
extern void destroy_dico(cell* dico);
extern void maj_dico(occ_table t); 
extern void suppr_dico(cell* dico,int one_index);
extern char* pop(cell* dico,int one_index); 

#endif
