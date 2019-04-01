//
// Created by Matthew Paletta on 2019-03-25.
//

#include "BTree.h"
#include "BTreeNode.h"

int main() {
    constexpr BTree<int> tree = BTree(BTreeNode<int>(1));
    tree.insert(BTreeNode<int>(1));
    tree.insert(BTreeNode<int>(2));
    tree.insert(BTreeNode<int>(3));

    return 0;
}