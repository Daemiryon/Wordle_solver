#ifndef TREE_H
#define TREE_H

#include "occurence_table.h"
#include "dictionnary.h"

struct _abr
{
    int profondeur;
    struct _abr *branche[26];
};

typedef struct _abr abr;

abr *creat_abr(int profondeur);

abr *init_A();

void print_A(abr *A, char *buffer); 

void add(abr *A, char *mot);

void destroy_A(abr *A);

int nb_match(abr *A, occ_table T, char *mot, char *coul, compteur c);

int elague(abr *A, occ_table T, char *mot, char *color, compteur c);
int MAJ_A(abr *A, occ_table T, char *mot, char *coul); 

int verify(abr* A, char* word);

#endif
