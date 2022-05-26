#include "dictionnary.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

extern int nb_letters;

cell* init_cell(char* word_cell,int ind){
    cell* cell_dico = malloc(sizeof(cell));
    cell_dico->word = word_cell;
    cell_dico->index = ind;
    cell_dico->previous = NULL;
    cell_dico->next = NULL;
    cell_dico->freq = 0;
    return cell_dico;
}

dico* init_dico(){

    /*Récupération de n en char* */
    char buffer_n[25];
    sprintf(buffer_n,"%d",nb_letters);

    /*Ouverture du bon fichier*/

    char dicoPath[32] = "src/dictionnaire/";
    strcat(dicoPath,buffer_n);
    char endDicoPath[25]="_lettres.txt";
    strcat(dicoPath,endDicoPath);
    
    FILE *f = fopen(dicoPath,"r"); 

    int longueurF =0; 
    char buffer_mot[10];
    fgets(buffer_mot,10,f); //Récupère dans buffer la 1ere ligne de f
    longueurF = atoi(buffer_mot); //Nombre de mots du fichier 
    
    char buffer[25];
    
    /*Libération de la mémoire pour x cellules*/

    dico* one_dico = malloc(sizeof(dico));
    one_dico->content = calloc(longueurF,sizeof(cell*)); 
    one_dico->first = 0;
    one_dico->taille = longueurF;
    int i=0;
    
    /*Remplissage de content*/

    while(fgets(buffer,25,f) != NULL){
        buffer[strlen(buffer)-1]='\0'; 
        char* buffer_copy= strdup(buffer);
        one_dico->content[i] = init_cell(buffer_copy,i);
        
        if(i !=0){
            one_dico->content[i-1]->next = one_dico->content[i];
            one_dico->content[i]->previous = one_dico->content[i-1];
        } 
        
        i++;
    }
    return one_dico;
}

void destroy_dico(dico* one_dico){
    for(int i=0;i<one_dico->taille;i++){
        free(one_dico->content[i]->word);
        free(one_dico->content[i]);
    }
    free(one_dico->content);
    free(one_dico);
}

void print_dico(dico* one_dico){
    for(int i=0;i<one_dico->taille;i++){
        printf("---%d---\n",one_dico->content[i]->index);
        printf("%s\n",one_dico->content[i]->word);
    }
}

void print_dico_p(dico* one_dico){
    cell* current_cell = one_dico->content[one_dico->first];
    while(current_cell != NULL){
        printf("---%d---\n",current_cell->index);
        printf("%s\n",current_cell->word);
        current_cell=current_cell->next;
    }
}

void maj_dico(dico* one_dico,occ_table T){
    
    cell* current_cell = one_dico->content[one_dico->first];
    
    while(current_cell != NULL){
        if(!filtre_D(T,current_cell->word)){
            suppr_dico(one_dico,current_cell->index);
        }
        current_cell = current_cell->next;
    }
}

void suppr_dico(dico* one_dico,int i){
    
    assert(i<one_dico->taille);
    cell* current_cell = one_dico->content[i];
    
    if(i == one_dico->first){ //Premier à supprimer
        if (current_cell->next != NULL){ //Dico réduit à 1 mot
            current_cell->next->previous = NULL;
            one_dico->first = current_cell->next->index;
        }
        else {
            printf("Un seul mot dans dico !\n");
        }
    }
    else{
        if (current_cell->next == NULL){ //Dernier à supprimer
            current_cell->previous->next = NULL;
            current_cell->previous = NULL;
        }
        else { //Cas autre
            current_cell->previous->next = current_cell->next;
            current_cell->next->previous = current_cell->previous;
        }
    }
}

char* pop(dico* one_dico,int i){
    assert(i<one_dico->taille);
    suppr_dico(one_dico,i);
    return(one_dico->content[i]->word);
}
