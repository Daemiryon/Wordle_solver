#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

extern int nb_letters;

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

// abr *init_A();

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

        int a = mot[p] - 'A';
        int count = 0;
        // printf("-> %c ; p = %d\n", a + 'A', p);

        switch (coul[p])
        {
        case '2': /* lettre bien place -> 1 seul sous arbre à explorer */

            if (A->branche[a] && T[a][1] > compteur[a])
            {
                // printf("[ 2.0 ] : %c ; p = %d; A[%c] = %s \n", a + 'A', p, a + 'A', (A->branche[a] == NULL) ? "FALSE" : "TRUE");
                compteur[a]++;
                count += nb_match(A->branche[a], T, mot, coul, compteur);
                compteur[a]--;
                // printf("[ 2.1 ] : %c ; p = %d\n", a + 'A', p);
            }

            break;

        case '1': /* 1 & 0 -> lettre pas à la bonne place -> on explores les sous arbre non vide parmis les 25 restants */
        case '0':
            for (int i = 0; i < 26; i++)
            {
                if (A->branche[i] && i != p && T[i][1] > compteur[i])
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

    // printf("%s\n", compteur_valide(T, compteur) ? "True" : "False");
    return compteur_valide(T, compteur);
}

// void MAJ(abr A, occ_table T, char *mot, char *coul, int compteur[26]);
