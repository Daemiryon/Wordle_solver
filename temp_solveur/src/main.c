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

void get_input(char* input){ //"while(invalid input)do(ask input and check its validity)"
    bool done = false;
    bool is_valid_char;
    bool is_valid_word;
    char* valid_numbers = "012";
    printf(\
        "Please review my word M.F !\n\
        0:Letter not found\n\
        1:Letter in wrong position\n\
        2:Letter in correct position\n\
        -1:Exit\n"\
    );
        
    while(!done){
        printf("M.F. answer: ");
        scanf("%s", input);
        if(strcmp(input,"-1")==0){
            exit(EXIT_SUCCESS);
        }
        if(strlen(input)!=5){
            printf("Wrong number of numbers ! Try again.\n");
        }
        else {
            is_valid_word = true;
            for (int i=0;i<5;i++){
                is_valid_char = false;
                for (int j=0;j<3;j++){
                    if(input[i] == valid_numbers[j]){
                        is_valid_char = true;
                    }
                }
                if(!is_valid_char){
                    printf("Invalid characters ! Try again.\n");
                    is_valid_word = false;
                    break;
                }
            }
            if(is_valid_word){
                done = true;
                printf("Registered input: %s\n",input);
            }
        }
    }
}

int main() {
    /* cell* D = init_dico(nb_letters);
    abr* init_A();
    occ_table T;
    init_T(T); */
    char input[512];
    get_nb_letters(); //reads wsolf.txt
    output_opener();  //reads openers.txt (the content of this file has to calculated)
    while(true){
        get_input(input); //provides a verified 5 character string input, also allows exiting of the program
        //Traitement [...]
        printf("Proposed word: ?\n");
    }
}
