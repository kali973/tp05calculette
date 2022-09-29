#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE    1
#define SPACE   ' '

int slong(char *s1);

int existe(char *s1);

char *substr(char *input, unsigned int i, size_t ind);

int calculator(char *t, int operator1, int operator2);

int strToint(char *right);

char *trim(char *s1, int i);

int main() {
    char str[1000];
    char rep[100];

    while (TRUE) {

        printf("\nIndiquez l'operation a effectuer [Quit/Calcul]: ");
        scanf("%s", rep);

        switch (rep[0]) {
            case 'q':
            case 'Q':
                exit(0);

            case 'c':
            case 'C':

                printf("Entrez une chaine de caractéres valide (Exemple : 120+6 ou -120+6) : ");

                scanf("%c", str);

                char *withSpace = fgets(str, 1000, stdin);
                char *strWithoutSpace = trim(withSpace, strlen(str));

                if (existe(strWithoutSpace) == -1) {
                    puts("Vous n'avez pas saisi d'opérateur valable");
                }
                break;
        }

    }
}

char *trim(char *withSpace, int len) {
    int i = 0, k = 0;
    while (i < len) {
        if ((withSpace[i] == SPACE) || (withSpace[i] == '\t')) {
            i++;
        } else {
            withSpace[k] = withSpace[i];
            k++;
            i++;
        }
    }
    withSpace[k] = '\0';
    return withSpace;
}

/*-------------------------------------------------------------------*/
/* function control of read value operator and values to compute     */
/*-------------------------------------------------------------------*/

int existe(char *strWithoutSpace) {

    int len = strlen(strWithoutSpace) -1;

    for (unsigned int indice = 0; indice < len; indice++) {
        if (strWithoutSpace[indice] == '+' || strWithoutSpace[indice] == '-' || strWithoutSpace[indice] == '*' ||
            strWithoutSpace[indice] == '/') {
            if (strWithoutSpace[0] == '-' && indice == 0) {
                indice++;
            }else {
                //Extract operator and sign
                char *operator_t = substr(strWithoutSpace, indice, indice + 1);
                char *operatorLeft = substr(strWithoutSpace, indice + 1, len);
                char *operatorRight = substr(strWithoutSpace, 0, indice);

                // transfor string to int values
                int operator1 = strToint(operatorRight);
                int operator2 = strToint(operatorLeft);

                // if the first operator is a negative value
                if (strWithoutSpace[0] == '-') {
                    operator1 = operator1 * -1;
                }

                printf("Result is %s = %d \n", strWithoutSpace, calculator(operator_t, operator1, operator2));

                // free of memory
                free(operator_t);
                free(operatorLeft);
                free(operatorRight);

                return indice;
            }
        }
    }
    return (-1);
}

/*-------------------------------------*/
/* function substring String           */
/*-------------------------------------*/

char *substr(char *input, unsigned int debut, size_t ind) {

    int len = ind - debut;
    char *result = (char *) malloc(sizeof(char) * (len + 1));

    for (int i = debut; i < ind && (*(input + i) != '\0'); i++) {
        *result = *(input + i);
        result++;
    }
    *result = '\0';
    return result - len;
}

/*---------------------------------------*/
/* function to calculate two values      */
/*---------------------------------------*/

int calculator(char *operator_t, int operator1, int operator2) {

    int resultat;

    if (*operator_t == '+') {
        resultat = operator1 + operator2;
    } else if (*operator_t == '-') {
        resultat = operator1 - operator2;
    } else if (*operator_t == '*') {
        resultat = operator1 * operator2;
    } else if (*operator_t == '/') {
        resultat = operator1 / operator2;
    }
    return resultat;
}

/*---------------------------------------*/
/* function to convert String to integer */
/*---------------------------------------*/

int strToint(char str[]) {
    int i = 0, sum = 0;
    while (str[i] != '\0') {
        if (str[i] < 48 || str[i] > 57) {
            printf("\n\nFirst operator is a negative value ==> ");
        } else {
            sum = sum * 10 + (str[i] - 48);
        }
        i++;
    }
    return sum;
}

