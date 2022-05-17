#ifndef OCCURENCE_TABLE_H
#define OCCURENCE_TABLE_H
#include <stdbool.h>

typedef int occ_table[26][2];
typedef int compteur[26];

void init_T(occ_table buffer);

void maj_T(occ_table T, char *mot, char *rep);

void copy_T(occ_table T, occ_table buffer);

void compute_occ(occ_table T, char *mot, char *rep, int index);

void print_T(occ_table T);

void init_C(compteur c);

int compteur_valide(occ_table T, compteur c);

bool filtre_D(occ_table T,char *mot);

#endif
