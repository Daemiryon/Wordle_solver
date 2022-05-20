#include "tree.h"
#include "dictionnary.h"
#include "occurence_table.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nb_letters;

void get_nb_letters(){
    FILE* f = fopen ("wsolf.txt", "r");
    fscanf(f,"%d",&nb_letters);
    printf("Nombre de lettres: %d\n",nb_letters);
    fclose(f);
}

void output_opener(){
    FILE* f = fopen ("openers.txt", "r");
    int line = nb_letters;
    char str[512];
    for(int i=0;i<line;++i){
        fgets(str, sizeof(str), f);
    }
    fclose(f);
    printf("Opener: %s\n",str);
}

int main() {
    char input[4];
    get_nb_letters();
    output_opener();
    while(true){
        printf(\
        "Please review my word M.F !\n\
        0:Letter not found\n\
        1:Letter in wrong position\n\
        2:Letter in correct position\n\
        -1:Exit\n"\
        );
        fgets(input, 4, stdin);
        if(strcmp(input,"-1")==0){
            printf("FUCK");
            return EXIT_SUCCESS;
        }
    }
    /* cell* D = init_dico(nb_letters); */
    abr* init_A();
    occ_table T;
    init_T(T);
    return EXIT_SUCCESS;
}
