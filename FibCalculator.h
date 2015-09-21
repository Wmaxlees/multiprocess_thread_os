//
// Created by William Lees on 9/18/15.
//

#ifndef OSPROJ1_FIBCALCULATOR_H
#define OSPROJ1_FIBCALCULATOR_H

#include <pthread.h>

#define     MAX_FIB_CALCULABLE      1500

class FibCalculator {
public:
    double calculateFibIndex(short i);

    const char* toString();

private:
    static double              fib[MAX_FIB_CALCULABLE];
    static pthread_mutex_t     mutex[MAX_FIB_CALCULABLE];

    void static *threadedFibCalculator(void* i);
};

#endif //OSPROJ1_FIBCALCULATOR_H
