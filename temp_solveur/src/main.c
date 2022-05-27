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
    FILE *f = fopen("wsolf.txt", "r");
    fscanf(f, "%d", &nb_letters);
    printf("Nombre de lettres: %d\n", nb_letters);
    fclose(f);
}

void get_opener(char *opener)
{

    FILE *f = fopen("openers.txt", "r");
    int line = nb_letters;
    for (int i = 0; i < line; ++i)
    {
        fgets(opener, nb_letters + 3, f);
    }
    fclose(f);
}

void get_input(char *input)
{ //"while(invalid input)do(ask input and check its validity)"
    bool done = false;
    bool is_valid_char;
    bool is_valid_word;
    char *valid_numbers = "012";
    // printf(
    //     "Please review my word M.F !\n\
    //     0:Letter not found\n\
    //     1:Letter in wrong position\n\
    //     2:Letter in correct position\n\
    //     -1:Exit\n");

    while (!done)
    {
        printf("M.F. answer: ");
        scanf("%s", input);
        if (strcmp(input, "-1") == 0)
        {
            return;
        }
        if (strlen(input) != nb_letters)
        {
            printf("Wrong number of numbers ! Try again.\n");
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
                    printf("Invalid characters ! Try again.\n");
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

bool end_condition(char *input)
{
    if (strcmp(input, "-1") == 0)
    {
        printf("Partie interrompue.\n");
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
    char buffer[nb_letters + 1];
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

    printf("Opener: %s\n", guess);
    get_input(input);
    while (!end_condition(input))
    {
        maj_T(T, guess, input);
        MAJ_A(A, T, guess, input);
        maj_dico(D);

        // print_A(A, buffer);
        // print_T(T);
        // print_dico_p(D);

        if (nb_letters <= 10)
        {
            index = compute_next_strat_1();
        }
        else
        {
            index = D->first;
        }

        guess = pop(D, index);
        printf("Guess : %s\n", guess);
        get_input(input); // provides "-1" or a verified nb_letters character string input, also allows exiting of the program
    }
    destroy_A(A);
    destroy_dico(D);
    return EXIT_SUCCESS;
}
