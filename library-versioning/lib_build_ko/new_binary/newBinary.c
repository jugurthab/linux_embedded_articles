#include <stdio.h>
#include "timemgr.h"

int main(){
    struct timespec clockRes;
    struct timeval tsMicroSec;

    clockRes = getClockPrecision(CLOCK_REALTIME);
    tsMicroSec = getCurrentTimestampU();

    printf("Timestamp sec=%ld, usec=%ld\n", (long)tsMicroSec.tv_sec,
            (long)tsMicroSec.tv_usec);
    printf("Clock Resolution sec=%ld nsec=%ld\n",
            (long)clockRes.tv_sec, (long)clockRes.tv_nsec);

    return 0;
}

