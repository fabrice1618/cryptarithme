#ifndef CRYPTARITHME_H
#define CRYPTARITHME_H

#include <stdbool.h>

#define MAX_OPERANDES 10
#define MAX_LEN 50
#define MAX_OPERATION_LEN 200

struct conversion_element {
    char lettre;
    int chiffre;
};

typedef struct conversion_t {
    struct conversion_element table[10];
    int cnt;
} Conversion;

int operation_analyser(char *operation, char (*operandes)[MAX_LEN]);
int solutions_chercher( char *operation, char (*operandes)[MAX_LEN], int operandes_cnt);
void solutions_print(char *operation, Conversion *conv);
bool generateur_combinaison(int *combinaison, int nombre_chiffres);
int conversions_get(Conversion *conv, char car);
Conversion *conversions_init(char (*operandes)[MAX_LEN], int operandes_cnt);
void conversions_set(Conversion *conv, int *combinaison);
long conversions_convert(Conversion *conv, char *chaine);

#endif