#include "dictionnary.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int nb_letters;
dico* D;
abr* A;

int main(){

    nb_letters = 4;
    D = init_dico();
    A = init_A(); 

    /* VERIFICATION QUE LE DICTIONNAIRE SE SOIT BIEN CHARGÉ : */
    
    print_dico(D);
    print_dico_p(D);


    /* --- TEST SUPPR_DICO --- */


    suppr_dico(D,1992); //Case - Last removed
    printf("ACHE (1992) shouldn't be here : \n");
    print_dico_p(D);
    suppr_dico(D,0); //Case - First removed
    printf("SUIS (0) shouldn't be here : \n");
    print_dico_p(D);
    suppr_dico(D,1990); //Case - Random removed
    printf("AGRO (1990) shouldn't be here : \n");
    print_dico_p(D);
    for (int i=1;i<D->taille;i++){
        if(i == 1992 || i==1990){
            continue;
        }
        suppr_dico(D,i);
    }
    printf("Only ADJA should remain : \n"); //Case - Only 1 element left
    print_dico_p(D);
    

    /* --- TEST POP --- */


    // Réinitialisation du dictionnaire 
    destroy_dico(D);
    D = init_dico();
    
    printf("Should be AGRO : %s\n",pop(D,1990)); //Case - Random removed
    printf("Should be SUIS : %s\n",pop(D,0)); //Case - First removed
    printf("Should be ACHE : %s\n",pop(D,1992)); //Case - Last removed
    printf("AGRO (1990), SUIS (0) and ACHE (1992) shouldn't be here : \n");
    //print_dico_p(D);
    for (int i=1;i<D->taille;i++){
        if(i == 1992 || i==1990){
            continue;
        }
        suppr_dico(D,i);
    }
    printf("Should be ADJA : %s \n",pop(D,D->taille-2)); //Case - Only 1 element left


    /* --- TEST MAJ_DICO --- */


    // Réinitialisation du dictionnaire 
    destroy_dico(D);
    D = init_dico();
    occ_table T;
    init_T(T);
    
    // Case - colour matching = 0

    maj_T(T,"ACHE","0000");
    MAJ_A(A,T,"ACHE","0000");
    maj_dico(D);
    printf("Any words with A,C,H and E shouldn't be here :\n");
    print_dico_p(D);
    
    // Case - colour matching = 1

    // Réinitialisation du dictionnaire et T
    destroy_dico(D);
    destroy_A(A);
    D = init_dico();
    init_T(T);
    A = init_A();

    maj_T(T,"ACHE","1111");
    MAJ_A(A,T,"ACHE","1111");
    maj_dico(D);
    printf("Only ACHE should be here :\n");
    print_dico_p(D);
    
    // Case - colour matching = 2

    // Réinitialisation du dictionnaire et T 
    destroy_dico(D);
    destroy_A(A);
    D = init_dico();
    init_T(T);
    A = init_A();

    maj_T(T,"ACHE","2222");
    MAJ_A(A,T,"ACHE","2222");
    maj_dico(D);
    printf("Only ACHE should be here :\n");
    print_dico_p(D);


    /* --- TEST MAJ_DICO2 --- */


    // Réinitialisation du dictionnaire et T
    destroy_dico(D);
    D = init_dico();
    init_T(T);
    
    // Case - colour matching = 0

    maj_T(T,"ACHE","0000");
    maj_dico2(T,D);
    printf("Any words with A,C,H and E shouldn't be here :\n");
    print_dico_p(D);

    // Case - colour matching = 1

    // Réinitialisation du dictionnaire et T
    destroy_dico(D);
    D = init_dico();
    init_T(T);

    maj_T(T,"ACHE","1111"); 
    maj_dico2(T,D);
    printf("Only ACHE should be here :\n");
    print_dico_p(D);

    // Case - colour matching = 2

    // Réinitialisation du dictionnaire et T 
    destroy_dico(D);
    D = init_dico();
    init_T(T);

    maj_T(T,"ACHE","2222"); 
    maj_dico2(T,D);
    printf("Only ACHE should be here :\n");
    print_dico_p(D);
    

    destroy_A(A);
    destroy_dico(D);
    return EXIT_SUCCESS;
}
