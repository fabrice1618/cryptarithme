#include <stdio.h>
#include <string.h>

#include "cryptarithme.h"

// Etats de l'automate de conversion
typedef enum {
    STATE_INIT,
    STATE_OPERANDE,
    STATE_OPERATEUR,
    STATE_FINISH
} State;

// Fonction pour initialiser le tableau avec des chaînes vides
void operandes_initialiser(char (*operandes)[MAX_LEN]) 
{
    for (int i = 0; i < MAX_OPERANDES; ++i) {
        memset(operandes[i], '\0', sizeof(operandes[i]));
    }
}

// Afficher une opération (debug)
void operation_print(char *operation, char *ptr)
{
    printf("%s\n", operation);
    int pos = ptr - operation;
    printf("pos:%d\n", pos);
}

// State Machine
int operation_analyser(char *operation, char (*operandes)[MAX_LEN]) 
{
    operandes_initialiser(operandes);

    int op_idx = 0;

    State state = STATE_INIT;
    char *ptr = operation;

    while (state != STATE_FINISH) {
        switch (state) {
            case STATE_INIT:
                if (*ptr == ' ') {
                    // Ignorer les espaces initiaux
                    break;
                }
                if (*ptr >= 'A' && *ptr <= 'Z') {
                    strncat(operandes[op_idx], ptr, 1);
                    state = STATE_OPERANDE;
                    break;
                } else {
                    operation_print(operation, ptr);
                    fprintf(stderr, "Erreur : Caractère inattendu au début de l'opération = (%c)\n", *ptr);
                    return 0;
                }                

            case STATE_OPERANDE:
                if (*ptr == ' ' || *ptr == '=' || *ptr == '+') {
                    // Fin de l'opérande, passer à l'état suivant
                    op_idx++;
                    if (op_idx > MAX_OPERANDES) {
                        fprintf(stderr, "Erreur : Trop d'opérandes.\n");
                        return 0;
                    }
                    state = STATE_OPERATEUR;
                    break;
                }
                if ((*ptr >= 'A' && *ptr <= 'Z')) {
                    // Continuer à lire l'opérande
                    strncat(operandes[op_idx], ptr, 1);
                    break;
                } else {
                    operation_print(operation, ptr);
                    fprintf(stderr, "Erreur : Caractère inattendu dans l'opérande = (%c)\n", *ptr);
                    return 0;
                }

            case STATE_OPERATEUR:
                if (*ptr == ' ' || *ptr == '+' || *ptr == '=') {
                    // Ne pas stocker operateur
                    break;
                }
                if ((*ptr >= 'A' && *ptr <= 'Z')) {
                    strncat(operandes[op_idx], ptr, 1);
                    state = STATE_OPERANDE;
                    break;
                } else {
                    operation_print(operation, ptr);
                    fprintf(stderr, "Erreur : Caractère inattendu pendant séparateur: (%c)\n", *ptr);
                    return 0;
                }

            default:
                fprintf(stderr, "Erreur : État inattendu = %d.\n", state);
                return 0;
        }

        // Passer au caractère suivant
        ptr++;

        // Fin de la chaîne, terminer le traitement
        if (*ptr == '\0') {
            state = STATE_FINISH;
        }
    }

    return op_idx + 1;
}
