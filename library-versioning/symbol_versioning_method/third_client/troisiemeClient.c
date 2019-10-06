#include <stdio.h>
#include "nbgenerator.h"

int main(){
    struct PasswordHash pass = getRandomPassword(10);
    printf("Le nombre aléatoire est %d\n", getPseudoNumber(1500));
    printf("Le hash de %s  avec la fonction %s : %s \n",
            pass.passwordToHash, pass.hashNameFunc, pass.hashedPassword);

    return 0;
}

