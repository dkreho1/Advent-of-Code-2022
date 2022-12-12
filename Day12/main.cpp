#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

void move(const std::vector<std::string>& heightmap, std::vector<std::vector<bool>>& visited,
          std::vector<uint16_t>& steps, const std::pair<uint16_t, uint16_t>& S,
          const std::pair<uint16_t, uint16_t>& E, uint16_t previousSteps, uint16_t i, uint16_t j) {

    visited.at(i).at(j) = true;

    if (i == E.first && j == E.second) {
        steps.push_back(previousSteps + 1);
        return;
    }

    if (i + 1 != heightmap.size() && !visited.at(i + 1).at(j)
        && heightmap.at(i + 1).at(j) - heightmap.at(i).at(j) == 1) {
        move(heightmap, visited, steps, S, E, previousSteps + 1, i + 1, j);
        visited.at(i + 1).at(j) = false;
    }

    if (j + 1 != heightmap.at(0).size() && !visited.at(i).at(j + 1)
        && heightmap.at(i).at(j + 1) - heightmap.at(i).at(j) == 1) {
        move(heightmap, visited, steps, S, E, previousSteps + 1, i, j + 1);
        visited.at(i).at(j + 1) = false;
    }

    if (i != 0 && !visited.at(i - 1).at(j)
        && heightmap.at(i - 1).at(j) - heightmap.at(i).at(j) == 1) {
        move(heightmap, visited, steps, S, E, previousSteps + 1, i - 1, j);
        visited.at(i - 1).at(j) = false;
    }

    if (j != 0 && !visited.at(i).at(j - 1)
        && heightmap.at(i).at(j - 1) - heightmap.at(i).at(j) == 1) {
        move(heightmap, visited, steps, S, E, previousSteps + 1, i, j - 1);
        visited.at(i).at(j - 1) = false;
    }

    if (i + 1 != heightmap.size() && !visited.at(i + 1).at(j)
        && heightmap.at(i + 1).at(j) - heightmap.at(i).at(j) == 0) {
        move(heightmap, visited, steps, S, E, previousSteps + 1, i + 1, j);
        visited.at(i + 1).at(j) = false;
    }

    if (j + 1 != heightmap.at(0).size() && !visited.at(i).at(j + 1)
        && heightmap.at(i).at(j + 1) - heightmap.at(i).at(j) == 0) {
        move(heightmap, visited, steps, S, E, previousSteps + 1, i, j + 1);
        visited.at(i).at(j + 1) = false;
    }

    if (i != 0 && !visited.at(i - 1).at(j)
        && heightmap.at(i - 1).at(j) - heightmap.at(i).at(j) == 0) {
        move(heightmap, visited, steps, S, E, previousSteps + 1, i - 1, j);
        visited.at(i - 1).at(j) = false;
    }

    if (j != 0 && !visited.at(i).at(j - 1)
        && heightmap.at(i).at(j - 1) - heightmap.at(i).at(j) == 0) {
        move(heightmap, visited, steps, S, E, previousSteps + 1, i, j - 1);
        visited.at(i).at(j - 1) = false;
    }
}

int main() {
    std::ifstream in(R"(C:\Users\User\CLionProjects\AdventOfCode\Day12\inputDay12.txt)");

    std::vector<std::string> heightmap;
    std::pair<uint16_t, uint16_t> S, E;


    while (!in.eof()) {
        std::string input;
        in >> input;
        std::size_t findS{input.find('S')};
        if (findS != std::string::npos) {
            S = {heightmap.size(), findS};
        }
        std::size_t findE{input.find('E')};
        if (findE != std::string::npos) {
            E = {heightmap.size(), findE};
        }
        heightmap.push_back(input);
    }

    std::vector<uint16_t> steps;

    heightmap.at(S.first).at(S.second) = 'a';
    heightmap.at(E.first).at(E.second) = 'z';

    std::vector<std::vector<bool>> visited(heightmap.size(),
                                           std::vector<bool>(heightmap.at(0).size(), false));

    move(heightmap, visited, steps, S, E, 0, S.first, S.second);

    std::cout << *std::min_element(steps.begin(), steps.end()) - 1;

    return 0;
}
