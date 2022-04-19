//
// Created by kacper on 14.03.2022.
//

#ifndef SDIZO_PROJECT_1_TIME_MEASUREMENT_HPP
#define SDIZO_PROJECT_1_TIME_MEASUREMENT_HPP
#define MILLISECONDS 1000.0
#define MICROSECONDS 1000000.0
#define NANOSECONDS 1000000000.0


#include <windows.h>
#include <iostream>


class TimeMeasurement {
public:
    void startCounting() {
        reset();
        if (!QueryPerformanceFrequency(&li)) {
            std::cout << "QueryPerformanceFrequency failed!\n";
        }

        PCFreq = double(li.QuadPart) / NANOSECONDS;

        QueryPerformanceCounter(&li);
        CounterStart = li.QuadPart;
    }

    double getTime() {
        QueryPerformanceCounter(&li);
        return double(li.QuadPart - CounterStart) / PCFreq;
    }

private:
    double PCFreq = 0.0;
    __int64 CounterStart = 0;
    LARGE_INTEGER li{};

    void reset() {
        PCFreq = 0.0;
        CounterStart = 0;
    }
};


#endif //SDIZO_PROJECT_1_TIME_MEASUREMENT_HPP