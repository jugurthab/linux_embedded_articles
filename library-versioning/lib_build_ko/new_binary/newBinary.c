#include <stdio.h>
#include "timemgr.h"

int main(){
 
    printf ("La date : %s\n", getCurrentTimestamp());
    
    // Used to compare timestamp with old binary
    printf("Le timestamp : %ld\n", time(NULL));

    return 0;
}

