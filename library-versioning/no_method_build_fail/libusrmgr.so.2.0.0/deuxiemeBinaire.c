#include "usrmgr.h"

int main(){
    printf("La liste des utilisateurs connectés : \n");
    getLoggedUsers("");

    printf("\nFiltrer sur l'utilisateur 'jugurtha' : \n");
    getLoggedUsers("jugurtha");

    return EXIT_SUCCESS;
}

