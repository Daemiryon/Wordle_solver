#include "dictionnary.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*Première version - sera sûrement sujette à modfications*/

cell* init_dico(int n){
    
    cell* dico = calloc(n,sizeof(cell));
    
    /*----Ouverture du bon dico----*/
    char* dicoPath = "../../appli/data/dictionnaires/"; 
    char n_charValue = n+'0'; //marche uniquement pour n<10 : TO FIX later
    char* dicoName = "_lettres.json";
    strcat(dicoPath,n_charValue); //Ajoute n_charValue à la fin de de dicoPath
    strcat(dicoPath,dicoName); // Même fonctionnement

    /*Remarque : l'ouverture est à tester*/

    FILE *f = fopen(dicoPath,"r");

    if(f == NULL){
        printf("/!\\ INVALID FILENAME /!\\");
    }
    else{

        int longueurF =0; 
        fscanf(f,"%d",&longueurF); //Récupération de l0
        char buffer[longueurF];

        fseek(f,1,SEEK_SET); //Ajuste (normalement) la lecture sur l1

        while(fgets(buffer,longueurF,f) != NULL){
            dico_add(dico,buffer);
            
            /*Ici, remplir le dico avec dico_add*/

        }
    }

    fclose(f);
    return dico;
}


void dico_add(cell* dico, char* word){
    
}