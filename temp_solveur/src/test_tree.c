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

dico* D;
abr* A;
int nb_letters;

int main()
{

    nb_letters = 4;
    D = init_dico();

    A = init_A();
    char buffer[nb_letters + 1];
    //print_A(A, buffer);
    
    occ_table T;
    init_T(T);
    compteur c;
    init_C(c);

    maj_T(T,"AXEL","2222");
    MAJ_A(A,T,"AXEL","2222");
    print_A(A,buffer);
    // for (int i = 0; i < 52; i++)
    // {
    //     // init_T(T);
    //     maj_T(T, mots[i], couleur[i]);
    //     // print_T(T);

    //     printf("%s : \n", mots[i]);
    //     compteur c;
    //     init_C(c);
    //     printf("%d \n", elague(A, T, mots[i], couleur[i], c));
    //     printf("%d \n", nb_match(A, T, mots[i], couleur[i], c));
    //     print_A(A, buffer);
    // }

    destroy_A(A);
    destroy_dico(D);
    return 0;
}
