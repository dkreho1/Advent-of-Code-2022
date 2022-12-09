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
    std::vector<Position> rope(10);
    visited.push_back(rope.at(9));
#else
    Position head, tail;
    visited.push_back(tail);
#endif


    while (!in.eof()) {
        char direction;
        uint64_t amount;

        in >> direction >> amount;


        for (int i{}; i < amount; i++) {
#ifdef PART2
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

            for (int j{ 1 }; j < 10; j++) {
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

            if (std::find(visited.begin(), visited.end(), rope.at(9)) == visited.end()) {
                visited.push_back(rope.at(9));
            }
#else
            switch (direction) {
                case 'R':
                    head.x++;
                    break;
                case 'L':
                    head.x--;
                    break;
                case 'U':
                    head.y++;
                    break;
                case 'D':
                    head.y--;
                    break;
                default:
                    break;
            }

            if (tail.isNextTo(head)) {
                continue;
            }

            if (std::abs(Position::distance(head, tail) - 2) < eps) {
                tail.x += (head.x - tail.x) / 2;
                tail.y += (head.y - tail.y) / 2;
            } else {
                int64_t move{head.x - tail.x};
                if (std::abs(move) == 1) {
                    move = ((move > 0) ? (move + 1) : (move - 1));
                }
                tail.x += (move) / 2;

                move = head.y - tail.y;
                if (std::abs(move) == 1) {
                    move = ((move > 0) ? (move + 1) : (move - 1));
                }
                tail.y += (move) / 2;
            }


            if (std::find(visited.begin(), visited.end(), tail) == visited.end()) {
                visited.push_back(tail);
            }
#endif
        }
    }

    std::cout << visited.size();

    return 0;
}
