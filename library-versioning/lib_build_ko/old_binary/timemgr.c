#include "timemgr.h"

long getCurrentTimestamp(){
    return ((long) time(NULL));
}

struct timespec getClockPrecision(clockid_t clockId){
    struct timespec clockResolution;
    /* Gets clock precision */
    clock_getres(clockId, &clockResolution);    

    return clockResolution;
}
