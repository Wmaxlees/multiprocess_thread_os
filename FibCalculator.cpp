//
// Created by William Lees on 9/18/15.
//

#include <iostream>
#include <string>

#include "FibCalculator.h"

double FibCalculator::fib[1500] = { [0 ... 1499] = -1.0};
pthread_mutex_t FibCalculator::mutex[1500] = {};

bool equalDouble(double, double);

double FibCalculator::calculateFibIndex(short i) {
    double result = -1.0;

    // Check that request isn't out of range
    if (i > MAX_FIB_CALCULABLE) {
        result = -1.0;
    } else if (i == 0) {
        result = 0.0;
    } else if (i == 1) {
        result = 1.0;
    } else

    // Calculate otherwise
    if (fib[i] == -1.0){
        short n_1 = i-1, n_2 = i-2;
        pthread_t thread_one, thread_two;
        pthread_create(&thread_one, NULL, threadedFibCalculator, (void*)&n_1);
        pthread_create(&thread_two, NULL, threadedFibCalculator, (void*)&n_2);

        pthread_join(thread_one, NULL);
        pthread_join(thread_two, NULL);

        // std::cout << fib[i-1] << " + " << fib[i-2];
        result = fib[i-1] + fib[i-2];
    }

    return result;
}

const char *FibCalculator::toString() {
    std::string result = "";
    for (int i = 0; i < MAX_FIB_CALCULABLE; ++i) {
        if (this->fib[i] != -1.0) {
            result += "Fib(";
            result += std::to_string(i);
            result += ")=";
            result += std::to_string(this->fib[i]);
            result += "\n";
        }
    }

    return result.c_str();
}

void *FibCalculator::threadedFibCalculator(void* i) {
    // Base cases
    if (*(short*)i == 0) {
        pthread_mutex_lock(&mutex[*(short*)i]);
        fib[*(short*)i] = 0.0;
        pthread_mutex_unlock(&mutex[*(short*)i]);

        // std::cout << 0.0 << std::endl;
    } else if (*(short*)i == 1) {
        pthread_mutex_lock(&mutex[*(short*)i]);
        fib[*(short*)i] = 1.0;
        pthread_mutex_unlock(&mutex[*(short*)i]);

        // std::cout << 1.0 << std::endl;
    } else
    // Calculate otherwise
    if (equalDouble(fib[*(short*)i], -1.0)) {
        pthread_mutex_lock(&mutex[*(short*)i]);
        // std::cout << *(short*)i << std::endl;

        short n_1 = *(short*)i-1, n_2 = *(short*)i-2;
        pthread_t thread_one, thread_two;
        pthread_create(&thread_one, NULL, threadedFibCalculator, (void*)&n_1);
        pthread_create(&thread_two, NULL, threadedFibCalculator, (void*)&n_2);

        pthread_join(thread_one, NULL);
        pthread_join(thread_two, NULL);

        double value = fib[*(short*)i-1] + fib[*(short*)i-2];

        // std::cout << value << std::endl;
        fib[*(short*)i] = value;
        pthread_mutex_unlock(&mutex[*(short*)i]);
    }

    pthread_exit(NULL);
}

#define         EPSILON         0.9

bool equalDouble(double lvalue, double rvalue) {
    double testValue = lvalue - rvalue;
    if (testValue < 0) {
        testValue = -testValue;
    }

    if (testValue < EPSILON){
        return true;
    }

    return false;
}