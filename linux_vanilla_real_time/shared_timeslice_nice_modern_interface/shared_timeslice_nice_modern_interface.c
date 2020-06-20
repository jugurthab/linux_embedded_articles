#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h> // inclure setpriority(), getpriority()
#include <errno.h>

int process_nice_value = 0;

void display_process_nice_value(char *stepName){
    // Get current process priority.
    process_nice_value = getpriority(PRIO_PROCESS, 0);
    printf ("%s process priority : %d\n", stepName, process_nice_value);
}

int main(int argc, char *argv[]){
    
    display_process_nice_value("Previous");

    /* setpriority modifie la priorité dynamique
    * d'un processus s'exécutant en politique temps partagée.
    * PRIO_PROCESS et 0 : appliquer sur le processus en cours.
    * -10 : nouvelle valeur de nice.
    */
    process_nice_value = setpriority(PRIO_PROCESS, 0, -10);
    
    // Il est recommandé d'ajouter la vérification de errno.
    if(process_nice_value == -1){
        perror ("setpriority error");
    } else {
        printf("------- Nice Updated --------\n");
    }

    display_process_nice_value("Current");

    return EXIT_SUCCESS;
}

