#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sched.h>
#include <time.h>
#include <errno.h>

void incrementCounter(char *stepName){
    long long int counterLoop = 0;
    time_t counterStat;
    time(&counterStat);
    // Incrémenter le compteur quand le processus s'exécute
    // sur le CPU.
    while(time(NULL) < (counterStat+200)){
        counterLoop++;
    }
    printf("[%s] => Counter value : %lli\n",
                                stepName, counterLoop);
}

int main(int argc, char *argv[]){
    struct sched_param sched_p;

    incrementCounter("SCHED_OTHER");
    // Création d'un processus temps réel
    // (priorité statique 70) avec une politique FIFO.
    sched_p.sched_priority = 70;
    if(sched_setscheduler(0, SCHED_FIFO, &sched_p) == -1)
        perror ("sched_setscheduler ");
    else
        printf("------ Scheduling policy updated ------\n");

    incrementCounter("SCHED_FIFO ");

    return EXIT_SUCCESS;
}

