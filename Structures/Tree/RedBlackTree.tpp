//
// Created by kacper on 07.04.2022.
//

#ifndef SDIZO_PROJECT_1_BLACK_RED_TREE_TPP
#define SDIZO_PROJECT_1_BLACK_RED_TREE_TPP

#include "../../Enums.h"
#include <windows.h>

template<typename T>
RedBlackTree<T>::RedBlackTree() {
    // Initialize gandalf node
    this->gandalf = new TreeNode<T>(NodeColor::black);
    this->gandalf->leftSon = this->gandalf;
    this->gandalf->rightSon = this->gandalf;
    this->gandalf->parent = this->gandalf;

    // Set root to gandalf
    this->root = this->gandalf;
}

template<typename T>
RedBlackTree<T>::RedBlackTree(const std::string &fileName) {
    //Opening source file
    std::ifstream srcFile(fileName);

    // Initialize gandalf node
    this->gandalf = new TreeNode<T>(NodeColor::black);
    this->gandalf->leftSon = this->gandalf;
    this->gandalf->rightSon = this->gandalf;
    this->gandalf->parent = this->gandalf;

    // Set root to gandalf
    this->root = this->gandalf;

    //Checking whether file exists
    if (!srcFile.is_open()) {
        std::cout << "File not found\n\n";
        return;
    }

    size_t counter;
    srcFile >> counter;
    T value;

    //Filling the array with data from source file
    for (int i = 0; i < counter; i++) {
        srcFile >> value;
        this->add(value);
    }
}

template<typename T>
RedBlackTree<T>::RedBlackTree(const std::list <int> &dataSet) {
    // Initialize gandalf node
    this->gandalf = new TreeNode<T>(NodeColor::black);
    this->gandalf->leftSon = this->gandalf;
    this->gandalf->rightSon = this->gandalf;
    this->gandalf->parent = this->gandalf;

    // Set root to gandalf
    this->root = this->gandalf;

    //Filling the array with data from list
    for(T element: dataSet){
        this->add(element);
    }
}

template<typename T>
RedBlackTree<T>::~RedBlackTree() {
    // Delete all nodes
    this->deleteTree(this->root);

    // Delete gandalf
    if (this->gandalf != nullptr) {
        delete this->gandalf;
    }
}

template<typename T>
void RedBlackTree<T>::add(const T &value) {

    // Creating new node, and a temporary one
    TreeNode<T> *newNode;
    TreeNode<T> *tmpNode;

    // Initializing new node
    newNode = new TreeNode<T>(NodeColor::red, value,
                              this->gandalf, this->gandalf, this->root);

    // Checking if the tree is empty
    if (newNode->parent == this->gandalf) {
        this->root = newNode;
    } else {
        // Placing new node in a tree, like in a normal Binary Search one
        while (true) {
            if (value < newNode->parent->content) {
                if (newNode->parent->leftSon == this->gandalf) {
                    newNode->parent->leftSon = newNode;
                    break;
                }
                newNode->parent = newNode->parent->leftSon;
            } else {
                if (newNode->parent->rightSon == this->gandalf) {
                    newNode->parent->rightSon = newNode;
                    break;
                }
                newNode->parent = newNode->parent->rightSon;
            }
        }
    }

    // Fixing tree structure
    while (newNode != this->root && newNode->parent->color == NodeColor::red) {
        if (newNode->parent == newNode->parent->parent->leftSon) {
            tmpNode = newNode->parent->parent->rightSon;

            if (tmpNode->color == NodeColor::red) {
                newNode->parent->color = NodeColor::black;
                tmpNode->color = NodeColor::black;

                newNode->parent->parent->color = NodeColor::red;
                newNode = newNode->parent->parent;
                continue;
            }

            if (newNode == newNode->parent->rightSon) {
                newNode = newNode->parent;
                this->leftRotation(newNode);
            }

            newNode->parent->color = NodeColor::black;
            newNode->parent->parent->color = NodeColor::red;
            this->rightRotation(newNode->parent->parent);

            break;
        } else {
            tmpNode = newNode->parent->parent->leftSon;

            if (tmpNode->color == NodeColor::red) {
                newNode->parent->color = NodeColor::black;
                tmpNode->color = NodeColor::black;

                newNode->parent->parent->color = NodeColor::red;
                newNode = newNode->parent->parent;
                continue;
            }

            if (newNode == newNode->parent->leftSon) {
                newNode = newNode->parent;
                this->rightRotation(newNode);
            }

            newNode->parent->color = NodeColor::black;
            newNode->parent->parent->color = NodeColor::red;

            this->leftRotation(newNode->parent->parent);
            break;
        }
    }

    // Changing root color to black
    this->root->color = NodeColor::black;
}

template<typename T>
void RedBlackTree<T>::remove(const T &value) {
    TreeNode<T> *nodeToDelete = this->findNode(value, this->root);

    // Checking whether node with wanted value exists
    if (nodeToDelete == nullptr) {
        return;
    }

    TreeNode<T> *tmp1;
    TreeNode<T> *tmp2;

    //Checking whether left son or right son are leafs
    if (nodeToDelete->leftSon == this->gandalf || nodeToDelete->rightSon == this->gandalf) {
        tmp1 = nodeToDelete;
    } else {
        tmp1 = this->getSuccessor(nodeToDelete);
    }

    if (tmp1->leftSon != this->gandalf) {
        tmp2 = tmp1->leftSon;
    } else {
        tmp2 = tmp1->rightSon;
    }

    tmp2->parent = tmp1->parent;

    if (tmp1->parent == this->gandalf) {
        this->root = tmp2;
    } else {
        if (tmp1 == tmp1->parent->leftSon) {
            tmp1->parent->leftSon = tmp2;
        } else {
            tmp1->parent->rightSon = tmp2;
        }
    }

    if (tmp1 != nodeToDelete) {
        nodeToDelete->content = tmp1->content;
    }

    if (tmp1->color == NodeColor::black) {
        this->deleteFixColors(tmp2);
    }
}

template<typename T>
void RedBlackTree<T>::print() {
    if (this->root == this->gandalf) {
        std::cout << "Tree is empty\n\n";
        return;
    }

    std::cout << "Contents of tree:\n\n";

    // Calculating tree depth
    size_t depth = 0;
    getDepth(this->root, depth, 0);

    // Calculating maximum size of the tree
    size_t size = pow(2, depth);

    // Creating tree table to get easy access to all nodes
    TreeNode<T> **tree = new TreeNode<T> *[size];
    for (size_t i = 0; i < size; i++) {
        tree[i] = nullptr;
    }

    // Placing nodes inside table
    placeNodes(this->root, tree, 0);

    bool end = false;
    size_t first = 0;
    size_t last = 1;
    size--;

    size_t space = size;

    while (!end) {
        // Printing spaces before each tree level
        std::cout << std::string(space / 2 * 3, ' ');

        // Printing nodes on current tree level
        for (size_t i = first; i < last; i++) {
            if (i >= size) {
                end = true;
                break;
            }

            // Checking if table on current index is not empty
            if (tree[i] != nullptr) {
                // Displaying node
                char color = tree[i]->color == NodeColor::red ? 'R' : 'B';

                std::cout << color << '(' << tree[i]->content << ')' << std::string(space * 3, ' ');
                continue;
            }

            // Displaying empty space instead of node
            std::cout << "   " << std::string(space * 3, ' ');
        }
        std::cout << "\n";

        // Changing indexes or last and first node on each tree level
        first = last;
        last = 2 * last + 1;

        // Changing size of space between nodes
        space = space / 2;
    }

    // Deleting table
    delete[] tree;

    std::cout << "\n\n";
}

template<typename T>
bool RedBlackTree<T>::find(const T &value) {
    // Checking whether tree is empty
    if (this->root == this->gandalf) {
        return false;
    }

    TreeNode<T> *tmp = this->root;

    //While there is a child moving through the tree searching for a match value
    do {
        if (value == tmp->content) {
            return true;
        }

        if (value < tmp->content) {
            tmp = tmp->leftSon;
        }

        if (value > tmp->content) {
            tmp = tmp->rightSon;
        }
    } while (tmp != this->gandalf);

    return false;
}

template<typename T>
TreeNode<T> *RedBlackTree<T>::getSuccessor(TreeNode<T> *node) {
    // Checking whether right son exists
    if (node->rightSon != this->gandalf) {
        return this->min(node->rightSon);
    }

    TreeNode<T> *tmpNode = node->parent;

    //Going up through the tree
    while (tmpNode != this->gandalf && node == tmpNode->rightSon) {
        node = tmpNode;
        tmpNode = tmpNode->parent;
    }
    return tmpNode;
}

template<typename T>
TreeNode<T> *RedBlackTree<T>::min(TreeNode<T> *node) {
    // Looping while left child exists
    while (node->leftSon != this->gandalf) {
        node = node->leftSon;
    }
    return node;
}

template<typename T>
TreeNode<T> *RedBlackTree<T>::findNode(const T &value, TreeNode<T> *node) {
    // Checking whether tree is empty
    if (node == this->gandalf) {
        return nullptr;
    }

    // Checking whether node has right value
    if (value == node->content) {
        return node;
    }

    // Looking for a node in the right branch of the tree
    if (value > node->content) {
        return findNode(value, node->rightSon);
    }

    // Looking for a node in the left branch of the tree
    return findNode(value, node->leftSon);
}

template<typename T>
void RedBlackTree<T>::leftRotation(TreeNode<T> *node) {
    // Creating two temporary pointers to TreeNodes
    TreeNode<T> *newChild;
    TreeNode<T> *newParent;

    newChild = node->rightSon;

    // Checking if right son exits
    if (newChild != this->gandalf) {
        newParent = node->parent;
        node->rightSon = newChild->leftSon;

        // Checking if exists left son of the node's right son
        if (node->rightSon != this->gandalf) {
            node->rightSon->parent = node;
        }

        // Swapping nodes
        newChild->leftSon = node;
        newChild->parent = newParent;
        node->parent = newChild;

        // Checking if parent exists
        if (newParent != this->gandalf) {
            if (newParent->leftSon == node) {
                newParent->leftSon = newChild;
                return;
            }
            newParent->rightSon = newChild;
            return;
        }
        this->root = newChild;
    }
}

template<typename T>
void RedBlackTree<T>::rightRotation(TreeNode<T> *node) {
    // Creating two temporary pointers
    TreeNode<T> *newChild;
    TreeNode<T> *newParent;

    newChild = node->leftSon;

    // Checking whether left child exits
    if (newChild != this->gandalf) {
        newParent = node->parent;
        node->leftSon = newChild->rightSon;

        // Checking whether exists right child of left child
        if (node->leftSon != this->gandalf) {
            node->leftSon->parent = node;
        }

        // Swapping nodes
        newChild->rightSon = node;
        newChild->parent = newParent;
        node->parent = newChild;

        // Checking if parent exists
        if (newParent != this->gandalf) {
            if (newParent->leftSon == node) {
                newParent->leftSon = newChild;
                return;
            }
            newParent->rightSon = newChild;
            return;
        }
        this->root = newChild;
    }
}

template<typename T>
void RedBlackTree<T>::deleteFixColors(TreeNode<T> *node) {
    TreeNode<T> *tmpNode;

    // Fixing tree structure and node colors
    while (node != this->root && node->color == NodeColor::black) {
        if (node == node->parent->leftSon) {
            tmpNode = node->parent->rightSon;

            if (tmpNode->color == NodeColor::red) {
                tmpNode->color = NodeColor::black;
                node->parent->color = NodeColor::red;
                this->leftRotation(node->parent);
                tmpNode = node->parent->rightSon;
            }

            if (tmpNode->leftSon->color == NodeColor::black
                && tmpNode->rightSon->color == NodeColor::black) {
                tmpNode->color = NodeColor::red;
                node = node->parent;
            } else {
                if (tmpNode->rightSon->color == NodeColor::black) {
                    tmpNode->leftSon->color = NodeColor::black;
                    tmpNode->color = NodeColor::red;
                    this->rightRotation(tmpNode);
                    tmpNode = node->parent->rightSon;
                }
                tmpNode->color = tmpNode->parent->color;
                node->parent->color = NodeColor::black;
                tmpNode->rightSon->color = NodeColor::black;
                this->leftRotation(node->parent);
                node = this->root;
            }
        } else {
            tmpNode = node->parent->leftSon;

            if (tmpNode->color == NodeColor::red) {
                tmpNode->color = NodeColor::black;
                node->parent->color = NodeColor::red;
                this->rightRotation(node->parent);
                tmpNode = node->parent->leftSon;
            }

            if (tmpNode->rightSon->color == NodeColor::black
                && tmpNode->leftSon->color == NodeColor::black) {
                tmpNode->color = NodeColor::red;
                node = node->parent;
            } else {
                if (tmpNode->leftSon->color == NodeColor::black) {
                    tmpNode->rightSon->color = NodeColor::black;
                    tmpNode->color = NodeColor::red;
                    this->leftRotation(tmpNode);
                    tmpNode = node->parent->leftSon;
                }
                tmpNode->color = tmpNode->parent->color;
                node->parent->color = NodeColor::black;
                tmpNode->leftSon->color = NodeColor::black;
                this->rightRotation(node->parent);
                node = this->root;
            }
        }
    }
    node->color = NodeColor::black;
}

template<typename T>
void RedBlackTree<T>::deleteTree(TreeNode<T> *node) {
    // Checking whether current node is not the gandalf
    if (node != this->gandalf) {
        deleteTree(node->leftSon);
        deleteTree(node->rightSon);
        delete node;
    }
}

template<typename T>
void RedBlackTree<T>::getDepth(TreeNode<T> *node, size_t &maxDepth, size_t currentDepth) {
    // Increasing depth
    currentDepth++;

    // Checking whether calculated depth is greater than max depth
    if (currentDepth > maxDepth) {
        maxDepth = currentDepth;
    }

    // Checking whether left child is not gandalf
    if (node->leftSon != this->gandalf) {
        getDepth(node->leftSon, maxDepth, currentDepth);
    }

    // Checking whether right child is not gandalf
    if (node->rightSon != this->gandalf) {
        getDepth(node->rightSon, maxDepth, currentDepth);
    }
}

template<typename T>
void RedBlackTree<T>::placeNodes(TreeNode<T> *node, TreeNode<T> **tree, size_t index) {
    // Placing node in table
    tree[index] = node;

    // Checking whether left child exists
    if (node->leftSon != this->gandalf) {
        placeNodes(node->leftSon, tree, 2 * index + 1);
    }

    // Check whether right child exists
    if (node->rightSon != this->gandalf) {
        placeNodes(node->rightSon, tree, 2 * index + 2);
    }
}


#endif //SDIZO_PROJECT_1_BLACK_RED_TREE_TPP