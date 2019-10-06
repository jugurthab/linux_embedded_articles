#include "usrmgr.h"

/* Retourne la liste des utilisateurs connectés */
void getLoggedUsers(){
    struct utmpx *utmpUser;

    setutxent(); // Ouverture du fichier /var/run/utmp

    /* Parcours de la liste des utilisateurs */
    while ((utmpUser = getutxent()) != NULL) {
        printf("Utilisateur : %s <=> PID : %ld at : %s", utmpUser->ut_user,
         (long) utmpUser->ut_pid, ctime((time_t *) &(utmpUser->ut_tv.tv_sec)));
    }
}

