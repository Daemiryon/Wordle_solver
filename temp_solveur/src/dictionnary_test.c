#include "dictionnary.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){

    dico* dico = init_dico(3); 
    print_dico(dico);
    print_dico_p(dico);
    

    destroy_dico(dico);

    return EXIT_SUCCESS;
}
