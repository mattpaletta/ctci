//
// Created by Matthew Paletta on 2019-01-21.
//

#include "LinkedListNode.h"

#ifndef CTCI_LINKEDLIST_H
#define CTCI_LINKEDLIST_H

template <class T>
class LinkedList {
private:
    LinkedListNode<T>* head;

    bool isEmpty();
    int size();

public:
    LinkedList();
    LinkedList(LinkedListNode<T>* node);

    ~LinkedList();

    void add(T value);
    void add(int index, T value);

    T get(int index);

    T pop();
    T remove(int index);
};


#endif //CTCI_LINKEDLIST_H
