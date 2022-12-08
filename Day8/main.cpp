#include <iostream>
#include <fstream>
#include <vector>
#define PART2

int main() {
    std::ifstream in(R"(C:\Users\User\CLionProjects\AdventOfCode\Day8\inputDay8.txt)");

    std::vector<std::vector<uint8_t>> map;

    while (!in.eof()) {
        std::vector<uint8_t> row;
        while (in.peek() != '\n' && in.peek() != EOF) {
            row.push_back(in.get() - '0');
        }
        map.push_back(row);
        in.get();
    }

#ifdef PART2
    uint64_t maxScore{};
#else
    uint64_t visibleCount{ 2 * map.size() + 2 * map.at(0).size() - 4 };
#endif


    for (int i{1}; i + 1 < map.size(); i++) {
        for (int j{1}; j + 1 < map.at(i).size(); j++) {
            uint8_t currentTree{ map.at(i).at(j) };

#ifdef PART2
            uint64_t score{ 1 };
            int k{};
            for (k = i - 1; k >= 0; k--) {
                if (currentTree <= map.at(k).at(j)) {
                    k--;
                    break;
                }
            }
            score *= (i - (k + 1));

            for (k = i + 1; k < map.size(); k++) {
                if (currentTree <= map.at(k).at(j)) {
                    k++;
                    break;
                }
            }
            score *= ((k - 1) - i);

            for (k = j - 1; k >= 0; k--) {
                if (currentTree <= map.at(i).at(k)) {
                    k--;
                    break;
                }
            }
            score *= (j - (k + 1));

            for (k = j + 1; k < map.at(i).size(); k++) {
                if (currentTree <= map.at(i).at(k)) {
                    k++;
                    break;
                }
            }
            score *= ((k - 1) - j);

            if (score > maxScore) {
                maxScore = score;
            }
#else
            bool notVisible{ false };
            for (int k{i - 1}; k >= 0; k--) {
                if (currentTree <= map.at(k).at(j)) {
                    notVisible = true;
                    break;
                }
            }

            if (!notVisible) {
                visibleCount++;
                continue;
            }

            notVisible = false;
            for (int k{i + 1}; k < map.size(); k++) {
                if (currentTree <= map.at(k).at(j)) {
                    notVisible = true;
                    break;
                }
            }

            if (!notVisible) {
                visibleCount++;
                continue;
            }

            notVisible = false;
            for (int k{j - 1}; k >= 0; k--) {
                if (currentTree <= map.at(i).at(k)) {
                    notVisible = true;
                    break;
                }
            }

            if (!notVisible) {
                visibleCount++;
                continue;
            }

            notVisible = false;
            for (int k{j + 1}; k < map.at(i).size(); k++) {
                if (currentTree <= map.at(i).at(k)) {
                    notVisible = true;
                    break;
                }
            }

            if (!notVisible) {
                visibleCount++;
                continue;
            }
#endif
        }
    }

#ifdef PART2
    std::cout << maxScore;
#else
    std::cout << visibleCount;
#endif

    return 0;
}
