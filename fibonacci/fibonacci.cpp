//
// Created by Matthew Paletta on 2019-02-18.
//

#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <unistd.h>

int fibonacci_basic(int n) {
    if (n < 2) {
        return n;
    } else {
        return fibonacci_basic(n - 1) + fibonacci_basic(n - 2);
    }
}

unsigned long finonacci_dynamic(unsigned long n, std::vector<unsigned long> *cache) {
    if (n < 2 && n >= cache->size()) {
        cache->push_back(n);
        return n;
    } else if (n < cache->size()) {
        return cache->at(n);
    } else {
        auto n0 = finonacci_dynamic(n - 1, cache) + finonacci_dynamic(n - 2, cache);
        cache->push_back(n0);
        return n0;
    }
}

int main() {
    int N = 10;

    std::cout << "Running basic" << std::endl;
    auto start = std::chrono::steady_clock::now();
    auto n1 = fibonacci_basic(N);
    auto end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time in milliseconds : "
         << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
         << " ms" << std::endl;

    std::cout << "Running dynamic" << std::endl;
    std::vector<unsigned long> cache = {};
    start = std::chrono::steady_clock::now();
    auto n2 = finonacci_dynamic(N, &cache);
    end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time in milliseconds : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;
    if ((unsigned long) n1 == n2) {
        std::cout << "Result is: %i" << n1 << std::endl;
    } else {
        std::cout << "Results do not match %i" << n1 << ", %i" << n2 <<  std::endl;
    }

    return 0;
}