#include "occurence_table.h"
#include <stdio.h>
#include <stdbool.h>

extern int nb_letters;

int min(int a, int b) { return (a < b) ? a : b; }
int max(int a, int b) { return (a > b) ? a : b; }

void init_T(occ_table buffer)
{
    for (int i = 0; i < 26; i++)
    {
        buffer[i][1] = nb_letters;
        buffer[i][0] = 0;
    }
}

void maj_T(occ_table T, char *mot, char *rep)
{
    occ_table T2;
    init_T(T2);
    compute_occ(T2, mot, rep, 0);
    int sum_min_occ = 0;
    for (int i = 0; i < 26; i++)
    {
        T[i][0] = max(T[i][0], T2[i][0]);
        T[i][1] = min(T[i][1], T2[i][1]);
        sum_min_occ += T[i][0];
    };
    for (int i = 0; i < 26; i++)
    {
        if (T[i][0] != T[i][1])
        {
            T[i][1] = nb_letters - sum_min_occ + T[i][0];
        };
    };
}

void copy_T(occ_table T, occ_table buffer)
{
    for (int i = 0; i < 26; i++)
    {
        buffer[i][1] = T[i][1];
        buffer[i][0] = T[i][0];
    }
}

void compute_occ(occ_table T, char *mot, char *rep, int index)
{
    if (index < nb_letters)
    {
        int a = mot[index] - 'A';
        int c = rep[index] - '0';

        if (c)
        {
            for (int i = 0; i < 26; i++)
            {
                if (i != a)
                {
                    T[i][1] -= (T[i][0] != T[i][1]);
                }
            }
            T[a][0] += 1;
            T[a][1] = max(T[a][0], T[a][1]);
        }
        else
        {
            T[a][1] = T[a][0];
        }
        compute_occ(T, mot, rep, index + 1);
    }
}

void print_T(occ_table T)
{
    for (int i = 0; i < 26; i++)
    {
        printf("\33[%dm%c : (%d, %d) \33[0m\n", (33 + T[i][0]) * (T[i][0] == T[i][1]), i + 'A', T[i][0], T[i][1]);
    }
    printf("\n");
}

int compteur_valide(occ_table T, compteur compteur)
{
    for (int i = 0; i < 26; i++)
    {
        if (T[i][0] > compteur[i] || T[i][1] < compteur[i])
        {
            return 0;
        }
    }
    return 1;
}

void init_C(compteur c)
{
    for (int i = 0; i < 26; i++)
    {
        c[i] = 0;
    }
}

bool filtre_D(occ_table T, char *mot)
{
    compteur c;
    init_C(c);
    for (int i = 0; i < nb_letters; i++)
    {
        int a = mot[i] - 'A';
        c[a]++;
        if (T[a][1] < c[a])
        {
            return false;
        }
    }
    return true;
}
