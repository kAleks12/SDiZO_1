//
// Created by kacper on 13.04.2022.
//

#ifndef SDIZO_PROJECT_1_TREE_NODE_TPP
#define SDIZO_PROJECT_1_TREE_NODE_TPP


template<typename T>
TreeNode<T>::TreeNode(NodeColor color,T value, TreeNode<T> *lSon, TreeNode<T> *rSon, TreeNode<T> *parent) {
    this->color = color;
    this->content = value;
    this->leftSon = lSon;
    this->rightSon = rSon;
    this->parent = parent;

}

#endif //SDIZO_PROJECT_1_TREE_NODE_TPP