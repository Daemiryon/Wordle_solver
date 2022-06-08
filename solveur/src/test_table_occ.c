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
    // char target[5] = "DEVIN";
    for (int i = 0; i < 14; i++)
    {
        printf("%s : \n", mots[i]);
        maj_T(T, mots[i], couleur[i]);
        print_T(T);
    }
    printf("Convergence vers DEVIN -> OK\n-----------------------------\n");

    init_T(T);
    maj_T(T, "ABCDE", "00000");
    printf("mot : ABCDE, couleur : 00000 \nOccurence à 0 pour A,B,C et D :\n");
    print_T(T);

    init_T(T);
    maj_T(T, "ABCDE", "22222");
    printf("mot : ABCDE, couleur : 22222 \nOccurence à 1 pour A,B,C et D et à 0 pour tout les autres:\n");
    print_T(T);

    init_T(T);
    maj_T(T, "AAABB", "10200");
    printf("mot : AAABB, couleur : 10200 \nOccurence à 2 pour A et à 0 pour B:\n");
    print_T(T);

    init_T(T);
    maj_T(T, "AABBB", "12000");
    printf("mot : AABBB, couleur : 12000 \nOccurence à (2,5) pour A et à 0 pour B:\n");
    print_T(T);

    return 0;
}
