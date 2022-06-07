#include "tree.h"
#include "dictionnary.h"
#include "occurence_table.h"
#include "Entropy.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variables
abr *A;
occ_table T;
dico *D;
int nb_letters;
double nb_mots;

void get_nb_letters()
{
    FILE *f = fopen("src/wsolf.txt", "r");
    fscanf(f, "%d", &nb_letters);
    printf("\nNombre de lettres: %d\n", nb_letters);
    fclose(f);
}

void get_opener(char *opener)
{

    FILE *f = fopen("src/openers.txt", "r");
    int line = nb_letters;
    for (int i = 0; i < line; ++i)
    {
        fgets(opener, nb_letters + 3, f);
    }
    fclose(f);
}

void get_input(char *input)
{
    bool done = false;
    bool is_valid_char;
    bool is_valid_word;
    char *valid_numbers = "012";

    while (!done)
    {
        printf("User answer: ");
        scanf("%s", input);
        if (strcmp(input, "-1") == 0)
        {
            return;
        }
        if ((int)strlen(input) != nb_letters)
        {
            printf("La longueur de la chaîne ne correspond pas avec la longueur du mot à trouver. Réessayez !\n");
        }
        else
        {
            is_valid_word = true;
            for (int i = 0; i < nb_letters; i++)
            {
                is_valid_char = false;
                for (int j = 0; j < 3; j++)
                {
                    if (input[i] == valid_numbers[j])
                    {
                        is_valid_char = true;
                    }
                }
                if (!is_valid_char)
                {
                    printf("Un ou plusieurs caractères de la chaîne ne sont pas valides ! Réessayez.\n");
                    is_valid_word = false;
                    break;
                }
            }
            if (is_valid_word)
            {
                done = true;
            }
        }
    }
}

bool end_condition(char *input, char *guess)
{
    if (strcmp(input, "-1") == 0)
    {
        printf("Partie interrompue.\n");
        return true;
    }
    compteur c;
    init_C(c);

    if (nb_match(A, T, guess, input, c) == 0)
    {
        printf("Désolé mais le mot auquel vous pensez ne figure pas dans notre dictionnaire\n");
        return true;
    }

    for (int i = 0; i < nb_letters; i++)
    {
        if (input[i] != '2')
        {
            return false;
        }
    }

    printf("Mot trouvé.\n");
    return true;
}

int main()
{

    get_nb_letters(); // reads wsolf.txt

    char opener[nb_letters + 2];
    char input[nb_letters + 2];
    char *guess;
    int index;
    //char buffer[nb_letters + 1];
    init_T(T);
    D = init_dico();
    A = init_A();
    nb_mots = D->taille;

    if (nb_letters <= 10)
    {
        get_opener(opener); // reads openers.txt (the content of this file has to calculated)
        guess = opener;
    }
    else
    {
        guess = D->content[D->first]->word;
    }

    printf("\nOpener: %s", guess);
    get_input(input);

    maj_T(T, guess, input);

    while (!end_condition(input, guess))
    {
        nb_mots = MAJ_A(A, T, guess, input);

        if (nb_letters > 6)
        {
            maj_dico(D);
        }
        else
        {
            maj_dico2(T, D);
        }

        if (nb_letters <= 10)
        {
            index = compute_next_strat_2();
        }
        else
        {
            index = D->first;
        }

        guess = pop(D, index);
        printf("\nGuess : %s\n", guess);
        get_input(input); // provides "-1" or a verified nb_letters character string input, also allows exiting of the program
        maj_T(T, guess, input);
    }
    destroy_A(A);
    destroy_dico(D);
    return EXIT_SUCCESS;
}
