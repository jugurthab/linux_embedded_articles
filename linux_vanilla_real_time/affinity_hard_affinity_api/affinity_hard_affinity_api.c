#define _GNU_SOURCE
// getAffinityReturnValue() et set_process_affinity()
// sont des extensions GNU.
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

cpu_set_t cpuSet; // stocker l'affinité du processus.

void get_process_affinity(){
    int i = 0;
    // Remise à zéro avant lecture de l'affinité.
    CPU_ZERO(&cpuSet);

    // sched_getaffinity retourne l'affinité d'un processus
    // 0 : représente le processus en cours.
    if(sched_getaffinity(0,
                sizeof(cpu_set_t), &cpuSet) == -1){
        perror("sched_getaffinity");
    }

    // Affichage de l'affinité.
    for(i = 0; i < CPU_SETSIZE; i++) {
        int isCPUSet = CPU_ISSET(i, &cpuSet);
        if(isCPUSet){
            printf("CPU[%d] is set for this process\n", i);
        }
    }
    printf("-------------------------------------\n");
}

void set_process_affinity(){
    /*
    *  Remise à zéro de l'affinité.
    */
    CPU_ZERO(&cpuSet);
    // Autoriser l'affinité sur les CPU1 et CPU2.
    CPU_SET(0, &cpuSet);
    CPU_SET(1, &cpuSet);

    /* Interdire explicitement l'affinité sur les CPU3 et CPU4.
    *  (CPU_ZERO() interdit tout les CPU).
    */
    CPU_CLR(2, &cpuSet);

    // Appliquer les nouvelles régles d'affinité.
    if( sched_setaffinity(0,
           sizeof(cpu_set_t), &cpuSet) == -1 ){
        perror("sched_setaffinity");
    } else {
        printf("-------------------------------------\n");
        printf("--- CPU Affinity has been changed ---\n");
        printf("-------------------------------------\n");
    }
}

int main(int argc, char *argv[]){
    get_process_affinity(); // Lecture de l'affinité initiale.

    // Forcer l'affinité sur le CPU0 et CPU1.
    set_process_affinity();

    get_process_affinity(); // Relecture de l'affinité.

    return EXIT_SUCCESS;
}

