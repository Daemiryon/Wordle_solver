#include "dictionnary.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int nb_letters;
dico* D;
abr* A;

int main(){

    nb_letters = 10;
    D = init_dico();
    A = init_A();
    occ_table T;
    init_T(T);

    clock_t start = clock(),diff; //début timer
    
    /*Insert your code here*/

    diff = clock() - start; //fin timer
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Temps : %d,%d\n", msec/1000, msec%1000);

    destroy_A(A);
    destroy_dico(D);

    return EXIT_SUCCESS;
}
