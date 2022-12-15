#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#define PART2

int main() {
    std::ifstream in(R"(C:\Users\User\CLionProjects\AdventOfCode\Day14\inputDay14.txt)");

    std::vector<std::vector<char>> map(200, std::vector<char>(1000, ' '));

    std::vector<std::pair<uint64_t, uint64_t>> points;
    uint64_t yMax{};
    while (true) {
        uint64_t x, y;
        char waste;

        in >> x >> waste >> y;
        points.push_back({x, y});

        if (yMax < y) {
            yMax = y;
        }

        char peek = in.peek();
        if (peek == '\n' || peek == EOF) {
            for (int i{}; i + 1 < points.size(); i++) {
                if (points.at(i).first == points.at(i + 1).first) {
                    uint64_t start, end;
                    if (points.at(i).second > points.at(i + 1).second) {
                        start = points.at(i + 1).second;
                        end = points.at(i).second;
                    } else {
                        start = points.at(i).second;
                        end = points.at(i + 1).second;
                    }
                    for (uint64_t j{start}; j <= end; j++) {
                        map.at(j).at(points.at(i).first) = '#';
                    }
                }
                if (points.at(i).second == points.at(i + 1).second) {
                    uint64_t start, end;
                    if (points.at(i).first > points.at(i + 1).first) {
                        start = points.at(i + 1).first;
                        end = points.at(i).first;
                    } else {
                        start = points.at(i).first;
                        end = points.at(i + 1).first;
                    }
                    for (uint64_t j{start}; j <= end; j++) {
                        map.at(points.at(i).second).at(j) = '#';
                    }
                }
            }
            points.erase(points.begin(), points.end());
            if (peek == EOF) {
                break;
            }
        } else {
            in >> waste >> waste;
        }
    }

#ifdef PART2
    yMax += 2;

    for (int i{}; i < map.at(yMax).size(); i++) {
        map.at(yMax).at(i) = '#';
    }
#endif

    uint64_t sandCount{};
    bool end{ false };
    while (!end) {
        int64_t y{}, x{500};
        sandCount++;

#ifdef PART2
        if (map.at(y).at(x) == 'o') {
            end = true;
            sandCount--;
            break;
        }
#endif

        while (true) {
#ifndef PART2
            if (y == yMax + 1) {
                end = true;
                sandCount--;
                break;
            }
#endif

            if (map.at(y).at(x) == ' ') {
                y++;
                continue;
            }

            if (map.at(y).at(x - 1) == ' ') {
                y++;
                x--;
                continue;
            }

            if (map.at(y).at(x + 1) == ' ') {
                y++;
                x++;
                continue;
            }

            y--;
            map.at(y).at(x) = 'o';
            break;
        }
    }

    std::cout << sandCount;

    return 0;
}
