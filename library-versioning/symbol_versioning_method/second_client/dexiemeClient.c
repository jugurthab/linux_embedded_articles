#include <stdio.h>
#include "nbgenerator.h"

int main(){
    printf("Le nombre aléatoire est %d\n", getPseudoNumber(1500));
    printf("Le mot de passe : %s\n", getRandomPassword(10));
    return 0;
}

