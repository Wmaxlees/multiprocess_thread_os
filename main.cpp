#include <iostream>
#include <chrono>

#include "FibCalculator.h"

int main() {
    // List of fib number memoization
    short index;

    std::cout << "Calculate Fibonacci index: ";
    std::cin >> index;

    auto startTime = std::chrono::high_resolution_clock::now();

    FibCalculator fibCalculator;
    fibCalculator.calculateFibIndex(index+1);

    auto endTime = std::chrono::high_resolution_clock::now();

    std::cout << "\n" << fibCalculator.toString() << std::endl;

    std::cout << "\nElapsed Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime-startTime).count()/1000000 << " ms";

    return 0;
}

