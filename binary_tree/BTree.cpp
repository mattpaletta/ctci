//
// Created by Matthew Paletta on 2019-01-24.
//

#include "BTree.h"


template<class T>
BTree<T>::BTree() {
    this->head = nullptr;
}

template<class T>
void BTree<T>::insert(BTreeNode<T> *node) {
    if (this->head == nullptr) {
        // We have an empty tree
        this->head = node;
    } else {
        // We have at least one item in the tree.
        return this->insert(this->head, node);
    }
}


template<class T>
void BTree<T>::insert(BTreeNode<T> *root, BTreeNode<T> *node) {
    // We have at least one node, we continue the search from 'root'
    if (root->value <= node->value && root->lChild != nullptr) {
        // It's a smaller value, so we go left
        this->insert(root->lChild, node);

    } else if (root->value <= node->value) {
        // It's a smaller value, so we go left, and we insert it here
        root->rChild = node;

    } else if (root->value > node->value && root->rChild != nullptr) {
        // It's a greater value, so we go right
        this->insert(root->rChild, node);

    } else if (root->value > node->value) {
        // It's a greater value, but we add it here.
        root->rChild = node;
    }
}

template<class T>
bool BTree<T>::exists(BTreeNode<T> *node) {
    if (this->head == nullptr) {
        // We have an empty tree
        return false;
    } else {
        // We have at least one item in the tree.
        return this->exists(this->head, node);
    }
}


template<class T>
bool BTree<T>::exists(BTreeNode<T> *root, BTreeNode<T> *node) {

    if (root->value == node->value) {
        // It's a smaller value, so we go left
        return true;

    } else if (root->value <= node->value && root->lChild == nullptr) {
        // It's a smaller value, but we don't have anything smaller
        return false;

    } else if (root->value <= node->value) {
        // It's a smaller value, so we go left
        return this->exists(root->lChild, node);

    } else if (root->value > node->value && root->rChild == nullptr) {
        // It's a greater value, but we don't have anything larger.
        return false;

    } else if (root->value > node->value) {
        // It's a greater value, so we go right.
        return this->exists(root->rChild, node);
    } else {
        // Both children are empty, and it's not the same value, so we don't have it.
        return false;
    }
}


template<class T>
void BTree<T>::remove(BTreeNode<T> *node) {
    if (this->head != nullptr) {
        this->remove(this->head, node);
    }
}

template<class T>
BTreeNode<T>* BTree<T>::remove(BTreeNode<T> *root, BTreeNode<T> *node) {
    if (root->value == node->value) {
        // We found the value, so we remove it.

        // Reattach the children.
        if (root->lChild == nullptr && root->rChild != nullptr) {
            // We only have the right child
            return root->rChild;

        } else if (root->rChild == nullptr && root->lChild != nullptr) {
            // We only have a left child, easy!
            return root->lChild;

        } else if (root->rChild == nullptr && root->lChild == nullptr) {
            // We don't have any children, easy!
            return nullptr;
        } else {
            // We have a left and right, make the left one the parent of the right one.
            this->insert(root->lChild, root->rChild);
            return root->lChild;
        }

    } else if (root->value <= node->value && root->lChild == nullptr) {
        // It's a smaller value, but we don't have anything smaller
        return nullptr;

    } else if (root->value <= node->value) {
        // It's a smaller value, so we go left
        auto* removed = this->remove(root->lChild, node);

        if (removed != nullptr) {
            // Skip over that node
            root->lChild = removed;
            return nullptr;
        }

    } else if (root->value > node->value && root->rChild == nullptr) {
        // It's a greater value, but we don't have anything larger.
        return nullptr;

    } else if (root->value > node->value) {
        // It's a greater value, so we go right.
        auto* removed = this->remove(root->rChild, node);

        if (removed != nullptr) {
            // Skip over that node
            root->rChild = removed;
            return nullptr;
        }

    } else {
        // Both children are empty, and it's not the same value, so we don't have it.
        return nullptr;
    }
}

