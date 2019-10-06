#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DEFAULT_MAX_NUMBER_LIMIT 1000
#define MAX_PASSWORD_LENGTH 20

int getPseudoNumber(int numLimit);

/* generationMotDePasse has a local symbol */
char *generationMotDePasse(int nbCharacters);

/* generationMotDePasse has a global symbol (exported to client binary) */
char* getRandomPassword(int nbCharacters);
