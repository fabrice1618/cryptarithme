#include <stdio.h>
#include <string.h>

#include "cryptarithme.h"

int main(int argc, char **argv) 
{
    char operandes[MAX_OPERANDES][MAX_LEN];
    char operation[MAX_OPERATION_LEN];
    int operandes_cnt;

    // Controle des parametres de la ligne de commande
    if (1 == argc) {
        printf("Usage: %s \"operation\"\n", argv[0]);
        return 0;
    } else if (2 != argc) {
        fprintf(stderr, "Erreur paramètres\n");
        return 1;
    }

    // Décomposer l'operation en opérandes
    strcpy(operation, argv[1]);
    operandes_cnt = operation_analyser(operation, operandes);
    if (operandes_cnt < 3) {
        fprintf(stderr, "Erreur opération incorrecte\n");
        return 1;
    }

    // Chercher et afficher les solutions
    solutions_chercher(operation, operandes, operandes_cnt);

    return 0;
}