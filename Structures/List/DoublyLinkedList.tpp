//
// Created by kacper on 14.03.2022.
//

#ifndef SDIZO_PROJECT_1_DOUBLY_LINKED_LIST_TPP
#define SDIZO_PROJECT_1_DOUBLY_LINKED_LIST_TPP

#include <iostream>
#include <fstream>


template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() = default;

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const std::string &fileName) {
    //Opening source file
    std::ifstream srcFile(fileName);

    //Checking whether source file exists
    if (!srcFile.is_open()) {
        return;
    }

    size_t counter;
    srcFile >> counter;
    T value;

    //Filling list with values from source file
    for (int i = 0; i < counter; i++) {
        srcFile >> value;
        this->addBack(value);
    }
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const std::list <int> &dataSet) {
    //Filling the array with data from list
    for(T element: dataSet){
        this->addBack(element);
    }
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    //Checking whether list is not empty
    if (this->head != nullptr && this->tail != nullptr) {
        deleteList(this->head);
    }
}


template<typename T>
void DoublyLinkedList<T>::addBack(const T &val) {
    //Creating new element
    auto newElement = new ListElement<T>(val, this->tail, nullptr);

    //Checking whether it is the first element in the list
    if (this->size == 0) {
        this->head = newElement;
        this->tail = newElement;
        this->size++;

        return;
    }

    //Inserting new element to the list
    (this->tail)->next = newElement;
    this->tail = newElement;
    this->size++;
}

template<typename T>
void DoublyLinkedList<T>::addFront(const T &val) {
    //Creating new element
    auto newElement = new ListElement<T>(val, nullptr, this->head);

    //Checking whether it is the first element in the list
    if (this->size == 0) {
        this->head = newElement;
        this->tail = newElement;
        this->size++;

        return;
    }

    //Inserting new element to the list
    (this->head)->previous = newElement;
    this->head = newElement;
    this->size++;
}

template<typename T>
void DoublyLinkedList<T>::add(const T &val, const size_t &position) {
    //Checking whether position is within list bounds
    if (position >= this->size) {
        throw std::out_of_range("Out of range!");
    }

    //Checking whether to call addFront()
    if (position == 0) {
        addFront(val);
        return;
    }

    //Calculating middle index of the list
    size_t middleIndex = (this->size) / 2;

    //Checking whether to iterate list from head or from tail
    if (position < middleIndex) {
        addFromFront(val, position);
    } else addFromBack(val, position);
}

template<typename T>
void DoublyLinkedList<T>::addFromFront(const T &val, size_t position) {
    //Creating previous and next elements for new element
    ListElement<T> *newElementPrevious = this->head;
    ListElement<T> *newElementNext;

    //Iterating through the list from head to set previous element
    while (--position > 0) {
        newElementPrevious = newElementPrevious->next;
    }

    //Setting next element
    newElementNext = newElementPrevious->next;

    //Creating new element
    auto newElement = new ListElement(val, newElementPrevious, newElementNext);

    //Inserting new element to the list
    newElementPrevious->next = newElement;
    newElementNext->previous = newElement;
    this->size++;
}

template<typename T>
void DoublyLinkedList<T>::addFromBack(const T &val, const size_t &position) {
    //Creating previous and next elements for new element
    ListElement<T> *newElementPrevious;
    ListElement<T> *newElementNext = this->tail;

    //Iterating through the list from tail to set next element
    size_t iterator = this->size;
    while (--iterator > position) {
        newElementNext = newElementNext->previous;
    }

    //Setting previous element
    newElementPrevious = newElementNext->previous;

    //Creating new element
    auto newElement = new ListElement(val, newElementPrevious, newElementNext);

    //Inserting new element to the list
    newElementPrevious->next = newElement;
    newElementNext->previous = newElement;
    this->size++;
}

template<typename T>
void DoublyLinkedList<T>::removeBack() {
    //Checking whether list is empty
    if (this->size == 0) {
        return;
    }

    //Checking if there is only one element in the list
    if (this->size == 1) {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
        return;
    }

    //Creating new tail and setting its previous and next elements
    auto newTail = (this->tail)->previous;
    newTail->next = nullptr;

    //Deleting old tail and swapping it with the new one
    delete this->tail;
    this->tail = newTail;
    this->size--;
}

template<typename T>
void DoublyLinkedList<T>::removeFront() {
    //Checking whether list is empty
    if (this->size == 0) {
        return;
    }

    //Checking if there is only one element in the list
    if (this->size == 1) {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
        return;
    }

    //Creating new head and setting its previous and next elements
    auto newHead = (this->head)->next;
    newHead->previous = nullptr;

    //Deleting old head and swapping it with the new one
    delete this->head;
    this->head = newHead;
    this->size--;
}

template<typename T>
void DoublyLinkedList<T>::remove(const size_t &position) {
    //Checking whether position is within list bounds
    if (position >= this->size) {
        throw std::out_of_range("Out of range!");
    }

    //Checking whether to call addFront()
    if (position == 0) {
        removeFront();
        return;
    }

    //Checking whether to call removeBack()
    if (position == this->size - 1) {
        removeBack();
        return;
    }

    //Calculating middle index of the list
    size_t middleIndex = (this->size) / 2;

    //Checking whether to iterate list from head or from tail
    if (position < middleIndex) {
        removeFromFront(position);
    } else removeFromBack(position);
}

template<typename T>
void DoublyLinkedList<T>::removeFromFront(size_t position) {
    //Creating previous and next elements for element to delete
    ListElement<T> *previousElement = this->head;
    ListElement<T> *nextElement;
    ListElement<T> *elementToDelete;

    //Iterating through the list from head to set previous element
    while (--position > 0) {
        previousElement = previousElement->next;
    }

    //Deleting element and setting new next for the previous element
    elementToDelete = previousElement->next;
    nextElement = elementToDelete->next;


    //Setting new previous for the next element nad new next for the previous element
    previousElement->next = nextElement;
    nextElement->previous = previousElement;
    this->size--;
}

template<typename T>
void DoublyLinkedList<T>::removeFromBack(size_t position) {
    //Creating previous and next elements for element to delete
    ListElement<T> *previousElement;
    ListElement<T> *nextElement = this->tail;
    ListElement<T> *elementToDelete;


    //Iterating through the list from tail to set next element
    while (--position > 0) {
        nextElement = nextElement->previous;
    }

    //Deleting element
    elementToDelete = nextElement->previous;
    previousElement = elementToDelete->previous;
    delete elementToDelete;

    //Setting new previous for the next element nad new next for the previous element
    previousElement->next = nextElement;
    nextElement->previous = previousElement;
    this->size--;
}

template<typename T>
bool DoublyLinkedList<T>::find(const T &val) {
    //Creating list iterator
    auto iterator = this->head;

    //Iterating through the list till its tail
    while (iterator != this->tail) {
        if (iterator->content == val) {
            return true;
        }
        iterator = iterator->next;
    }

    //Checking whether tail has the right value
    if(this -> tail != nullptr) {
        if (this->tail->content == val) {
            return true;
        }
    }

    return false;
}

template<typename T>
void DoublyLinkedList<T>::print() {
    if (this->size == 0) {
        std::cout << "Contents of List: empty\n";
        std::cout << "Size of the list is: " << this->size << "\n\n";
        return;
    }

    std::cout << "Contents of List: \n\n( nullptr ";

    ListElement<T> *iterator = this->head;

    if (this->size == 1) {
        std::cout << " <- (" << iterator->content << ") -> nullptr )\n";
        std::cout << "Size of the list is: " << this->size << "\n\n";
        return;
    }

    while (true) {

        std::cout << " <- (" << iterator->content << ") ->";
        if (iterator->next == nullptr) {
            break;
        }
        iterator = iterator->next;

    }
    std::cout << " nullptr )\n\n";
    std::cout << "Size of the list is: " << this->size << "\n\n";
}


template<typename T>
void DoublyLinkedList<T>::deleteList(ListElement<T>* element) {
    //Checking whether the element is the tail
    if(element->next != nullptr){
        //Calling function to delete nex element
        deleteList(element->next);

        //Deleting element
        delete element;
    }
}
#endif //SDIZO_PROJECT_1_DOUBLY_LINKED_LIST_TPP