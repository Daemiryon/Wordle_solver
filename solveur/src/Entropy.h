#ifndef ENTROPY_H
#define ENTROPY_H

void color(int n, char *buffer);

double Proba_colo(char *mot, char *color);

double Max_prob(char *mot);

double Entropy(char *mot);

int compute_next_strat_1();

int compute_next_strat_2();

#endif
