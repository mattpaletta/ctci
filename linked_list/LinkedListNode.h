//
// Created by Matthew Paletta on 2019-01-21.
//

#ifndef CTCI_LINKEDLISTNODE_H
#define CTCI_LINKEDLISTNODE_H

template<class T>
class LinkedListNode {
    T value;
    LinkedListNode* next;

    LinkedListNode();
    ~LinkedListNode();

    LinkedListNode(T value, LinkedListNode* next);
    LinkedListNode(T value);
};

#endif //CTCI_LINKEDLISTNODE_H
