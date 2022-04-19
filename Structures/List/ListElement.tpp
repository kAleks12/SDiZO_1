//
// Created by kacper on 14.03.2022.
//

#ifndef SDIZO_PROJECT_1_LIST_ELEMENT_TPP
#define SDIZO_PROJECT_1_LIST_ELEMENT_TPP


template<typename T>
ListElement<T>::ListElement(T val, ListElement<T> *previous, ListElement<T> *next) {
    this->content = val;
    this->previous = previous;
    this->next = next;
}

#endif //SDIZO_PROJECT_1_LIST_ELEMENT_TPP