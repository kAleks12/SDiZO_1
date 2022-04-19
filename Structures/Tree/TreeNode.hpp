//
// Created by kacper on 13.04.2022.
//

#ifndef SDIZO_PROJECT_1_TREE_NODE_HPP
#define SDIZO_PROJECT_1_TREE_NODE_HPP

#include "../../Enums.h"

template<typename T>
struct TreeNode {
protected:
    T content;
    NodeColor color;
    TreeNode <T> *leftSon;
    TreeNode <T> *rightSon;
    TreeNode <T> *parent;


    explicit TreeNode(NodeColor color, T value = INT32_MAX,TreeNode <T> *lSon = nullptr,
             TreeNode <T> *rSon = nullptr , TreeNode< T> *parent = nullptr);

    template<typename TT> friend
    class RedBlackTree;
};

#include "TreeNode.tpp"

#endif //SDIZO_PROJECT_1_TREE_NODE_HPP