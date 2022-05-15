#ifndef TREE_H
#define TREE_H

#include "occurence_table.h"

struct _abr
{
    int profondeur;
    struct _abr *branche[26];
};

typedef struct _abr abr;

abr *creat_abr(int profondeur);

abr *init_A();

void print_A(abr *A);

void add(abr *A, char *mot);

void destroy_A(abr *A);

int nb_match(abr *A, occ_table T, char *mot, char *coul, compteur c);

void MAJ(abr *A, occ_table T, char *mot, char *coul, compteur c);

#endif
