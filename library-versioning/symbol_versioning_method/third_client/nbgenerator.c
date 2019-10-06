#include "nbgenerator.h"

char password[MAX_PASSWORD_LENGTH] = {0};

int getPseudoNumber(int numLimit){
    int rNumber = 0;
    srand(time(NULL));
    if(numLimit > 0)
        rNumber = rand() % numLimit;
    else
        rNumber = rand() % DEFAULT_MAX_NUMBER_LIMIT;
    return rNumber;
}

// generationMotDePasse : not exported to client binary
char *generationMotDePasse(int nbCharacters){
    short i = 0;
    memset(password, 0, MAX_PASSWORD_LENGTH);
    
    srand(time(NULL));
    
    if((nbCharacters > MAX_PASSWORD_LENGTH) || (nbCharacters <= 0))
        nbCharacters = MAX_PASSWORD_LENGTH;
    /* Génération du mot de passe */
    for(i = 0; i< nbCharacters; i++){
        password[i] = 'A' + (rand() % nbCharacters);
    }
    return password;
}

/* @ means use this for legacy (old binaries) */
__asm__(".symver getRandomPassword_1_1,getRandomPassword@NBGENERATOR_1.1");
char* getRandomPassword_1_1(int nbCharacters){
    return generationMotDePasse(nbCharacters);
}

/* @@ means default use this for new binaries */
__asm__(".symver getRandomPassword_2_0,getRandomPassword@@NBGENERATOR_2.0");
struct PasswordHash getRandomPassword_2_0(int nbCharacters){
    char *passwordToHash = generationMotDePasse(10);
    char *passwordSalt = generationMotDePasse(3);
    
    sprintf(passHash.hashNameFunc, "%s", "crypt");
    passHash.passwordToHash = passwordToHash;            
    
    /* Crypt returns a hash based on DES encryption */
    passHash.hashedPassword = crypt(passwordToHash, passwordSalt);

    return passHash;
}
