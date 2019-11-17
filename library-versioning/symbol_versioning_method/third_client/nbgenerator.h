#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <crypt.h>

#define DEFAULT_MAX_NUMBER_LIMIT 1000
#define MAX_PASSWORD_LENGTH 20
#define ENCRYPTION_CIPHER_METHOD "crypt"

struct PasswordHash{
    char hashNameFunc[20];
    char* passwordToHash;
    char* hashedPassword;
} passHash;

int getPseudoNumber(int numLimit);
char *generationMotDePasse(int nbCharacters);

/* LIB_NBGENERATOR_VERSION_2_0 : Constant to be passed at compilation time */
/* Because only one header is allowed in case of same function signature */
#ifdef LIB_NBGENERATOR_VERSION_2_0
struct PasswordHash getRandomPassword(int nbCharacters);
#else
char* getRandomPassword(int nbCharacters);
#endif
