#include <time.h>
#include <sys/time.h>

/* return current time in microseconds since Linux epoch */
struct timeval getCurrentTimestampU();
/* Get Linux specific clock resolution */
struct timespec getClockPrecision();
