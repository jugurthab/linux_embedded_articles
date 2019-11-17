#include <stdio.h>
#include "nbgenerator.h"

int main(){
    struct PasswordHash pass = getRandomPassword(10);
    printf("Le nombre aléatoire est %d\n", getPseudoNumber(1500));
    printf("Le mot de passe avec hash : %s obtenu avec la fonction => %s\n",
            pass.hashedPassword, pass.hashNameFunc);

    return 0;
}

