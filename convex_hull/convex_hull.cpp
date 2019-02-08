//
// Created by Matthew Paletta on 2019-01-21.
//

// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>     /* strtol */
#include <cstdlib>
#include <ctime>
#include <iostream>

typedef struct {
    int x;
    int y;
} point;

std::vector<std::vector<point>> extract_points_from_file(const std::string &filepath) {

    std::vector<std::vector<point>> all_examples = {};

    std::ifstream myfile (filepath);
    if (myfile.is_open()) {
        std::string line;


        // TODO: For now, assume this parses the file correctly.
        getline(myfile, line);
        int num_examples = stoi(line);
        for (int i = 0; i < num_examples; i++) {
            std::vector<point> points = {};

            getline(myfile, line);
            int num_points = stoi(line);
            for (int j = 0; j < num_points; j++) {
                getline(myfile, line, ' ');
                int x = stoi(line);

                getline(myfile, line, ' ');
                int y = stoi(line);

                points.push_back({x, y});
            }

            all_examples.push_back(points);
        }

        myfile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }

    return all_examples;
}

int intRand() {
    return rand() * RAND_MAX + 1;
}

std::vector<point> generateRand(int size) {
    std::vector<point> output = {};
    for (int i=0; i < size; i++) {
        output.push_back({intRand(), intRand()});
    }
    return output;
}

point operator-(const point &A, const point &B) {
    return {B.x - A.x, B.y - A.y};
}


template <typename T>
std::vector<T> operator+(const std::vector<T> &A, const std::vector<T> &B) {
    std::vector<T> AB;
    AB.reserve( A.size() + B.size() );                // preallocate memory
    AB.insert( AB.end(), A.begin(), A.end() );        // add A;
    AB.insert( AB.end(), B.begin(), B.end() );        // add B;
    return AB;
}


template <typename T>
std::vector<T> operator+(const T  &A, const std::vector<T> &B) {
    std::vector<T> AB;
    AB.reserve( B.size() + 1);                // preallocate memory
    AB.push_back(A);
    AB.insert( AB.end(), B.begin(), B.end() );        // add A;
    return AB;
}

template <typename T>
std::vector<T> operator+(const std::vector<T> &A, const T &B) {
    std::vector<T> AB;
    AB.reserve( A.size() + 1);                // preallocate memory
    AB.insert( AB.end(), A.begin(), A.end() );        // add A;
    AB.push_back(B);
    return AB;
}

template <typename T>
std::vector<T> operator-(const std::vector<T> &A, const std::vector<T> &B) {
    std::vector<T> AB;
    for (auto& [a, b] : zip(A, B)) {
        AB.push_back(b - a);
    }

    return AB;
}

template <typename T>
std::vector<T> &operator+=(std::vector<T> &A, const std::vector<T> &B) {
    A.reserve( A.size() + B.size() );                // preallocate memory without erase original data
    A.insert( A.end(), B.begin(), B.end() );         // add B;
    return A;                                        // here A could be named AB
}

// Function that return
// dot product of two vector array.
int dotProduct(const std::vector<int> &vect_A, const std::vector<int> &vect_B) {
    int product = 0;

    // Loop for calculate cot product
    for (unsigned long i = 0; i < vect_A.size(); i++) {
        product += vect_A.at(i) * vect_B.at(i);
    }
    return product;
}

// Function to find
// cross product of two vector array.
inline int crossProduct(point vect_A, point vect_B) {
    return (vect_A.x * vect_B.y) - (vect_A.y * vect_B.x);
}

/*
 * def split(u, v, points):
    # return points on left side of UV
    return [p for p in points if np.cross(p - u, v - u) < 0]
 */

std::vector<point> split(const point u, const point v, const std::vector<point> &points) {
    std::vector<point> bar;
    std::copy_if (points.begin(), points.end(), std::back_inserter(bar), [u, v](point p) {
        return crossProduct(p - u, v - u) > 0;
    });

    return bar;
}

template<class T>
point max(const std::vector<point> &points, T f) {
    point max_point = points.at(0);
    int max = f(points.at(0));

    for (auto& curr_point : points) {
        int curr = f(curr_point);
        if (curr >= max) {
            max = curr;
            max_point = curr_point;
        }
    }

    return max_point;
}

template<class T>
point min(const std::vector<point> &points, T f) {
    point min_point = points.at(0);
    int min = f(points.at(0));

    for (auto& curr_point : points) {
        int curr = f(curr_point);
        if (curr < min) {
            min = curr;
            min_point = curr_point;
        }
    }

    return min_point;
}

/*
 * def extend(u, v, points):
    if not points:
        return []

    # find furthest point W, and split search to WV, UW
    w = min(points, key=lambda p: np.cross(p - u, v - u))
    p1, p2 = split(w, v, points), split(u, w, points)
    return extend(w, v, p1) + [w] + extend(u, w, p2)
 */

std::vector<point> extend(const point u, const point v, const std::vector<point> &points) {
    if (points.empty()) {
        return std::vector<point> {};
    }

    point w = min(points, [u, v](point p) {
        return crossProduct(p - u, v - u);
    });

    auto p1 = split(w, v, points);
    auto p2 = split(u, w, points);
    return extend(w, v, p1) + w + extend(u, w, p2);
}

/*
 * def convex_hull(points):
    # find two hull points, U, V, and split to left and right search
    u = min(points, key=lambda p: p[0])
    v = max(points, key=lambda p: p[0])
    left, right = split(u, v, points), split(v, u, points)

    # find convex hull on each side
    return [v] + extend(u, v, left) + [u] + extend(v, u, right) + [v]
 */

std::vector<point> compute_convex_hulls(const std::vector<point> &points) {
    point u = min(points, [](point p) { return p.x; });
    point v = max(points, [](point p) { return p.x; });

    auto left = split(u, v, points);
    auto right = split(v, u, points);

    return v + extend(u, v, left) + u + extend(v, u, right) + v;
}

void convex_hulls(const std::string &filepath) {
    auto examples = extract_points_from_file(filepath);
    for (const auto &points : examples) {
        std::vector<point> result = compute_convex_hulls(points);

        std::cout << "Printing next example: " << std::endl;
        for (const auto &point : result) {
            std::cout << point.x << ' ' << point.y << std::endl;
        }
    }
}

int main() {
    convex_hulls("example.txt");

    auto random_points = generateRand(5);
    std::vector<point> result = compute_convex_hulls(random_points);

    std::cout << "Printing next example: " << std::endl;
    for (const auto &point : result) {
        std::cout << point.x << ' ' << point.y << std::endl;
    }

    return 0;
}
