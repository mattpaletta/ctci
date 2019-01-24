//
// Created by Matthew Paletta on 2019-01-24.
//

#include "BTreeNode.h"

template<class T>
BTreeNode<T>::BTreeNode(T value) {
    this->value = value;
    this->lChild = nullptr;
    this->rChild = nullptr;
}

template<class T>
BTreeNode<T>::BTreeNode(T value, BTreeNode lChild, BTreeNode rChild) {
    this->value = value;
    this->lChild = lChild;
    this->rChild = rChild;
}

template<class T>
BTreeNode<T>::~BTreeNode() {
    this->lChild = nullptr;
    this->rChild = nullptr;
}
