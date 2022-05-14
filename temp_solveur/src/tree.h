struct _abr {
    _abr* abr[26];
};
typedef _abr abr;

abr *init_A(cell D[]);
void add (abr A, char* mot);
void destroy_A(abr A);
int nb_match(abr A, table_acc T, char* mot, char* coul, int compteur[26]);
void MAJ(abr A. table_acc T, char* mot, char* coul, int compteur[26]);
