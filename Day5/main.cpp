#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#define PART2

int main() {
    std::ifstream in(R"(C:\Users\User\CLionProjects\AdventOfCode\Day5\inputDay5.txt)");

    std::vector<std::stack<char>> stacks;

    std::vector<std::string> stacksInput;
    std::string stringIn;
    for (int i{}; i < 10; i++) {
        std::getline(in, stringIn);
        if (i < 8) {
            stacksInput.push_back(stringIn);
        }
    }

    for (int i{}; i < 9; i++) {
        std::stack<char> stack;
        for (int j{int(stacksInput.size() - 1)}; j >= 0; j--) {
            if (stacksInput.at(j).at(1 + 4 * i) != ' ') {
                stack.push(stacksInput.at(j).at(1 + 4 * i));
            }
        }
        stacks.push_back(stack);
    }

    while (true) {
        in >> stringIn;

        if (in.eof()) {
            break;
        }

        uint64_t amount{};
        in >> amount >> stringIn;

        uint64_t from{};
        in >> from >> stringIn;

        uint64_t to{};
        in >> to;

#ifdef PART2
        std::stack<char> helper;
        for (int i{} ; i < amount; i++) {
            char tmp{ stacks.at(from - 1).top() };
            stacks.at(from - 1).pop();
            helper.push(tmp);
        }

        for (int i{} ; i < amount; i++) {
            char tmp{ helper.top() };
            helper.pop();
            stacks.at(to - 1).push(tmp);
        }
#else
        for (int i{} ; i < amount; i++) {
            char tmp{ stacks.at(from - 1).top() };
            stacks.at(from - 1).pop();
            stacks.at(to - 1).push(tmp);
        }
#endif
    }

    for (const auto& stack : stacks) {
        std::cout << stack.top();
    }

    return 0;
}