#include <iostream>
#include <fstream>
#include <string>
#define PART2

uint64_t findElfWithMostCalories(std::ifstream& in, bool ignoreEnable = false, uint64_t ignoreValue = 0) {
    in.clear();
    in.seekg(0);

    uint64_t max{}, sum{};
    while (!in.eof()) {
        uint64_t tmp{};
        in >> tmp;
        sum += tmp;

        if (in.get(), in.peek() == '\n' || in.peek() == EOF) {
            if (sum > max && !(ignoreValue && sum >= ignoreValue)) {
                max = sum;
            }
            sum = 0;
        }
    }

    return max;
}

int main() {
    std::ifstream in(R"(C:\Users\User\CLionProjects\AdventOfCode\Day1\inputDay1.txt)");

#ifdef PART2
    uint64_t firstMax = findElfWithMostCalories(in);
    uint64_t secondMax = findElfWithMostCalories(in, true, firstMax);
    uint64_t thirdMax = findElfWithMostCalories(in, true, secondMax);

    std::cout << firstMax + secondMax + thirdMax << std::endl;
#else
    std::cout << findMaxElfWithMostCalories(in) << std::endl;
#endif

}
