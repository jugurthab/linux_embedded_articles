#include <time.h>
#include <sys/time.h>

/* return current time in seconds since Linux epoch */
long getCurrentTimestamp();
/* Get Linux specific clock resolution */
struct timespec getClockPrecision();
