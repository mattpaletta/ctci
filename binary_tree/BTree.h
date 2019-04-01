//
// Created by Matthew Paletta on 2019-01-24.
//

#ifndef CTCI_RBTREE_H
#define CTCI_RBTREE_H

#include "BTreeNode.h"

template<class T>
class BTree {
private:
    const BTreeNode<T>* head;
    constexpr void insert(BTreeNode<T>* root, BTreeNode<T>* node);
    constexpr bool exists(BTreeNode<T>* root, BTreeNode<T>* node);
    constexpr BTreeNode<T>* remove(BTreeNode<T>* root, BTreeNode<T>* node);

public:
    constexpr BTree(BTreeNode<T>* head);

    constexpr void insert(BTreeNode<T>* node);
    constexpr bool exists(BTreeNode<T>* node);
    constexpr void remove(BTreeNode<T>* node);
};

template<class T>
constexpr BTree<T>::BTree(BTreeNode<T>* head) {
    this->head = head;
}


#endif //CTCI_RBTREE_H
