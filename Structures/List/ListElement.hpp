//
// Created by kacper on 14.03.2022.
//

#ifndef SDIZO_PROJECT_1_LIST_ELEMENT_HPP
#define SDIZO_PROJECT_1_LIST_ELEMENT_HPP


template<typename T>
struct ListElement {
protected:
    ListElement *previous;
    ListElement *next;
    T content;

    ListElement(T val, ListElement<T> *previous, ListElement<T> *next);

    template<typename TT> friend
    class DoublyLinkedList;
};

#include "ListElement.tpp"

#endif //SDIZO_PROJECT_1_LIST_ELEMENT_HPP