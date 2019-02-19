//
// Created by Matthew Paletta on 2019-02-07.
//

#include <iostream>
#include "string"
#include "vector"

/*
 * def hanoi(n, source, helper, target):
    if n > 0:
        # move tower of size n - 1 to helper:
        hanoi(n - 1, source, target, helper)
        # move disk from source peg to target peg
        if source:
            target.append(source.pop())
        # move tower of size n-1 from helper to target
        hanoi(n - 1, helper, source, target)
 */

std::vector<int> hanoi(int n, std::vector<int> &source, std::vector<int> &helper, std::vector<int> &target) {
    if (n > 0) {
        // Move tower of size n - 1 to helper
        hanoi(n - 1, source, target, helper);

        if (!source.empty()) {
            target.push_back(source.back());
            source.pop_back();
        }

        hanoi(n - 1, helper, source, target);
    }

    return target;
}

std::vector<int> range(unsigned long max) {
    std::vector<int> AB = {};
    AB.reserve(max);
    for (int i = 0; i < max; i++) {
        AB.push_back(i);
    }

    return AB;
}

int main() {
    std::vector<int> source = range(20);
    std::vector<int> target = {};
    std::vector<int> helper = {};

    hanoi(source.size(), source, helper, target);

    std::cout << "Printing result: " << std::endl;
    for (const auto &block : target) {
        std::cout << block << std::endl;
    }
    return 0;
}