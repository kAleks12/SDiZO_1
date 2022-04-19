//
// Created by kacper on 05.04.2022.
//

#include <chrono>
#include <utility>
#include <io.h>
#include <vector>
#include "Tests.h"
#include "../Structures/List/DoublyLinkedList.hpp"
#include "../Structures/Heap/BinaryHeap.hpp"
#include "../Structures/Tree/RedBlackTree.hpp"

double Tests::calcAvg(const std::list<double> &dataStr) {
    double avg = 0;

    //Calculating average from provided vector's elements
    for (double result: dataStr) {
        avg += result;
    }
    avg /= double(dataStr.size());

    return avg;
}

void Tests::addOpAvg(double avg, std::string opName, std::string structureName) {
    OpResult result;

    //Creating result object for specific structure and operation
    result.time = avg;
    result.opName = std::move(opName);
    result.structure = std::move(structureName);

    //Adding created object to vector with all operations' results
    results.push_back(result);
}

void Tests::performTests() {
    //Creating src file generator
    IDGen idg;


    //Performing tests for each structure
    mkdir("Array");
    DArray(idg);
    saveResult("Array");
    results.clear();

    mkdir("List");
    DLList(idg);
    saveResult("List");
    results.clear();

    mkdir("Heap");
    Heap(idg);
    saveResult("Heap");
    results.clear();

    mkdir("Tree");
    RBTree(idg);
    saveResult("Tree");
    results.clear();
}


void Tests::DArray(IDGen &idg) {
    //Testing each possible operation
    testOperation(idg, ArrayOp::addf);
    testOperation(idg, ArrayOp::addb);
    testOperation(idg, ArrayOp::add);
    testOperation(idg, ArrayOp::rmf);
    testOperation(idg, ArrayOp::rmb);
    testOperation(idg, ArrayOp::rm);
    testOperation(idg, ArrayOp::find);

    std::cout << "\n\n";
}

void Tests::DLList(IDGen &idg) {
    //Testing each possible operation
    testOperation(idg, ListOp::addf);
    testOperation(idg, ListOp::addb);
    testOperation(idg, ListOp::add);
    testOperation(idg, ListOp::rmf);
    testOperation(idg, ListOp::rmb);
    testOperation(idg, ListOp::rm);
    testOperation(idg, ListOp::find);

    std::cout << "\n\n";
}

void Tests::Heap(IDGen &idg) {
    //Testing each possible operation for both min and max heap
    testOperation(idg, HeapOp::add, HeapTp::max);
    testOperation(idg, HeapOp::rmr, HeapTp::max);
    testOperation(idg, HeapOp::rm, HeapTp::max);
    testOperation(idg, HeapOp::find, HeapTp::max);

    std::cout << "\n\n";
}

void Tests::RBTree(IDGen &idg) {
    //Testing each possible operation for both min and max heap
    testOperation(idg, TreeOp::add);
    testOperation(idg, TreeOp::rm);
    testOperation(idg, TreeOp::find);

    std::cout << "\n\n";
}


void Tests::testOperation(IDGen &idg, ArrayOp operation) {
    //Creating list for individual operation execution times
    std::list<double> intervals;

    //Marking start of testing operation
    auto start = std::chrono::system_clock::now();

    int position;
    int value;
    double time;


    //Performing specific operation sampleSize times for specified structureSize array
    for (int j = 0; j <= sampleSize; j++) {
        //Creating list with generated structure elements
        std::list <int> dataSet = idg.generateDataSet(structureSize, minElement, maxElement);

        //Creating new array from list
        DynamicArray<int> array(dataSet);

        //Generating value from [minElement, maxElement]
        value = IDGen::getInt(minElement, maxElement);

        //Performing operation, measuring its execution time and adding it (time) to intervals vector
        switch (operation) {
            case ArrayOp::addf:
                watch.startCounting();
                array.addFront(value);
                time = watch.getTime();
                intervals.push_back(time);
                break;

            case ArrayOp::addb:
                watch.startCounting();
                array.addBack(value);
                time = watch.getTime();
                intervals.push_back(time);
                break;

            case ArrayOp::add:
                position = IDGen::getInt(0, int(structureSize - 1));

                watch.startCounting();
                array.add(value, position);
                time = watch.getTime();
                intervals.push_back(time);
                break;
            case ArrayOp::rmf:
                watch.startCounting();
                array.removeFront();
                time = watch.getTime();
                intervals.push_back(time);
                break;
            case ArrayOp::rmb:
                watch.startCounting();
                array.removeBack();
                time = watch.getTime();
                intervals.push_back(time);
                break;
            case ArrayOp::rm:
                position = IDGen::getInt(0, int(structureSize - 1));

                watch.startCounting();
                array.remove(position);
                time = watch.getTime();
                intervals.push_back(time);
                break;

            case ArrayOp::find:
                watch.startCounting();
                array.find(value);
                time = watch.getTime();
                intervals.push_back(time);
                break;

            default:
                break;
        }
    }


    //Calculating avg time for operation, creating opResult object and adding it to results vector
    switch (operation) {
        case ArrayOp::addf:
            addOpAvg(calcAvg(intervals), "addFront", "DArray");
            break;

        case ArrayOp::addb:
            addOpAvg(calcAvg(intervals), "addBack", "DArray");

            break;

        case ArrayOp::add:
            addOpAvg(calcAvg(intervals), "add", "DArray");
            break;
        case ArrayOp::rmf:
            addOpAvg(calcAvg(intervals), "removeFront", "DArray");
            break;

        case ArrayOp::rmb:
            addOpAvg(calcAvg(intervals), "removeBack", "DArray");

            break;

        case ArrayOp::rm:
            addOpAvg(calcAvg(intervals), "remove", "DArray");
            break;

        case ArrayOp::find:
            addOpAvg(calcAvg(intervals), "find", "DArray");
            break;

        default:
            break;
    }
    intervals.resize(0);

    //Marking end time of testing operation
    auto end = std::chrono::system_clock::now();

    //Calculating time needed to test operation
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "Finished operation for DArray -> " << elapsed_seconds.count() << " [s]\n";
}

void Tests::testOperation(IDGen &idg, ListOp operation) {
    //Creating list for individual operation execution times
    std::list<double> intervals;

    //Marking start of testing operation
    auto start = std::chrono::system_clock::now();

    int position;
    int value;
    double time;

    //Performing specific operation sampleSize times for specified structureSize list
    for (int j = 0; j <= sampleSize; j++) {
        //Creating list with generated structure elements
        std::list <int> dataSet = idg.generateDataSet(structureSize, minElement, maxElement);

        //Creating new list from list
        DoublyLinkedList<int> list(dataSet);


        //Generating value from [minElement, maxElement]
        value = IDGen::getInt(minElement, maxElement);

        //Performing operation, measuring its execution time and adding it (time) to intervals vector
        switch (operation) {
            case ListOp::addf:
                watch.startCounting();
                list.addFront(value);
                time = watch.getTime();
                intervals.push_back(time);
                break;

            case ListOp::addb:
                watch.startCounting();
                list.addBack(value);
                time = watch.getTime();
                intervals.push_back(time);
                break;

            case ListOp::add:
                position = IDGen::getInt(0, int(structureSize - 1));

                watch.startCounting();
                list.add(value, position);
                time = watch.getTime();
                intervals.push_back(time);
                break;

            case ListOp::rmf:
                watch.startCounting();
                list.removeFront();
                time = watch.getTime();
                intervals.push_back(time);
                break;

            case ListOp::rmb:
                watch.startCounting();
                list.removeBack();
                time = watch.getTime();
                intervals.push_back(time);
                break;

            case ListOp::rm:
                position = IDGen::getInt(0, int(structureSize - 1));

                watch.startCounting();
                list.remove(position);
                time = watch.getTime();
                intervals.push_back(time);
                break;

            case ListOp::find:
                watch.startCounting();
                list.find(value);
                time = watch.getTime();
                intervals.push_back(time);
                break;

            default:
                break;
        }
    }

    //Calculating avg time for operation, creating opResult object and adding it to results vector
    switch (operation) {
        case ListOp::addf:
            addOpAvg(calcAvg(intervals), "addFront", "DLList");
            break;

        case ListOp::addb:
            addOpAvg(calcAvg(intervals), "addBack", "DLList");
            break;

        case ListOp::add:
            addOpAvg(calcAvg(intervals), "add", "DLList");
            break;
        case ListOp::rmf:
            addOpAvg(calcAvg(intervals), "removeFront", "DLList");
            break;

        case ListOp::rmb:
            addOpAvg(calcAvg(intervals), "removeBack", "DLList");
            break;

        case ListOp::rm:
            addOpAvg(calcAvg(intervals), "remove", "DLList");
            break;

        case ListOp::find:
            addOpAvg(calcAvg(intervals), "find", "DLList");
            break;


        default:
            break;
    }
    intervals.resize(0);

    //Marking end time of testing operation
    auto end = std::chrono::system_clock::now();

    //Calculating time needed to test operation
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "Finished operation for DLList -> " << elapsed_seconds.count() << " [s]\n";
}

void Tests::testOperation(IDGen &idg, HeapOp operation, HeapTp type) {
    //Creating vectors for individual operation execution times
    std::list<double> intervals;

    //Marking start of testing operation
    auto start = std::chrono::system_clock::now();

    int position;
    int value;
    double time;

    //Performing specific operation sampleSize times for specified structureSize  and heap type heap
    for (int j = 0; j <= sampleSize; j++) {
        //Creating list with generated structure elements
        std::list <int> dataSet = idg.generateDataSet(structureSize, minElement, maxElement);

        //Creating new heap from list
        BinaryHeap<int> heap(type, dataSet);

        //Generating value from [minElement, maxElement]
        value = IDGen::getInt(minElement, maxElement);

        //Performing operation, measuring its execution time and adding it (time) to intervals vector
        switch (operation) {
            case HeapOp::add:
                watch.startCounting();
                heap.add(value);
                time = watch.getTime();
                intervals.push_back(time);
                break;

            case HeapOp::rmr:
                watch.startCounting();
                heap.extractRoot();
                time = watch.getTime();
                intervals.push_back(time);
                break;

            case HeapOp::rm:
                position = IDGen::getInt(0, int(structureSize - 1));

                watch.startCounting();
                heap.remove(position);
                time = watch.getTime();
                intervals.push_back(time);
                break;

            case HeapOp::find:
                watch.startCounting();
                heap.find(value);
                time = watch.getTime();
                intervals.push_back(time);
                break;

            default:
                break;
        }
    }

    //Putting heap type to variable
    std::string strType = "min";
    if (type == HeapTp::max) {
        strType = "max";
    }

    //Calculating avg time for operation, creating opResult object and adding it to results vector
    switch (operation) {
        case HeapOp::add:
            addOpAvg(calcAvg(intervals), "add", "BHeap - " + strType);
            break;

        case HeapOp::rmr:
            addOpAvg(calcAvg(intervals), "extractRoot", "BHeap - " + strType);
            break;

        case HeapOp::rm:
            addOpAvg(calcAvg(intervals), "deleteKey", "BHeap - " + strType);
            break;

        case HeapOp::find:
            addOpAvg(calcAvg(intervals), "find", "BHeap - " + strType);
            break;

        default:
            break;
    }
    intervals.resize(0);

    //Marking end time of testing operation
    auto end = std::chrono::system_clock::now();

    //Calculating time needed to test operation
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "Finished operation for BHeap -> " << elapsed_seconds.count() << " [s]\n";
}

void Tests::testOperation(IDGen &idg, TreeOp operation) {
    //Creating vectors for individual operation execution times
    std::list<double> intervals;

    //Marking start of testing operation
    auto start = std::chrono::system_clock::now();

    int value;
    double time;

    //Performing specific operation sampleSize times for specified structureSize list
    for (int j = 0; j <= sampleSize; j++) {
        //Creating list with generated structure elements
        std::list <int> dataSet = idg.generateDataSet(structureSize, minElement, maxElement);

        //Creating new tree from list
        RedBlackTree<int> tree(dataSet);

        //Generating value from [minElement, maxElement]
        value = IDGen::getInt(minElement, maxElement);

        //Performing operation, measuring its execution time and adding it (time) to intervals vector
        switch (operation) {
            case TreeOp::add:
                watch.startCounting();
                tree.add(value);
                time = watch.getTime();
                intervals.push_back(time);
                break;

            case TreeOp::rm:
                watch.startCounting();
                tree.remove(value);
                time = watch.getTime();
                intervals.push_back(time);
                break;

            case TreeOp::find:
                watch.startCounting();
                tree.find(value);
                time = watch.getTime();
                intervals.push_back(time);
                break;

            default:
                break;
        }
    }

    //Calculating avg time for operation, creating opResult object and adding it to results vector
    switch (operation) {
        case TreeOp::add:
            addOpAvg(calcAvg(intervals), "add", "RBTree");
            break;

        case TreeOp::rm:
            addOpAvg(calcAvg(intervals), "remove", "RBTree");

            break;

        case TreeOp::find:
            addOpAvg(calcAvg(intervals), "find", "RBTree");
            break;

        default:
            break;
    }
    intervals.resize(0);
    //Marking end time of testing operation
    auto end = std::chrono::system_clock::now();

    //Calculating time needed to test operation
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "Finished operation for RBTree -> " << elapsed_seconds.count() << " [s]\n";
}


void Tests::printResults() {
    std::cout << "\n\n\n";

    //Printing opResult objects for each tested operation
    for (const OpResult &result: results) {
        std::cout << "[" << result.structure << "] Calculated average for "
                  << result.opName << " -> " << result.time << " [ns]\n";
    }
}

void Tests::saveResult(const std::string &structureName) {

    //Creating write file
    std::ofstream saveFile(structureName + "//test - " + std::to_string(structureSize) + ".txt");

    //Printing opResult objects for each tested operation to the file
    for (const OpResult &result: results) {
        saveFile <<  result.structure << ";"
                  << result.opName << ";" << result.time << "\n";
    }

    saveFile.close();
}