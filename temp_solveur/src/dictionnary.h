#ifndef DICTIONNARY_H
#define DICTIONNARY_H

typedef struct cell{
    char* word;
    struct cell* next;
    struct cell* previous;
    int index;
} cell;

extern cell* init_dico(int); //Problème de type (?)
extern void destroy_dico(cell[]);
extern void maj_dico(); //missing args is normal
extern void suppr_dico(cell[],int);
extern char* pop(cell[],int); 

#endif
