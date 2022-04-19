//
// Created by kacper on 05.04.2022.
//

#ifndef SDIZO_PROJECT_1_TESTS_H
#define SDIZO_PROJECT_1_TESTS_H

#include <list>
#include "TimeMeasurement.hpp"
#include "IDGen.hpp"
#include "../Enums.h"

struct OpResult {
    double time;
    std::string opName;
    std::string structure;
};

class Tests {
public:
    size_t sampleSize = 1000;
    size_t structureSize = 1000;
    int minElement = 0;
    int maxElement = 100;
    TimeMeasurement watch;
    std::list<OpResult> results;

    static double calcAvg(const std::list<double> &);

    void addOpAvg(double avg, std::string opName, std::string structureName);

    void testOperation(IDGen &idg, ArrayOp operation);

    void testOperation(IDGen &idg, ListOp operation);

    void testOperation(IDGen &idg, HeapOp operation, HeapTp type);

    void testOperation(IDGen &idg, TreeOp operation);

    void DArray(IDGen &idg);

    void DLList(IDGen &idg);

    void Heap(IDGen &idg);

    void RBTree(IDGen &idg);

    void performTests();

    void printResults();

    void saveResult(const std::string &structureName);
};


#endif //SDIZO_PROJECT_1_TESTS_H