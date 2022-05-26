#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

dico* D;
abr* A;
int nb_letters;

int main()
{
    // TESTS AVEC DES MOTS DE 4 LETTRES
    // (pour des longueurs différentes, changer la variable globale "nb_letters" ci-après et choisir un mot dans le dictionnaire correspondant)
    // -----
    // Pour "AXEL" et la couleur "2222", doit afficher un seul mot : AXEL                                                               ==> OK
    // Pour "AAAA" et la couleur "2222", doit afficher aucun mot                                                                        ==> OK
    // Pour "AXEL" et la couleur "1111", doit afficher aucun mot                                                                        ==> OK
    // Pour "AAAA" et la couleur "1111", doit afficher aucun mot                                                                        ==> OK
    // Pour "AXEL" et la couleur "0000", doit afficher tous les mots qui ne contiennent pas de A                                        ==> OK
    // Pour "AAAA" et la couleur "0000", doit afficher tous les mots qui ne contiennent pas de A                                        ==> OK
    // Pour "AXEL" et la couleur "1000", doit afficher les mots qui ne commençent pas par A                                             ==> OK
    // Pour "AAAA" et la couleur "1000", doit afficher aucun mot                                                                        ==> OK
    // Pour "AXEL" et la couleur "2000", doit afficher seulement les mots commençent par la lettre A                                    ==> OK
    // Pour "AAAA" et la couleur "2000", doit afficher seulement les mots qui ne contiennent qu'un seul A et qui est au début du mot    ==> OK

    nb_letters = 4;
    char* wordTest = "AAAA";
    char* colorTest = "2000";

    D = init_dico();
    A = init_A();
    char buffer[nb_letters + 1];
    printf("%d\n",verify(A,"AXEL"));
    printf("%d\n",verify(A,"AAAA"));
    //print_A(A, buffer);   // Print pour vérifier le fonctionnement de la fonction d'initialisation de l'arbre
    
    occ_table T;
    init_T(T);
    compteur c;
    init_C(c);
    maj_T(T,wordTest,colorTest);
    MAJ_A(A,T,wordTest,colorTest);
    print_A(A,buffer);
    
    destroy_A(A);
    destroy_dico(D);
    return EXIT_SUCCESS;
}
