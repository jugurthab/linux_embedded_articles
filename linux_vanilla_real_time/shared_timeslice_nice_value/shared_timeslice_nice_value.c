#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Required by nice().
#include <errno.h>

int main(int argc, char *argv[]){
    int nice_value = -1; // Stores process nice value.

    /*
    * It is enough to pass 0 as nice value
    * increment to get current nice value. 
    */
    nice_value = nice(0);

    printf ("--- Initial nice value %d ---\n", nice_value);

    /*
    * One can passe a value!=0 to nice in order to change process niceness.
    * When setting nice with value!=0, errno variable must be
    * Checked as -1 is also a valid return value from nice.
    */
    errno = 0;
    // Increase process nice value (decrease dynamic priority).
    nice_value = nice(5);
    
    if(nice_value == -1 && errno != 0){
        perror ("nice error");
    } else {
        printf ("--- New nice value is : %d --\n", nice_value);
    }

    return EXIT_SUCCESS;
}

