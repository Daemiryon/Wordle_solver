#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

extern int nb_letters;
extern dico* D;

abr *creat_abr(int profondeur)
{
    abr *A = calloc(1, sizeof(abr));
    A->profondeur = profondeur;
    for (int i = 0; i < 26; i++)
    {
        A->branche[i] = NULL;
    }
    return A;
}

abr* init_A(){
    abr* A = creat_abr(0);
    for (int i = 0; i<D->taille; i++)
    {
        add(A,D->content[i]->word);
    }
    return A;
}

void print_A(abr *A, char *buffer)
{
    int p = A->profondeur;
    if (p == nb_letters)
    {
        buffer[nb_letters] = '\0';
        printf("%s\n", buffer);
    }
    else
    {
        for (unsigned int i = 0; i < 26; i++)
        {
            if (A->branche[i])
            {
                buffer[p] = i + 65;
                print_A(A->branche[i], buffer);
            }
        }
    }
}

void add(abr *A, char *mot)
{
    int i = A->profondeur;
    if (i < nb_letters)
    {
        int a = mot[i] - 'A';
        if (!A->branche[a])
        {
            A->branche[a] = creat_abr(i + 1);
        }
        add(A->branche[a], mot);
    }
}

void destroy_A(abr *A)
{
    for (int i = 0; i < 26; i++)
    {
        if (A->branche[i])
        {
            destroy_A(A->branche[i]);
        }
    };
    free(A);
}

int nb_match(abr *A, occ_table T, char *mot, char *coul, compteur compteur)
{
    int p = A->profondeur;

    if (p < nb_letters)
    {

        int a = mot[p] - 'A'; /* récupère l'indice de la lettre courante */
        int count = 0;

        switch (coul[p])
        {
        case '2': /* lettre bien place -> 1 seul sous arbre à explorer */

            if (A->branche[a] && (T[a][1] > compteur[a]))
            {
                compteur[a]++;
                count += nb_match(A->branche[a], T, mot, coul, compteur);
                compteur[a]--;
            }

            break;

        case '1': /* 1 & 0 -> lettre pas à la bonne place -> on explores les sous arbre non vide parmis les 25 restants */
        case '0':
            for (int i = 0; i < 26; i++)
            {
                if ((A->branche[i]) && (i != a) && (T[i][1] > compteur[i]))
                {
                    compteur[i]++;
                    count += nb_match(A->branche[i], T, mot, coul, compteur);
                    compteur[i]--;
                }
            }
            break;
        }
        return count;
    }
    return compteur_valide(T, compteur);
}

int MAJ_A(abr *A, occ_table T, char *mot, char *color){
    compteur c;
    init_C(c);
    return elague(A,T,mot,color,c);
}
int elague(abr *A, occ_table T, char *mot, char *color, compteur c){
    int p = A->profondeur;
    if (p < nb_letters)
    {
        int a = mot[p] - 65; /* récupère l'indice de la lettre courante */
        int count = 0;
        int temp_count;
        switch (color[p])
        {
        case '2': /* lettre bien place -> 1 seul sous arbre à explorer */
            for (int i = 0; i < 26; i++)
            {
                if (A->branche[i] && i != a)
                {
                    destroy_A(A->branche[i]);
                    A->branche[i] = NULL;
                }
            }
            if (A->branche[a])
            {
                if (T[a][1] > c[a])
                {
                    c[a]++;
                    temp_count = elague(A->branche[a], T, mot, color, c);
                    count += temp_count;
                    c[a]--;

                    if (temp_count == 0)
                    {
                        destroy_A(A->branche[a]);
                        A->branche[a] = NULL;
                    }
                }
                else
                {
                    destroy_A(A->branche[a]);
                    A->branche[a] = NULL;
                }
            }
            break;
        case '1': /* 1 & 0 -> lettre pas à la bonne place -> on explores les sous arbre non vide parmis les 25 restants */
        case '0':
            for (int i = 0; i < 26; i++)
            {
                if ((A->branche[i]) && (i != a))
                {
                    if (T[i][1] > c[i])
                    {
                        c[i]++;
                        temp_count = elague(A->branche[i], T, mot, color, c);
                        count += temp_count;
                        c[i]--;
                        if (temp_count == 0)
                        {
                            destroy_A(A->branche[i]);
                            A->branche[i] = NULL;
                        }
                    }
                    else
                    {
                        destroy_A(A->branche[i]);
                        A->branche[i] = NULL;
                    }
                }
            }
            if (A->branche[a])
            {
                destroy_A(A->branche[a]);
                A->branche[a] = NULL;
            }
            break;
        }
        return count;
    }
    return compteur_valide(T, c);
}
//[ recursif ] Ellague l'arbre et retourne le nombre de mots restant. Même algo que nb_match() + destoy les branches non_exploré.
