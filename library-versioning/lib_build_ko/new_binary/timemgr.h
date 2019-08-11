#include <time.h>

/* return current time in string format */
char * getCurrentTimestamp();
/* Get Linux specific clock resolution */
struct timespec getClockPrecision();
