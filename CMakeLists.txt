cmake_minimum_required(VERSION 3.21)
project(SDiZO_Project_1)


set(CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(
        SDiZO_Project_1
        main.cpp
        Structures/Array/DynamicArray.hpp
        Structures/Array/DynamicArray.tpp
        Structures/List/DoublyLinkedList.hpp
        Structures/List/DoublyLinkedList.tpp
        Structures/List/ListElement.hpp
        Structures/List/ListElement.tpp
        Structures/Heap/BinaryHeap.hpp
        Structures/Heap/BinaryHeap.tpp
        Structures/Tree/TreeNode.hpp
        Structures/Tree/TreeNode.tpp
        Structures/Tree/RedBlackTree.hpp
        Structures/Tree/RedBlackTree.tpp
        Testing/TimeMeasurement.hpp
        Testing/IDGen.hpp
        Testing/IDGen.cpp
        Testing/Tests.cpp
        Testing/Tests.h
        UI/Menu.h
        UI/Menu.cpp
        Enums.h
        SDiZO.h
)
