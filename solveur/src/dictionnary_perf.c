#include "dictionnary.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int nb_letters;
dico* D;
abr* A;


int main(){

    time_t t0,tf;
    time(&t0);

    /* Insert here your test*/


    time(&tf);
    printf("%f",difftime(tf,t0));


    destroy_A(A);
    destroy_dico(D);

    return EXIT_SUCCESS;
}