#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

// Calculer une puissance de 10 (sous forme d'entiers)
long puissance_10(int facteur)
{
    assert(facteur >= 1 && facteur <= 10);

    long result = 1;
    for(int i = 0; i < facteur; i++) {
        result *= 10;
    }

    return result;
}

// Verifier si la combinaison est valide 
// cad ne contenant que des chiffres différents
bool combinaison_valide(long cnt, int *combinaison, int nombre_chiffres)
{
    long reste;
    int chiffre;
    int utilisation[10] = {0};
    int *p = combinaison;

    // Decomposer cnt suivant ces chiffres
    reste = cnt;
    for (int i = 0; i < nombre_chiffres; i++) {
        // Isolation d'un chiffre
        chiffre = reste % 10;
        reste /= 10;

        // Stocker la combinaison
        *p = chiffre;
        p++;

        // vérifier le nombre d'utilisations
        utilisation[chiffre] += 1;
        if (utilisation[chiffre] > 1)
            return false;
    }

    return true;
}


// Retourner une combinaison de n chiffres 
// dont tous les chiffres sont différents
bool generateur_combinaison(int *combinaison, int nombre_chiffres)
{
    static long cnt = -1;
    static long cnt_max = 0;
    bool trouve = false;

    // Initialiser le générateur
    if (-1 == cnt) {
        cnt = 0;
        cnt_max = puissance_10( nombre_chiffres );
    }

    // Chercher une combinaison dont tous les chiffres sont différents
    while (!trouve && cnt < cnt_max) {
        if ( combinaison_valide(cnt, combinaison, nombre_chiffres) ) {
            trouve = true;
        }
        cnt++;
    }

    return trouve;
}
