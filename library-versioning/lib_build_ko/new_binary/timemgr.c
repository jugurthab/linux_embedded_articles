#include "timemgr.h"

char * getCurrentTimestamp(){
    time_t curTime;
    time(&curTime);

    return (ctime(&curTime));
}

struct timespec getClockPrecision(clockid_t clockId){
    struct timespec clockResolution;
    /* Gets clock precision */
    clock_getres(clockId, &clockResolution);    

    return clockResolution;
}
