//
// Created by Matthew Paletta on 2019-01-21.
//

// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>     /* strtol */

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

void compute_convex_hull(const std::string &filepath) {
    auto examples = extract_points_from_file(filepath);

    for (const auto &points : examples) {
        // Find the center

        // Compute the distance from the center

        // Take the maximum points, with the greater x,y
    }
}