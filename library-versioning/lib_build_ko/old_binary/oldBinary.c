#include <stdio.h>
#include "timemgr.h"

int main(){
    struct timespec clockRes;

    clockRes = getClockPrecision(CLOCK_REALTIME);

    printf("Timestamp %ld\n", getCurrentTimestamp());
    printf("Clock Resolution sec=%ld nsec=%ld\n",
            clockRes.tv_sec, clockRes.tv_nsec);

    return 0;
}

