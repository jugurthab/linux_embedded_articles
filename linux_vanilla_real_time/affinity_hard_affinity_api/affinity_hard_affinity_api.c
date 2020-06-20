// getAffinityReturnValue() and set_process_affinity()
// are GNU extensions.
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

cpu_set_t cpuSet; // Store current process affinity.

void get_process_affinity(){
    int getAffinityReturnValue, i;

    CPU_ZERO(&cpuSet); // Empty cpuSet from previous usage.

    // Retrieve affinity for current process
    getAffinityReturnValue = sched_getaffinity(0,
                              sizeof(cpu_set_t), &cpuSet);

    if(getAffinityReturnValue == -1){
        perror("sched_getaffinity");
    }

    // List CPUs on which current process is allowed to run.
    for(i = 0; i < CPU_SETSIZE; i++) {
        int isCPUSet = CPU_ISSET(i, &cpuSet);
        if(isCPUSet){
            printf("CPU[%d] is set for this process\n", i);
        }
    }
    printf("-------------------------------------\n");
}

void set_process_affinity(){
    int setAffinityReturnValue;

    /*
    *  clears all CPUs (by default, it disallow
    *  affinity on all CPUs).
    */
    CPU_ZERO(&cpuSet);
    /* Allow process to run on
    CPU0 and CPU1 */
    CPU_SET(0, &cpuSet);
    CPU_SET(1, &cpuSet);

    /* Disallow explicitly process to run on CPU2.
    *  Because CPU_ZERO() already disallowed it by default.
    */
    CPU_CLR(2, &cpuSet);

    setAffinityReturnValue = sched_setaffinity(0,
                                sizeof(cpu_set_t), &cpuSet);
    if(setAffinityReturnValue == -1){
        perror("sched_setaffinity");
    }
    printf("-------------------------------------\n");
    printf("--- CPU Affinity has been changed ---\n");
    printf("-------------------------------------\n");
}

int main(int argc, char *argv[]){
    get_process_affinity(); // Reads intial affinity

    set_process_affinity(); // Changes affinity to CPU0 and CPU1

    get_process_affinity(); // Reads new affinity

    return EXIT_SUCCESS;
}

