//
// Created by kacper on 04.04.2022.
//

#ifndef SDIZO_PROJECT_1_DATA_GENERATOR_HPP
#define SDIZO_PROJECT_1_DATA_GENERATOR_HPP

#include <string>
#include <list>

class IDGen {
public:
    explicit IDGen();

    std::list <int> generateDataSet(const size_t& vectorSize, const int& min, const int& max);

    static int getInt(const int& min, const int& max);
};

#endif //SDIZO_PROJECT_1_DATA_GENERATOR_HPP