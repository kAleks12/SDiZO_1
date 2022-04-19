//
// Created by kacper on 11.04.2022.
//

#ifndef SDIZO_PROJECT_1_ENUMS_H
#define SDIZO_PROJECT_1_ENUMS_H

//Enum for tree node color
enum class NodeColor{
    red,
    black
};

//Enum for possible heap types
enum class HeapTp {
    min,
    max
};

//Enum for possible structures
enum class Structures{
    array,
    list,
    heap,
    tree,
    find

};

//Enum for possible operations for array
enum class ArrayOp{
    addf,
    addb,
    add,
    rmf,
    rmb,
    rm,
    find
};

//Enum for possible operations for list
enum class ListOp{
    addf,
    addb,
    add,
    rmf,
    rmb,
    rm,
    find
};

//Enum for possible operations for heap
enum class HeapOp{
    add,
    rmr,
    rm,
    find

};

//Enum for possible operations for tree
enum class TreeOp{
    add,
    rm,
    find
};

#endif //SDIZO_PROJECT_1_ENUMS_H