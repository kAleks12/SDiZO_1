//
// Created by kacper on 18.03.2022.
//

#ifndef SDIZO_PROJECT_1_BINARY_HEAP_HPP
#define SDIZO_PROJECT_1_BINARY_HEAP_HPP

#include "../Array/DynamicArray.hpp"
#include "../../Enums.h"

#include <cmath>

template<typename T>
class BinaryHeap {
public:
    explicit BinaryHeap(HeapTp type);

    BinaryHeap(HeapTp type, const std::string &fileName);

    BinaryHeap(HeapTp type, const std::list<int> &dataSet);

    int extractRoot();

    void remove(const size_t &index);

    void add(const T &val);

    bool find(const T &val);

    void print();

private:
    size_t size = 0;
    HeapTp tp;
    DynamicArray<T> body;

    inline int getParent(int index) { return (index - 1) / 2; }

    inline int getLeft(int index) { return (2 * index + 1); }

    inline int getRight(int index) { return (2 * index + 2); }

    void minHeapify(int index);

    void maxHeapify(int index);

    void changeValue(size_t index, T newVal);

    int getDepth();

};

#include "BinaryHeap.tpp"

#endif //SDIZO_PROJECT_1_BINARY_HEAP_HPP