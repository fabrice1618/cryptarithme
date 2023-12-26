#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cryptarithme.h"

// Afficher une solution au cryptarithme
void solutions_print(char *operation, Conversion *conv)
{
    char solution[MAX_OPERATION_LEN];
    char *p = operation;
    char *q = solution;

    memset(solution, '\0', MAX_OPERATION_LEN);

    while (*p != 0)
    {
        int result = conversions_get(conv, *p);
        *q = (-1 == result) ? *p: '0' + result;
        q++;
        p++;
    }

    printf("solution:  %s\n", solution);
}

// Chercher les solutions à un cryptarithme
int solutions_chercher( char *operation, char (*operandes)[MAX_LEN], int operandes_cnt)
{
    Conversion *conv;
    int combinaison[10];

    printf("\nopération: %s\n", operation);

    // Création de la table de conversion à partir des operandes
    conv = conversions_init(operandes, operandes_cnt);

    while ( generateur_combinaison(combinaison, conv->cnt) ) {
        // Transferer la combinaison dans la structure de conversion
        conversions_set(conv, combinaison);

        long total = 0;
        for (int i = 0; i < operandes_cnt - 1; ++i) {
            total += conversions_convert(conv, operandes[i]);
        }

        long result = conversions_convert(conv, operandes[operandes_cnt - 1]);

        if (total == result) {
            solutions_print(operation, conv);
        }
    }

    // Liberation de la table de conversion
    free(conv);

    return 0;
}