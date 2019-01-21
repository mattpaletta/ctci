//
// Created by Matthew Paletta on 2019-01-21.
//

#include "LinkedListNode.h"
#include <stdlib.h>

template<class T>
LinkedListNode<T>::LinkedListNode() {
    this->value = nullptr;
    this->next = nullptr;
}

template<class T>
LinkedListNode<T>::LinkedListNode(T value) {
    this->value = value;
    this->next = nullptr;
}

template<class T>
LinkedListNode<T>::LinkedListNode(T value, LinkedListNode* next) {
    this->value = value;
    this->next = next;
}

template<class T>
LinkedListNode<T>::~LinkedListNode() {
    this->next = nullptr;
    this->value = nullptr;
}


