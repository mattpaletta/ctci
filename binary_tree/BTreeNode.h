//
// Created by Matthew Paletta on 2019-01-24.
//

#ifndef CTCI_RBTREENODE_H
#define CTCI_RBTREENODE_H

template <class T>
class BTreeNode {
private:
    T value;
    BTreeNode* lChild;
    BTreeNode* rChild;

public:
    BTreeNode(T value);
    BTreeNode(T value, BTreeNode lChild, BTreeNode rChild);

    ~BTreeNode();
};


#endif //CTCI_RBTREENODE_H
