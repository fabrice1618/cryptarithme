#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "cryptarithme.h"

// vérifier si la conversion existe deja
bool conversions_existe(Conversion *conv, char car)
{
    bool trouve = false;
    int indice = 0;
    struct conversion_element *p;

    while (indice < conv->cnt && !trouve) {
        p = &conv->table[indice];
        if (p->lettre == car) {
            trouve = true;
        }
        indice++;
    }

    return trouve;
}

// Ajout d'une conversion dans la table
void conversions_add(Conversion *conv, char car)
{
    struct conversion_element *p;

    if ( !conversions_existe(conv, car) ) {
        p = &conv->table[conv->cnt];
        p->lettre = car;
        p->chiffre = -1;
        conv->cnt += 1;
    }
    
}

// Ajouter dans la table de conversion les symboles d'un operande
void conversions_add_string(Conversion *conv, char *chaine)
{
    char *p = chaine;

    while (*p != 0) {
        conversions_add(conv, *p);
        p++;
    }
}

// Allouer et initialiser une table de conversion
Conversion *conversions_init(char (*operandes)[MAX_LEN], int operandes_cnt)
{
    Conversion *conv;

    // Création dynamique
    conv = malloc( sizeof(Conversion) );
    if (NULL == conv) {
        fprintf(stderr, "Erreur allocation 'Conversion'");
        exit(2);
    }

   // Initialiser la table comme vide
   conv->cnt = 0;

    for (int i = 0; i < operandes_cnt; ++i) {
        conversions_add_string(conv, operandes[i]);
    }

    return conv;
}

// Afficher la table de conversion
void conversions_print(Conversion *conv)
{
    struct conversion_element *p;

    printf("Conversion: cnt=%d, [", conv->cnt);
    for(int i = 0; i < conv->cnt; i++) {
        p = &conv->table[i];
        if (i != 0) {
            printf(", ");
        }
        printf("%c:%d", p->lettre, p->chiffre);
    }
    printf("]\n");
}

// Affecter la combinaison à la table de conversion
void conversions_set(Conversion *conv, int *combinaison)
{
    struct conversion_element *p;

    for (int i = 0; i < conv->cnt; i++) {
        p = &conv->table[i];
        p->chiffre = combinaison[i];
    }

}

// Récupérer le chiffre correspondant à un caractere
int conversions_get(Conversion *conv, char car)
{
    int result = -1;
    struct conversion_element *p;
    int indice = 0;

    while (indice < conv->cnt && -1 == result) {
        p = &conv->table[indice];
        if (p->lettre == car) {
            result = p->chiffre;
        }
        indice++;
    }

    return result;
}

// Convertir un operande en nombre
long conversions_convert(Conversion *conv, char *chaine)
{
    long result = 0;
    char *p = chaine;

    while (*p != 0)
    {
        result *= 10;
        result += conversions_get(conv, *p);
        p++;
    }

    return result;
}

