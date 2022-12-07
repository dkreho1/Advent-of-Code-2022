#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#define PART2

bool isNumber(char c) {
    c -= '0';
    return ((c >= 0) && (c <= 9));
}

int main() {
    std::ifstream in(R"(C:\Users\User\CLionProjects\AdventOfCode\Day7\inputDay7.txt)");

    std::vector<std::string> tree;

    uint64_t indentSize{};

    while (true) {
        if(in.peek() == '$') {
            std::string command, tmp;
            in >> tmp >> command;
            if (command == "cd") {
                std::string dirName;
                in >> dirName;

                if (dirName == "..") {
                    indentSize -= 2;
                } else {
                    tree.push_back(std::string(indentSize, ' ') + std::string("- ")
                                   + dirName + std::string(" (dir)"));
                    indentSize += 2;
                }
            }
        } else if (isNumber(in.peek())) {
            uint64_t size;
            std::string fileName;
            in >> size >> fileName;
            tree.push_back(std::string(indentSize, ' ') + std::string("- ")
                           + fileName + std::string(" (file, size=") + std::to_string(size)
                           + std::string(")"));
        } else {
            std::string line;
            std::getline(in, line);
        }

        if (in.peek() == EOF) {
            break;
        }
    }

    uint64_t size{};
    for (int64_t i{ tree.size() - 1 }; i >= 0; i--) {
        std::size_t found = tree.at(i).find("=");
        if (found == std::string::npos) {
            tree.at(i).insert(tree.at(i).length() - 1,
                              std::string(", size=") + std::to_string(size));
            size = 0;
        } else {
            size += std::stoull(tree.at(i).substr(found + 1, tree.at(i).size() - found - 2));
            tree.erase(tree.begin() + i);
        }
    }

    int maxLevel{};
    for (const auto& str : tree) {
        std::size_t found = str.find("-");
        if (found > maxLevel) {
            maxLevel = found;
        }
    }

    for (int j{maxLevel}; j >= 0; j -= 2) {
        size = 0;
        for (int64_t i{ tree.size() - 1 }; i >= 0; i--) {
            std::size_t foundDash = tree.at(i).find("-");
            std::size_t found = tree.at(i).find("=");
            if (foundDash == j) {
                size += std::stoull(tree.at(i).substr(found + 1, tree.at(i).size() - found - 2));
            } else if (foundDash < j) {
                uint64_t tmp = std::stoull(tree.at(i).substr(found + 1, tree.at(i).size() - found - 2));
                size += tmp;
                tree.at(i).erase(found + 1);

                tree.at(i).insert(tree.at(i).length(),
                                  std::to_string(size) + std::string(")"));

                size = 0;
            }
        }
    }

#ifdef PART2
    const uint64_t needed{30000000}, available{70000000};

    std::size_t found = tree.at(0).find("=");
    uint64_t needToFree{ needed -
        (available - std::stoull(tree.at(0).substr(found + 1, tree.at(0).size() - found - 2))) };

    uint64_t min{available};
    for (const auto& str : tree) {
        std::size_t found2 = str.find("=");
        uint64_t size = std::stoull(str.substr(found2 + 1, str.size() - found2 - 2));

        if (size >= needToFree && min > size) {
            min = size;
        }
    }

    std::cout << min;
#else
    uint64_t sumOfSizes{};
    for (const auto& str : tree) {
        std::size_t found = str.find("=");
        uint64_t size = std::stoull(str.substr(found + 1, str.size() - found - 2));
        if (size <= 100000) {
            sumOfSizes += size;
        }
    }

    std::cout << sumOfSizes;
#endif

    return 0;
}
