#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <sys/time.h>

#define NB_THREADS 3

pthread_attr_t attr[NB_THREADS]; // Store threads attributes.
pthread_t t_tid[NB_THREADS]; // Store thread PIDs
int threadPriorities[NB_THREADS] = {20, 0, 20};

void * displayThreadInformations(void * argument){
    int i=0;
    int scheduler_policy = -1; // Stores scheduler policy.
    int threadNumber = (int) argument; // Retrive thread number.
    struct sched_param param;
    
    for(i=0; i<80000000; i++);
    // Get thread static priority.
    pthread_attr_getschedparam(&attr[threadNumber], &param);
    printf("Thread [%d] has priority : %d\n", threadNumber,
                                              param.sched_priority);
    
    // Get thread scheduling policy
    pthread_attr_getschedpolicy(&attr[threadNumber], &scheduler_policy);
    
    switch(scheduler_policy){
        case SCHED_OTHER:
            printf("Thread [%d] is under policy : SCHED_OTHER policy\n",
                    threadNumber);
        break;

        case SCHED_FIFO:
            printf("Thread [%d] is under policy : SCHED_FIFO policy\n",
                    threadNumber);
        break;

        case SCHED_RR:
            printf("Thread [%d] is under policy : SCHED_RR policy\n",
                    threadNumber);
        break;
          
        case -1:
            perror("sched_getscheduler error");    
        break; 

        default:
            printf("Unknown\n");
        break;
    }
}

int main(int argc, char *argv[]){
    struct sched_param sp;

    int i;
    
    struct sched_param thrad_param; // holds threads static priorities

    for(i = 0; i < NB_THREADS; i++){
        // Initialize thread attribute structure
        pthread_attr_init(&attr[i]);
        if(i!=1){
            // Set thread policy to SCHED_FIFO
            if (pthread_attr_setschedpolicy(&attr[i], SCHED_FIFO) != 0) {
                perror("pthread_attr_setschedpolicy");
                exit(EXIT_FAILURE);
            }
            // Set thread static priority
            
            thrad_param.sched_priority = threadPriorities[i];
            if (pthread_attr_setschedparam(&attr[i], &thrad_param) != 0) {
                perror("pthread_attr_setschedparam");
                exit(EXIT_FAILURE);
            }
        
        /*
        * By default, threads are created with same static priority as
        * master thread (even if pthread_attr_setschedparam was called).
        * pthread_attr_setinheritsched enforces thread creation to take
        * into account pthread_attr_setinheritsched.
        */
        
            if (pthread_attr_setinheritsched(&attr[i], PTHREAD_EXPLICIT_SCHED) != 0) {
                perror("pthread_attr_setinheritsched");
                exit(EXIT_FAILURE);
            }
        }
    }

    for (i = 0; i < NB_THREADS; i ++){
        // Create threads
        if (pthread_create(&t_tid[i], &attr[i], displayThreadInformations, (void *) (i)) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }     
       pthread_join(t_tid[i], NULL);
    }

    for (i = 0; i < NB_THREADS; i ++){
       pthread_join(t_tid[i], NULL);
    }

    return EXIT_SUCCESS;
}

