#include "dictionnary.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int nb_letters;

int main(){

    nb_letters = 5;
    
    dico* dico;
    dico = init_dico(); 
    //print_dico(dico);
    //print_dico_p(dico);
    
    /*
    printf("----SUPPR_DICO----\n");
    suppr_dico(dico,22);
    suppr_dico(dico,21);
    printf("FIRST PRINT\n");
    print_dico_p(dico);
    suppr_dico(dico,20);
    suppr_dico(dico,19);
    suppr_dico(dico,18);
    suppr_dico(dico,1);
    suppr_dico(dico,0);
    suppr_dico(dico,2);
    suppr_dico(dico,3);
    suppr_dico(dico,10);
    suppr_dico(dico,9);
    suppr_dico(dico,11);
    suppr_dico(dico,12);
    suppr_dico(dico,8);
    suppr_dico(dico,7);
    printf("2nd PRINT\n");
    print_dico_p(dico);
    suppr_dico(dico,4);
    suppr_dico(dico,5);
    suppr_dico(dico,6);
    suppr_dico(dico,14);
    suppr_dico(dico,13);
    printf("3rd PRINT\n");
    print_dico_p(dico);
    suppr_dico(dico,15);
    suppr_dico(dico,16);
    suppr_dico(dico,17);
    */
    
    /*
    printf("----POP----\n");
    printf("Should be S : %s\n",pop(dico,15));
    printf("Should be A : %s\n",pop(dico,0));
    printf("Should be Z : %s\n",pop(dico,22));
    printf("S,A and Z shouldn't be here : \n");
    print_dico_p(dico);
    */

   /*
    printf("----MAJ_DICO----\n");

    occ_table T;
    init_T(T);
    maj_T(T,"AVION","00000");
    
    maj_dico(dico,T);

    print_dico_p(dico);
    print_T(T);
    */

    destroy_dico(dico);

    return EXIT_SUCCESS;
}
