//
// Created by kacper on 11.04.2022.
//

#include "Menu.h"
#include <windows.h>

void Menu::initMenu() {
    //Displaying initial menu with available structures
    char chosenStructure;

    while (true) {
        system("cls");

        std::cout << "Dynamic Array [1]\n";
        std::cout << "Doubly Linked List [2]\n";
        std::cout << "Binary Heap [3]\n";
        std::cout << "Red Black Tree [4]\n";
        std::cout << "Exit program [Q]\n";
        std::cout << "Hello, select structure: ";

        std::cin >> chosenStructure;

        switch (chosenStructure) {
            case '1':
                createStructure(Structures::array);
                break;

            case '2':
                createStructure(Structures::list);
                break;

            case '3':
                createStructure(Structures::heap);
                break;

            case '4':
                createStructure(Structures::tree);
                break;

            case 'Q':
                return;

            default:
                std::cout << "\nNumber out of range!!!\n";
                Sleep(2000);
                break;
        }
    }
}

void Menu::createStructure(Structures structure) {
    //Displaying prompt about creating structure from .txt file
    // and prompt about heap type when BinaryHeap structure chosen
    system("cls");
    std::string input;
    int heapType;

    if (structure == Structures::heap) {
        while (true) {
            std::cout << "Would you like to create max_heap[1] or min_heap[2]: ";
            std::cin >> input;

            if (input == "1" || input == "2") {
                heapType = std::stoi(input);
                system("cls");
                break;
            }
            std::cout << "Invalid input";
            Sleep(1000);
            system("cls");
        }
    }

    std::cout << "Would you like to create structure from a file ? [y/n]: ";
    std::cin >> input;

    if (input == "y" || input == "Y" || input == "yes" || input == "Yes") {
        std::cout << "Enter name of the file eg. \"data.txt\"\n(must be located in the same directory as .exe file): ";
        std::cin >> input;
    } else {
        input = "empty";
    }

    //Calling submenu for chosen structure
    switch (structure) {
        case Structures::array:
            if (input == "empty") {
                DynamicArray<int> array;
                arrSubmenu(array);
            } else {
                DynamicArray<int> array(input);
                arrSubmenu(array);
            }
            break;

        case Structures::list:
            if (input == "empty") {
                DoublyLinkedList<int> list;
                listSubmenu(list);
            } else {
                DoublyLinkedList<int> list(input);
                listSubmenu(list);
            }
            break;

        case Structures::heap:
            if (input == "empty") {
                if (heapType == 1) {
                    BinaryHeap<int> heap(HeapTp::max);
                    heapSubmenu(heap);
                } else {
                    BinaryHeap<int> heap(HeapTp::min);
                    heapSubmenu(heap);
                }
            }
            if (heapType == 1) {
                BinaryHeap<int> heap(HeapTp::max, input);
                heapSubmenu(heap);
            } else {
                BinaryHeap<int> heap(HeapTp::min, input);
                heapSubmenu(heap);
            }
            break;

        case Structures::tree:
            if (input == "empty") {
                RedBlackTree<int> tree;
                treeSubmenu(tree);
            } else {
                RedBlackTree<int> tree(input);
                treeSubmenu(tree);
            }
            break;

        default:
            break;
    }
}

void Menu::arrSubmenu(DynamicArray<int> &array) {
    //Displaying current content of the array, list of possible operations
    //and prompts before performing chosen operation
    char input;
    while (input != 'Q') {
        system("cls");
        array.print();

        std::cout << "Add front [1]\n";
        std::cout << "Add back [2]\n";
        std::cout << "Add at certain position [3]\n";
        std::cout << "Remove front [4]\n";
        std::cout << "Remove back [5]\n";
        std::cout << "Remove at certain position [6]\n";
        std::cout << "Find element [7]\n";
        std::cout << "Go to main menu [Q]\n\n";
        std::cout << "Hello, select operation: ";

        std::cin >> input;


        int value;
        int position;

        switch (input) {
            case '1':
                std::cout << "[AddFront] Enter value: ";
                value = getSafeInput();

                if (value != INT32_MIN) {
                    array.addFront(value);
                }
                break;

            case '2':
                std::cout << "[AddBack] Enter value: ";
                value = getSafeInput();

                if (value != INT32_MIN) {
                    array.addBack(value);
                }
                break;

            case '3':
                std::cout << "[Add] Enter value: ";
                value = getSafeInput();

                std::cout << "[Add] Enter position: ";
                position = getSafeInput();

                if (value != INT32_MIN && position != INT32_MIN) {
                    try {
                        array.add(value, position);
                    } catch (std::out_of_range &e) {
                        std::cout << "Index out of bounds\n";
                        Sleep(1000);
                    }
                }
                break;

            case '4':
                array.removeFront();
                break;

            case '5':
                array.removeBack();
                break;

            case '6':
                std::cout << "[Remove] Enter position: ";
                position = getSafeInput();

                if (position != INT32_MIN) {
                    try {
                        array.remove(position);
                    } catch (std::out_of_range &e) {
                        std::cout << "Index out of bounds\n";
                        Sleep(1000);
                    }
                }
                break;

            case '7':
                std::cout << "[Find] Enter value: ";
                value = getSafeInput();

                if (value != INT32_MIN) {
                    if (array.find(value)) {
                        std::cout << "Found element\n";
                        Sleep(2000);
                        break;
                    }
                    std::cout << "Element not found\n";
                    Sleep(2000);
                }
                break;

            default:
                break;
        }
    }
}

void Menu::listSubmenu(DoublyLinkedList<int> &list) {
    //Displaying current content of the list, list of possible operations
    //and prompts before performing chosen operation
    char input;
    while (input != 'Q') {
        system("cls");
        list.print();

        std::cout << "Add front [1]\n";
        std::cout << "Add back [2]\n";
        std::cout << "Add at certain position [3]\n";
        std::cout << "Remove front [4]\n";
        std::cout << "Remove back [5]\n";
        std::cout << "Remove at certain position [6]\n";
        std::cout << "Find element [7]\n";
        std::cout << "Go to main menu [Q]\n\n";
        std::cout << "Hello, select operation: ";

        std::cin >> input;


        int value;
        int position;

        switch (input) {
            case '1':
                std::cout << "[AddFront] Enter value: ";
                value = getSafeInput();

                if (value != INT32_MIN) {
                    list.addFront(value);
                }
                break;

            case '2':
                std::cout << "[AddBack] Enter value: ";
                value = getSafeInput();

                if (value != INT32_MIN) {
                    list.addBack(value);
                }
                break;

            case '3':
                std::cout << "[Add] Enter value: ";
                value = getSafeInput();

                std::cout << "[Add] Enter position: ";
                position = getSafeInput();

                if (value != INT32_MIN && position != INT32_MIN) {
                    try {
                        list.add(value, position);
                    } catch (std::out_of_range &e) {
                        std::cout << "Index out of bounds\n";
                        Sleep(1000);
                    }
                }
                break;

            case '4':
                list.removeFront();
                break;

            case '5':
                list.removeBack();
                break;

            case '6':
                std::cout << "[Remove] Enter position: ";
                position = getSafeInput();

                if (position != INT32_MIN) {
                    try {
                        list.remove(position);
                    } catch (std::out_of_range &e) {
                        std::cout << "Index out of bounds\n";
                        Sleep(1000);
                    }
                }
                break;

            case '7':
                std::cout << "[Find] Enter value: ";
                value = getSafeInput();

                if (value != INT32_MIN) {
                    if (list.find(value)) {
                        std::cout << "Found element\n";
                        Sleep(2000);
                        break;
                    }
                    std::cout << "Element not found\n";
                    Sleep(2000);
                }
                break;

            default:
                break;
        }
    }
}

void Menu::heapSubmenu(BinaryHeap<int> &heap) {
    //Displaying current content of the heap, list of possible operations
    //and prompts before performing chosen operation
    char input;
    while (input != 'Q') {
        system("cls");
        heap.print();

        std::cout << "Add [1]\n";
        std::cout << "Extract root [2]\n";
        std::cout << "Remove [3]\n";
        std::cout << "Find element [4]\n";
        std::cout << "Go to main menu [Q]\n\n";
        std::cout << "Hello, select operation: ";

        std::cin >> input;


        int value;
        int position;

        switch (input) {
            case '1':
                std::cout << "[Add] Enter value: ";
                value = getSafeInput();

                if (value != INT32_MIN) {
                    heap.add(value);
                }
                break;

            case '2':
                heap.extractRoot();
                break;

            case '3':
                std::cout << "[Remove] Enter position: ";
                position = getSafeInput();

                if (value != INT32_MIN) {
                    try {
                        heap.remove(position);
                    } catch (std::out_of_range &e) {
                        std::cout << "Index out of bounds\n";
                        Sleep(1000);
                    }
                }
                break;

            case '4':
                std::cout << "[Find] Enter value: ";
                value = getSafeInput();

                if (value != INT32_MIN) {
                    if (heap.find(value)) {
                        std::cout << "Found element\n";
                        Sleep(2000);
                        break;
                    }
                    std::cout << "Element not found\n";
                    Sleep(2000);
                }
                break;

            default:
                break;
        }
    }
}

void Menu::treeSubmenu(RedBlackTree<int> &tree) {
    //Displaying current content of the tree, list of possible operations
    //and prompts before performing chosen operation
    char input;
    while (input != 'Q') {
        system("cls");
        tree.print();

        std::cout << "Add [1]\n";
        std::cout << "Remove [2]\n";
        std::cout << "Find element [3]\n";
        std::cout << "Go to main menu [Q]\n\n";
        std::cout << "Hello, select operation: ";

        std::cin >> input;


        int value;

        switch (input) {
            case '1':
                std::cout << "[Add] Enter value: ";
                value = getSafeInput();

                if (value != INT32_MIN) {
                    tree.add(value);
                }
                break;

            case '2':
                std::cout << "[Remove] Enter value: ";
                value = getSafeInput();

                if (value != INT32_MIN) {
                    tree.remove(value);
                }
                break;

            case '3':
                std::cout << "[Find] Enter value: ";
                value = getSafeInput();

                if (value != INT32_MIN) {
                    if (tree.find(value)) {
                        std::cout << "Found element\n";
                        Sleep(2000);
                        break;
                    }
                    std::cout << "Element not found\n";
                    Sleep(2000);
                }
                break;

            default:
                break;
        }
    }
}

int Menu::getSafeInput() {
    std::string value;

    std::cin >> value;

    try {
        std::stoi(value);
    } catch (std::invalid_argument &e) {
        std::cout << "Not a number\n";
        Sleep(1000);
        return INT32_MIN;
    }

    return std::stoi(value);
}