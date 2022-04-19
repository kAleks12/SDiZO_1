//
// Created by kacper on 14.03.2022.
//

#ifndef SDIZO_PROJECT_1_DOUBLY_lINKED_LIST_HPP
#define SDIZO_PROJECT_1_DOUBLY_lINKED_LIST_HPP

#include "ListElement.hpp"
#include <iostream>
#include <list>


template<typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList();

    explicit DoublyLinkedList(const std::string &fileName);

    explicit DoublyLinkedList(const std::list<int> &dataSet);

    ~DoublyLinkedList();

    void addBack(const T &val);

    void addFront(const T &val);

    void add(const T &val, const size_t &position);

    void addFromFront(const T &val, size_t position);

    void addFromBack(const T &val, const size_t &position);

    void removeBack();

    void removeFront();

    void remove(const size_t &position);

    void removeFromFront(size_t position);

    void removeFromBack(size_t position);

    bool find(const T &val);

    void print();

    void deleteList(ListElement<T>* element);

private:
    size_t size = 0;
    ListElement<T> *head = nullptr;
    ListElement<T> *tail = nullptr;

};

#include "DoublyLinkedList.tpp"

#endif //SDIZO_PROJECT_1_DOUBLY_LINKED_LIST_HPP