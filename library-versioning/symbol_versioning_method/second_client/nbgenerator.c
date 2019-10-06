#include "nbgenerator.h"

char password[MAX_PASSWORD_LENGTH] = {0};
// getPseudoNumber : exported to client binary
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
// getRandomPassword : exported to client binary
char* getRandomPassword(int nbCharacters){
    return generationMotDePasse(nbCharacters);
}
