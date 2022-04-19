//
// Created by kacper on 07.04.2022.
//

#ifndef SDIZO_PROJECT_1_BLACK_RED_TREE_HPP
#define SDIZO_PROJECT_1_BLACK_RED_TREE_HPP


#include "TreeNode.hpp"
#include <cmath>

template<typename T>
class RedBlackTree {
public:
    RedBlackTree();

    explicit RedBlackTree(const std::string &fileName);

    explicit RedBlackTree(const std::list <int> &dataSet);

    ~RedBlackTree();

    void add(const T &value);

    bool find(const T &value);

    void remove(const T &value);

    void print();

private:
    TreeNode<T> *root;
    TreeNode<T> *gandalf;


    TreeNode<T> *getSuccessor(TreeNode<T> *node);

    TreeNode<T> *min(TreeNode<T> *node);

    TreeNode<T> *findNode(const T &value, TreeNode<T> *node);

    void deleteFixColors(TreeNode<T> *node);

    void leftRotation(TreeNode<T> *node);

    void rightRotation(TreeNode<T> *node);

    void placeNodes(TreeNode<T> *node, TreeNode<T> **tree, size_t index);

    void getDepth(TreeNode<T> *node, size_t &maxDepth, size_t currentDepth);

    void deleteTree(TreeNode<T> *node);


};

#include "RedBlackTree.tpp"


#endif //SDIZO_PROJECT_1_BLACK_RED_TREE_HPP