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

// abr *init_A(); // 1) créer un Arbre, 2)parcour le dico global et rempli l'arbre grace à la fonction add()
// int MAJ_A(abr A, occ_table T, char *mot, char *coul, int compteur[26]);
