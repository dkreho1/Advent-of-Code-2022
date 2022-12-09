#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#define PART2

const double eps{ 1e-5 };

struct Position {
    int64_t x{};
    int64_t y{};

    bool isNextTo(const Position& pos) const {
        return std::abs(this->x - pos.x) <= 1 && std::abs(this->y - pos.y) <= 1;
    }

    static double distance(const Position& pos1, const Position& pos2) {
        return std::sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
    }
};

bool operator==(const Position& pos1, const Position& pos2) {
    return pos1.x == pos2.x && pos1.y == pos2.y;
}


int main() {
    std::ifstream in(R"(C:\Users\User\CLionProjects\AdventOfCode\Day9\inputDay9.txt)");

    std::vector<Position> visited;

#ifdef PART2
    const uint8_t ropeSize{ 10 };
#else
    const uint8_t ropeSize{ 2 };
#endif

    std::vector<Position> rope(ropeSize);
    visited.push_back(rope.at(rope.size() - 1));


    while (!in.eof()) {
        char direction;
        uint64_t amount;

        in >> direction >> amount;

        for (int i{}; i < amount; i++) {
            switch (direction) {
                case 'R':
                    rope.at(0).x++;
                    break;
                case 'L':
                    rope.at(0).x--;
                    break;
                case 'U':
                    rope.at(0).y++;
                    break;
                case 'D':
                    rope.at(0).y--;
                    break;
                default:
                    break;
            }

            for (int j{ 1 }; j < rope.size(); j++) {
                if (rope.at(j).isNextTo(rope.at(j - 1))) {
                    continue;
                }

                if (std::abs(Position::distance(rope.at(j - 1), rope.at(j)) - 2) < eps) {
                    rope.at(j).x += (rope.at(j - 1).x - rope.at(j).x) / 2;
                    rope.at(j).y += (rope.at(j - 1).y - rope.at(j).y) / 2;
                } else {
                    int64_t move{rope.at(j - 1).x - rope.at(j).x};
                    if (std::abs(move) == 1) {
                        move = ((move > 0) ? (move + 1) : (move - 1));
                    }
                    rope.at(j).x += (move) / 2;

                    move = rope.at(j - 1).y - rope.at(j).y;
                    if (std::abs(move) == 1) {
                        move = ((move > 0) ? (move + 1) : (move - 1));
                    }
                    rope.at(j).y += (move) / 2;
                }
            }

            if (std::find(visited.begin(), visited.end(), rope.at(rope.size() - 1)) == visited.end()) {
                visited.push_back(rope.at(rope.size() - 1));
            }
        }
    }

    std::cout << visited.size();

    return 0;
}