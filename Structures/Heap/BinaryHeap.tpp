//
// Created by kacper on 18.03.2022.
//

#ifndef SDIZO_PROJECT_1_BINARY_HEAP_TPP
#define SDIZO_PROJECT_1_BINARY_HEAP_TPP


#include <fstream>

template<typename T>
BinaryHeap<T>::BinaryHeap(HeapTp type) : tp(type) {}

template<typename T>
BinaryHeap<T>::BinaryHeap(HeapTp type, const std::string &fileName): tp(type) {
    std::ifstream srcFile(fileName);

    if (!srcFile.is_open()) {
        std::cout << "File not found\n\n";
        return;
    }
    size_t tmpSize;
    srcFile >> tmpSize;
    T value;

    for (int i = 0; i < tmpSize; i++) {
        srcFile >> value;
        this->add(value);
    }
}

template<typename T>
BinaryHeap<T>::BinaryHeap(HeapTp type, const std::list<int> &dataSet): tp(type) {
    //Filling the array with data from vector
    for(T element: dataSet){
        this->add(element);
    }
}

template<typename T>
int BinaryHeap<T>::extractRoot() {
    //Checking whether heap is empty, then returning infinity number
    if (size <= 0) {
        return INT_MAX;
    }
    //Inserting root to variable
    T root = body[0];

    //Checking whether heap has only one element
    if (size == 1) {
        //Removing root from the heap's body
        body.removeFront();
        this->size--;
        return root;
    }

    //Swapping first and last elements in heap's body and removing root
    body[0] = body[size - 1];
    size--;
    body.removeBack();

    //Restoring heap
    if (this->tp == HeapTp::min) {
        minHeapify(0);
    }
    if (this->tp == HeapTp::max) {
        maxHeapify(0);
    }

    return root;
}

template<typename T>
void BinaryHeap<T>::remove(const size_t &index) {
    //Moving element to be deleted to the root by changing its value to heap's type limit
    if (this->tp == HeapTp::min) {
        changeValue(index, INT_MIN);
    } else {
        changeValue(index, INT_MAX);
    }

    //Extracting root
    extractRoot();
}

template<typename T>
void BinaryHeap<T>::add(const T &val) {
    //Inserting new val at last index of the body
    size++;
    body.addBack(val);
    size_t index = size - 1;


    //Restoring min heap
    if (this->tp == HeapTp::min) {
        while (index != 0 && body[getParent(index)] > body[index]) {
            T tmp = body[getParent(index)];
            body[getParent(index)] = body[index];
            body[index] = tmp;
            index = getParent(index);
        }
    }

    //Restoring max heap
    if (this->tp == HeapTp::max) {
        while (index != 0 && body[getParent(index)] < body[index]) {
            T tmp = body[getParent(index)];
            body[getParent(index)] = body[index];
            body[index] = tmp;
            index = getParent(index);
        }
    }
}

template<typename T>
bool BinaryHeap<T>::find(const T &val) {
    return body.find(val);
}

template<typename T>
void BinaryHeap<T>::print() {
    //Checking whether heap's body is empty
    if (this->size == 0) {
        std::cout << "Heap is empty\n\n";
        return;
    }
    std::cout << "Contents of heap:\n\n";

    // Calculating heap depth
    size_t depth = getDepth();
    getDepth();

    // Calculating maximum number of elements
    size_t maxSize = pow(2, depth);

    //Setting operational variables
    bool end = false;
    size_t first = 0;
    size_t last = 1;

    size_t space = maxSize;

    while (!end) {
        // Printing spaces before each tree level
        std::cout << std::string(space / 2 * 3, ' ');

        // Printing nodes on current heap level
        for (size_t i = first; i < last; i++) {
            if (i >= this->size) {
                end = true;
                break;
            }

            // Checking if table on current index is not empty
            std::cout << this->body[i] << std::string(space * 3, ' ');

        }

        std::cout << "\n";

        // Changing indexes or last and first node on each tree level
        first = last;
        last = 2 * last + 1;

        // Changing size of space between nodes
        space = space / 2;
    }
    std::cout << "\nSize of heap: " << this->size;
    std::cout << "\n\n";

}

template<typename T>
void BinaryHeap<T>::minHeapify(int index) {
    //Creating operational variables
    size_t leftSon = getLeft(index);
    size_t rightSon = getRight(index);
    size_t smallest = index;

    //Checking whether left son is within body bounds and whether its value is
    // smaller than the original elements' one
    if (leftSon < size && body[leftSon] < body[smallest]) {
        smallest = leftSon;
    }

    //Checking whether right son is within body bounds and whether its value is
    // smaller than smallest' one
    if (rightSon < size && body[rightSon] < body[smallest]) {
        smallest = rightSon;
    }

    //Checking whether the index with the smallest value is not the original one
    //and swapping values from the smallest index and original one
    if (smallest != index) {
        T tmp = body[smallest];
        body[smallest] = body[index];
        body[index] = tmp;

        //Checking rest of the indexes down the heap's body
        minHeapify(smallest);
    }
}

template<typename T>
void BinaryHeap<T>::maxHeapify(int index) {
    //Creating operational variables
    size_t leftSon = getLeft(index);
    size_t rightSon = getRight(index);
    size_t largest = index;

    //Checking whether left son is within body bounds and whether its value is
    // larger than the original elements' one
    if (leftSon < this->size && this->body[leftSon] > this->body[largest]) {
        largest = leftSon;
    }

    //Checking whether right son is within body bounds and whether its value is
    // larger than largest' one
    if (rightSon < this->size && this->body[rightSon] > this->body[largest]) {
        largest = rightSon;
    }

    //Checking whether the index with the largest value is not the original one
    //and swapping values from the largest index and original one
    if (largest != index) {
        T tmp = body[largest];
        body[largest] = body[index];
        body[index] = tmp;

        //Checking rest of the indexes down the heap's body
        maxHeapify(largest);
    }
}

template<typename T>
void BinaryHeap<T>::changeValue(size_t index, T newVal) {
    //Setting new value
    body[index] = newVal;

    //Restoring min heap
    if (this->tp == HeapTp::min) {
        while (index != 0 && body[getParent(index)] > body[index]) {
            T tmp = body[getParent(index)];
            body[getParent(index)] = body[index];
            body[index] = tmp;
            index = getParent(index);
        }
    }

    //Restoring max heap
    if (this->tp == HeapTp::max) {
        while (index != 0 && body[getParent(index)] < body[index]) {
            T tmp = body[getParent(index)];
            body[getParent(index)] = body[index];
            body[index] = tmp;
            index = getParent(index);
        }
    }
}

template<typename T>
int BinaryHeap<T>::getDepth() {
    //Creating operational variables
    size_t last = 1;
    size_t level = 0;

    //Calculating number of heap's levels
    while (last <= size) {
        level++;
        last = 2 * last + 1;
    }
    return level;
}


#endif //SDIZO_PROJECT_1_BINARY_HEAP_TPP