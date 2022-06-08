#include "tree.h"
#include "dictionnary.h"
#include <stdio.h>
#include <math.h>

extern abr *A;
extern occ_table T;
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
    occ_table T_temp;
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
        if (P)
        {
            E -= P * log2(P);
        }
    }
    return E;
}

double Max_prob(char *mot)
{
    double P;
    double P_max = 0;
    char couleur[nb_letters + 1];
    for (int i = 0; i < pow(3, nb_letters); i++)
    {
        color(i, couleur);
        P = Proba_Colo(mot, couleur);
        if (P > P_max)
        {
            P_max = P;
        }
    }
    // printf("P_MAX : %f\n", P_max);
    return P_max;
}

int compute_next_strat_1()
{
    int index_best;
    double E_max = 0;
    double E;
    cell *Cell = D->content[D->first];
    while (Cell)
    {
        E = Entropy(Cell->word);
        // printf("%f\n", E);
        if (E > E_max)
        {
            E_max = E;
            index_best = Cell->index;
        }
        Cell = Cell->next;
    }
    return index_best;
}

int compute_next_strat_2()
{
    int flag = 1;
    int index_best = 0;
    double P_min = 1;
    double P;
    cell *Cell = D->content[D->first];
    while (Cell)
    {
        P = Max_prob(Cell->word);
        if (((P_min > P) && P) || (verify(A, Cell->word) && ((P_min == P) && flag)))
        {
            if (!verify(A, Cell->word))
            {
                flag = 1;
            }
            else
            {
                flag = 0;
            }
            // printf("%s , %f \n", Cell->word, P);
            P_min = P;
            index_best = Cell->index;
            // printf("%d\n", index_best);
        }
        Cell = Cell->next;
    }
    return index_best;
}
