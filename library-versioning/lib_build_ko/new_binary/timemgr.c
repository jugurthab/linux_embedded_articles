#include "timemgr.h"

struct timeval getCurrentTimestampU(){
    struct timeval tsMicroSec;
    
    gettimeofday(&tsMicroSec, NULL);

    return tsMicroSec;
}

struct timespec getClockPrecision(clockid_t clockId){
    struct timespec clockResolution;
    /* Gets clock precision */
    clock_getres(clockId, &clockResolution);    

    return clockResolution;
}
