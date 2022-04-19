//
// Created by kacper on 11.04.2022.
//

#ifndef SDIZO_PROJECT_1_MENU_H
#define SDIZO_PROJECT_1_MENU_H


#include "../Structures/List/DoublyLinkedList.hpp"
#include "../Structures/Heap/BinaryHeap.hpp"
#include "../Structures/Tree/RedBlackTree.hpp"


class Menu {
public:
    static void initMenu();

    static void createStructure(Structures structure);

    static void arrSubmenu(DynamicArray<int> &array);

    static void listSubmenu(DoublyLinkedList<int> &list);

    static void heapSubmenu(BinaryHeap<int> &heap);

    static void treeSubmenu(RedBlackTree<int> &tree);

    static int getSafeInput();
};

#endif //SDIZO_PROJECT_1_MENU_H