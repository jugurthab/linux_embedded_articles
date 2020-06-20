#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> // Required by
#include <sys/resource.h> // setpriority() and getpriority()
#include <errno.h>

int process_nice_value; // Store current nice value

void display_process_nice_value(){
    // Get current process priority.
    process_nice_value = getpriority(PRIO_PROCESS, 0);

    printf ("Current process priority : %d\n", process_nice_value);
}

int main(int argc, char *argv[]){
    
    display_process_nice_value();

    // Set current process priority.
    process_nice_value = setpriority(PRIO_PROCESS, 0, -10);

    if(process_nice_value == -1){
        perror ("setpriority error");
    }

    display_process_nice_value();

    return EXIT_SUCCESS;
}

