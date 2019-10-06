#include "nbgenerator.h"

int getPseudoNumber(int numLimit){
    int rNumber = 0;
    srand(time(NULL));
    if(numLimit > 0)
        rNumber = rand() % numLimit;
    else
        rNumber = rand() % DEFAULT_MAX_NUMBER_LIMIT;
    return rNumber;
}
