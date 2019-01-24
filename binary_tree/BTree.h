//
// Created by Matthew Paletta on 2019-01-24.
//

#ifndef CTCI_RBTREE_H
#define CTCI_RBTREE_H

#include "BTreeNode.h"

template<class T>
class BTree {
private:
    BTreeNode<T>* head;
    void insert(BTreeNode<T>* root, BTreeNode<T>* node);
    bool exists(BTreeNode<T>* root, BTreeNode<T>* node);
    BTreeNode<T>* remove(BTreeNode<T>* root, BTreeNode<T>* node);

public:
    BTree();

    void insert(BTreeNode<T>* node);
    bool exists(BTreeNode<T>* node);
    void remove(BTreeNode<T>* node);
};



#endif //CTCI_RBTREE_H
