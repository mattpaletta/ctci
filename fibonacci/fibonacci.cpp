//
// Created by Matthew Paletta on 2019-02-18.
//

#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <unistd.h>

unsigned long fibonacci_basic(unsigned long n) {
    if (n < 2) {
        return n;
    } else {
        return fibonacci_basic(n - 1) + fibonacci_basic(n - 2);
    }
}

unsigned long finonacci_dynamic(unsigned long n, std::vector<unsigned long> *cache) {
    if (cache->empty()) {
        // Prefill the cache
        cache->push_back(fibonacci_basic(0));
        cache->push_back(fibonacci_basic(1));
        cache->push_back(fibonacci_basic(2));
    }

    if (n < cache->size()) {
        return cache->at(n);
    } else {
        auto n0 = finonacci_dynamic(n - 1, cache) + finonacci_dynamic(n - 2, cache);
        cache->push_back(n0);
        return n0;
    }
}

int main() {
    unsigned long N = 40;

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
    if (n1 == n2) {
        std::cout << "Result is: " << n1 << std::endl;
    } else {
        std::cout << "Results do not match " << n1 << ", " << n2 <<  std::endl;
    }

    return 0;
}