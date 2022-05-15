#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char mots[52][6] = {
    "DUNES",
    "DUODI",
    "DUPEE",
    "DUPER",
    "DUPES",
    "DUPEZ",
    "DURAT",
    "DURCI",
    "DUREE",
    "DURER",
    "DURES",
    "DURIT",
    "DUSSE",
    "DUVET",
    "DYKES",
    "DYNES",
    "EBAHI",
    "EBATS",
    "EBENE",
    "EBOUE",
    "ECALE",
    "ECART",
    "ECHEC",
    "ECHER",
    "ECHOS",
    "ECHUE",
    "ECHUT",
    "ECLAT",
    "ECLOS",
    "ECOLE",
    "ECOLO",
    "ECOPA",
    "ECOPE",
    "ECRAN",
    "ECRIA",
    "ECRIE",
    "ECRIN",
    "ECRIS",
    "ECRIT",
    "ECROU",
    "ECRUE",
    "ECSTA",
    "ECULE",
    "ECUMA",
    "ECUME",
    "EDENS",
    "EDITE",
    "EDITO",
    "EDITS",
    "EDUEN",
    "DEVON",
    "DEVIN",
};
char couleur[52][6] = {
    "20110",
    "20001",
    "20010",
    "20010",
    "20010",
    "20010",
    "20000",
    "20001",
    "20010",
    "20010",
    "20010",
    "20020",
    "20001",
    "20210",
    "20010",
    "20110",
    "10001",
    "10000",
    "10010",
    "10000",
    "10000",
    "10000",
    "10000",
    "10000",
    "10000",
    "10000",
    "10000",
    "10000",
    "10000",
    "10000",
    "10000",
    "10000",
    "10000",
    "10002",
    "10020",
    "10020",
    "10022",
    "10020",
    "10020",
    "10000",
    "10000",
    "10000",
    "10000",
    "10000",
    "10000",
    "11010",
    "11100",
    "11100",
    "11100",
    "11002",
    "22202",
    "22222",
};

int nb_letters;

int main()
{

    nb_letters = 5;
    abr *A = creat_abr(0);

    for (int i = 0; i < 52; i++)
    {
        add(A, mots[i]);
    }
    occ_table T;
    // init_T(T);
    // compute_occ(T, mots[11], couleur[11], 0);
    // print_T(T);
    // compteur c;
    // init_C(c);
    // printf("%d \n", nb_match(A, T, mots[11], couleur[11], c));
    // printf("%d\n", A->branche['D' - 'A']->branche['U' - 'A']->branche['R' - 'A']->branche['I' - 'A']->branche['T' - 'A']->profondeur);

    for (int i = 0; i < 52; i++)
    {
        init_T(T);
        compute_occ(T, mots[i], couleur[i], 0);
        // print_T(T);

        printf("%s : \n", mots[i]);
        compteur c;
        init_C(c);
        printf("%d \n", nb_match(A, T, mots[i], couleur[i], c));
    }

    destroy_A(A);
    return 0;
}
