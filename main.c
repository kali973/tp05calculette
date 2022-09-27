#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int slong(char *s1);

int existe(char *s1);

char *substr(char *input, unsigned int i, size_t ind);

int calculator(char *t, char *right, char *left);

int stringToInt(char *left);

int main() {
    char str[1000];
    char reponse[] = "next";

    while (strcmp(reponse, "exit")) {

        printf("Entrez une chaine de caractéres valide (Exemple : 120+6) :\n");
        sscanf("%s", str);

        if (existe(str) == -1) {
            puts("Vous n'avez pas saisi d'opérateur valable");
            exit(1);
        }

        printf("(<exit> pour quitter ou <next>)\n");
        scanf("%s", reponse);
    } // while "Quit"
    return 0;
}

int existe(char *str_input) {

    size_t ind = strlen(str_input);

    for (unsigned int indice = 0; indice < ind; indice++) {
        if (str_input[indice] == '+' || str_input[indice] == '-' || str_input[indice] == '*' ||
            str_input[indice] == '/') {

            char *operator_t = substr(str_input, indice, indice + 1);
            char *operandeLeft = substr(str_input, indice + 1, ind);
            char *operandeRight = substr(str_input, 0, indice);

            int val = calculator(operator_t, operandeRight, operandeLeft);

            printf("Resultat de %s = %d \n", str_input, val);

            free(operator_t);
            free(operandeLeft);
            free(operandeRight);

            return indice;
        }
    }
    return (-1);
}

char *substr(char *input, unsigned int debut, size_t ind) {

    int len = ind - debut;
    char *dest = (char *) malloc(sizeof(char) * (len + 1));

    for (int i = debut; i < ind && (*(input + i) != '\0'); i++) {
        *dest = *(input + i);
        dest++;
    }

    *dest = '\0';

    return dest - len;
}

int calculator(char *operator_t, char *operandeRight, char *operandeLeft) {

    int operande1 = atoi(operandeRight);
    int operande2 = stringToInt(operandeLeft); //Todo stringToint()

    int resultat;

    if (*operator_t == '+') {
        resultat = operande1 + operande2;
    } else if (*operator_t == '-') {
        resultat = operande1 - operande2;
    } else if (*operator_t == '*') {
        resultat = operande1 * operande2;
    } else if (*operator_t == '/') {
        resultat = operande1 / operande2;
    }

    return resultat;
}

int stringToInt(char *str_input) {

    // Il existe une fonction de bibliothèque qui fait la même chose atoi ou strtol
    int indice;

    for (indice = 0; str_input[indice] != '\0'; indice++) {
        int value = strtol(str_input, NULL, 10);
        return value;
    }
}

int toString(char a[]) {
    int c, sign, offset, n;
    if (a[0] == '-') {  // Handle negative integers
        sign = -1;
    }

    if (sign == -1) {  // Set starting position to convert
        offset = 1;
    } else {
        offset = 0;
    }

    n = 0;
    for (c = offset; a[c] != '\0'; c++) {
        n = n * 10 + a[c] - '0';
    }
    if (sign == -1) {
        n = -n;
    }
    return n;
}