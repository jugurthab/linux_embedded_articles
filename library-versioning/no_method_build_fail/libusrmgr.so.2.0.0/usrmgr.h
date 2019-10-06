#include <stdio.h>
#include <stdlib.h>
#include <utmpx.h>
#include <time.h>
#include <string.h>

#define HIDDEN_USER "Pierre"

/* Affiche et retourne le nombre des utilisateurs connectés */
int getLoggedUsers(char filterUser[]);

