#include <chrono>
#include "SDiZO.h"



int main() {
/*
    auto testStart = std::chrono::system_clock::now();
    Tests test;
    test.maxElement = 10000;
    test.minElement = -10000;
    test.sampleSize = 100;


    for(int structureSize = 1000; structureSize <= 10000; structureSize += 1000){
        test.structureSize = structureSize;
        test.performTests();
        std::cout << "Finished with " << structureSize << " sample size\n\n";
    }

    auto testEnd = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = testEnd - testStart;

    std::cout << "Finished testing -> " << elapsedTime.count()/double(60) << " [min]\n";
*/
    Menu::initMenu();

    return 0;
}