#include "tree.h"
#include "dictionnary.h"
#include <math.h>

extern abr *A;
extern occ_table *T;
extern dico *D;
extern int nb_letters;
extern double nb_mots;

void color(int n, char *buffer)
{
    for (int i = 0; i < nb_letters; i++)
    {
        buffer[i] = '0' + n % 3;
        n = n / 3;
    }
    buffer[nb_letters] = '\0';
}

double Proba_Colo(char *mot, char *color)
{
    compteur c;
    occ_table *T_temp;
    init_C(c);
    copy_T(T, T_temp);
    maj_T(T_temp, mot, color);
    return nb_match(A, T_temp, mot, color, c) / nb_mots;
}

double Entropy(char *mot)
{
    double P;
    double E = 0;
    char couleur[nb_letters + 1];
    for (int i = 0; i < pow(3, nb_letters); i++)
    {
        color(i, couleur);
        P = Proba_Colo(mot, couleur);
        E -= P * log2(P);
    }
    return E;
}

int compute_next_strat_1()
{
    cell *Cell = D->content[D->first];
    while (Cell)
    {
        }
}

int compute_next_strat_2()
{
}
