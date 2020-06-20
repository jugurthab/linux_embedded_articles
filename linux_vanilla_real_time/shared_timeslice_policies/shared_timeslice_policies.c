#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sched.h>

void display_process_sched_attributes(){
    int scheduler_policy = -1; // Stores scheduler policy.

    // Returns current process scheduler.
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
            * Actually there 2 other policies (SCHED_FIFO
            * and SCHED_RR) but are reserved for realtime.
            */
        default:
            printf("Unknown\n");
        break;
    }

}

int main(int argc, char *argv[]){

    display_process_sched_attributes();

    /*
    * sched_setscheduler can be used to change process scheduling policy.
    * Argument param is not needed for timeshared processes (pass NULL).
    */
    sched_setscheduler(0, SCHED_BATCH, NULL);    

    display_process_sched_attributes();

    return EXIT_SUCCESS;
}

