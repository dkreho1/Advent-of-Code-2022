#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#define PART2

enum class Operation { add, multiply, square };

struct Monkey {
    uint16_t number;
    std::vector<uint64_t> items;
    std::pair<Operation, uint64_t> operation;
    uint64_t divisibleTestNumber;
    uint16_t monkeyNumberCondTrue;
    uint16_t monkeyNumberCondFalse;
    uint64_t inspectedCount{};
};

int main() {
    std::ifstream in(R"(C:\Users\User\CLionProjects\AdventOfCode\Day11\inputDay11.txt)");
    std::vector<Monkey> monkeys;

    while (!in.eof()) {
        Monkey monkey;

        std::string line{"Nesta"};

        std::getline(in, line);
        monkey.number = line.at(line.length() - 2) - '0';

        in >> line >> line;
        std::vector<uint64_t> items;
        while (true) {
            uint64_t item;
            char tmp;
            in >> item >> tmp;
            items.push_back(item);
            if (tmp == 'O') {
                break;
            }
        }
        monkey.items = items;

        std::getline(in, line);
        std::size_t found = line.find("old * old");
        if (found != std::string::npos) {
            monkey.operation = std::make_pair(Operation::square, 1);
        } else {
            found = line.find("old * ");
            if (found != std::string::npos) {
                monkey.operation = std::make_pair(Operation::multiply,
                                                  std::stoi(line.substr(found + 6)));
            }
        }
        found = line.find("old + ");
        if (found != std::string::npos) {
            monkey.operation = std::make_pair(Operation::add,
                                              std::stoi(line.substr(found + 6)));
        }

        uint64_t num1;
        uint16_t num2;

        in >> line >> line >> line >> num1;
        monkey.divisibleTestNumber = num1;

        in >> line >> line >> line >> line >> line >> num2;
        monkey.monkeyNumberCondTrue = num2;

        in >> line >> line >> line >> line >> line >> num2;
        monkey.monkeyNumberCondFalse = num2;

        std::getline(in, line);
        std::getline(in, line);

        monkeys.push_back(monkey);
    }

#ifdef PART2
    const int numberOfRound{ 10000 };
#else
    const int numberOfRound{ 20 };
#endif

    for (int k{}; k < numberOfRound; k++) {
        for (int i{}; i < monkeys.size(); i++) {
            for (int j{}; j < monkeys.at(i).items.size(); j++) {
                auto tmp = monkeys.at(i).items.at(j);
                switch (monkeys.at(i).operation.first) {
                    case Operation::square:
                        monkeys.at(i).items.at(j) *= monkeys.at(i).items.at(j);
                        break;
                    case Operation::add:
                        monkeys.at(i).items.at(j) += monkeys.at(i).operation.second;
                        break;
                    case Operation::multiply:
                        monkeys.at(i).items.at(j) *= monkeys.at(i).operation.second;
                        break;
                }

                if (tmp > monkeys.at(i).items.at(j)) {
                    return -1; // overflow detected
                }

                monkeys.at(i).inspectedCount++;

#ifndef PART2
                monkeys.at(i).items.at(j) = monkeys.at(i).items.at(j) / 3;
#endif

                if (monkeys.at(i).items.at(j) % monkeys.at(i).divisibleTestNumber == 0) {
                    monkeys.at((monkeys.at(i).monkeyNumberCondTrue))
                            .items.push_back(monkeys.at(i).items.at(j));
                } else {
                    monkeys.at((monkeys.at(i).monkeyNumberCondFalse))
                            .items.push_back(monkeys.at(i).items.at(j));
                }

                monkeys.at(i).items.erase(monkeys.at(i).items.begin() + j);
                j--;
            }
        }
    }

    uint64_t firstMax{}, secondMax{};
    for (const Monkey& m: monkeys) {
        if (m.inspectedCount > firstMax) {
            firstMax = m.inspectedCount;
        }
    }

    for (const Monkey& m: monkeys) {
        if (m.inspectedCount < firstMax && m.inspectedCount > secondMax) {
            secondMax = m.inspectedCount;
        }
    }

    std::cout << firstMax * secondMax;

    return 0;
}
