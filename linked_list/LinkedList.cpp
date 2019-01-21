//
// Created by Matthew Paletta on 2019-01-21.
//

#include "LinkedListNode.h"
#include "LinkedList.h"

#include <stdlib.h>

template<class T>
LinkedList<T>::LinkedList() {
    this->head = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(LinkedListNode<T>* node) {
    this->head = node;
}

template<class T>
LinkedList<T>::~LinkedList() {
    while (!this->isEmpty()) {
        // Deallocate all the nodes first.
        this->pop();
    }
}

template <class T>
int LinkedList<T>::size() {
    if (this->head == nullptr) {
        return 0;
    } else {
        int size = 0;
        LinkedListNode<T>* curr = this->head;
        while(curr->next != nullptr) {
            size++;
        }

        return size;
    }
}

template<class T>
void LinkedList<T>::add(T value) {
    return this->add(0, value);
}

template<class T>
void LinkedList<T>::add(int index, T value) {
    LinkedListNode<T>* insert = LinkedListNode<T>(value);

    if (this->isEmpty()) {
        this->head = insert;
    } else {
        int current_index = 0;
        LinkedListNode<T>* curr = this->head;
        while (curr->next != nullptr && current_index < index) {
            current_index++;
            curr = curr->next;
        }

        if (current_index == index) {
            // curr is the old one we are inserting after.
            insert->next = curr->next;
            curr->next = insert;
        }
    }
}

template<class T>
T LinkedList<T>::get(int index) {
    if (this->isEmpty()) {
        this->head = nullptr;
    } else {
        int current_index = 0;
        LinkedListNode<T>* curr = this->head;
        while (curr->next != nullptr && current_index < index) {
            current_index++;
            curr = curr->next;
        }

        return curr->value;
    }
}

template<class T>
bool LinkedList<T>::isEmpty() {
    return this->size() == 0;
}

template<class T>
T LinkedList<T>::pop() {
    return this->remove(0);
}

template<class T>
T LinkedList<T>::remove(int index) {
    // If it's empty, we do nothing!

    if (!this->isEmpty()) {
        int current_index = 0;
        LinkedListNode<T>* curr = this->head;
        while (curr->next != nullptr && current_index < index) {
            current_index++;
            curr = curr->next;
        }

        if (current_index == index) {
            // If we missed it, do nothing.
            LinkedListNode<T>* oldNode = curr->next;
            curr->next = oldNode->next;
            T oldValue = oldNode->value;
            delete oldNode;
            return oldValue;
        }
    }

    return nullptr;
}

