#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sched.h>
#include <errno.h>

void display_process_sched_attributes(){
    int scheduler_policy = -1;

    // Retourne la politique d'ordonnacement du procesus
    // en cours.
    scheduler_policy = sched_getscheduler(0);

    printf("Current scheduling policy : ");
    
    switch(scheduler_policy){
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
        break;

        case SCHED_BATCH:
            printf("SCHED_BATCH\n");
        break;

        case SCHED_IDLE:
            printf("SCHED_IDLE\n");
        break;
          
        case -1:
            perror("sched_getscheduler error");    
        break; 
            /*
            * Il en existe 2 autres politiques (SCHED_FIFO
            * et SCHED_RR) réservées au temps réel.
            */
        default:
            printf("Unknown\n");
        break;
    }

}

int main(int argc, char *argv[]){
    int t;
    struct sched_param sched_p;
    // Affiche la politique d'ordonnancement.
    display_process_sched_attributes();

    sched_p.sched_priority = 0; // N'est pas prise en compte
                                // dans le temps partagé
    /*
    * sched_setscheduler change la politique d'ordonnancement.
    * 1er param : PID du processus (0 pour processus en cours).
    * 2ème param : type de politique d'ordonnancement
    * 3ème param : paramètre d'ordonnancement.
    */ 
    if(sched_setscheduler(0, SCHED_BATCH, &sched_p) == -1)
        perror ("sched_setscheduler ");

    display_process_sched_attributes();

    return EXIT_SUCCESS;
}

