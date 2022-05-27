#include "occurence_table.h"
#include <stdio.h>
#include <stdlib.h>

int nb_letters;

int main()
{
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
        "EFFET",
        "EFRIT",
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
        "10000",
        "10020",
    };

    nb_letters = 5;
    occ_table T;
    init_T(T);
    char target[5] = "DEVIN";
    for (int i = 0; i < 14; i++)
    {
        printf("%s : \n", mots[i]);
        maj_T(T, mots[i], couleur[i]);
        print_T(T);
    }

    return 0;
}
