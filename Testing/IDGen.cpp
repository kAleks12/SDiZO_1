//
// Created by kacper on 04.04.2022.
//
#include "IDGen.hpp"

#include <random>


IDGen::IDGen() = default;

std::list <int> IDGen::generateDataSet(const size_t& setSize, const int& min, const int& max) {
    //Creating output list for generated numbers
    std::list <int> dataSet;

    //Creating variables needed to generate numbers
    std::uniform_int_distribution <int> range(min, max);
    std::random_device rdev;
    std::mt19937 engine (rdev());


    //Generating numbers and writing them to the output list
    for(int i = 0; i < setSize; i++){
        dataSet.push_back(range(engine));
    }

    return dataSet;
}

int IDGen::getInt(const int& min, const int& max) {
    //Creating variables needed to generate numbers
    std::random_device rdev;
    std::mt19937 engine (rdev());
    std::uniform_int_distribution <int> range(min, max);

    //Generating random number
    return range(engine);
}