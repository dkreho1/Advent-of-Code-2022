#include <iostream>
#include <fstream>
#define PART2

int main() {
    std::ifstream in(R"(C:\Users\User\CLionProjects\AdventOfCode\Day4\inputDay4.txt)");

#ifdef PART2
    uint32_t overlap{};
#else
    uint32_t fullyContained{};
#endif

    while (true) {
        uint64_t section1Begin{};
        in >> section1Begin;

        if (in.eof()) {
            break;
        }

        char tmp{};
        in >> tmp;

        uint64_t section1End{};
        in >> section1End >> tmp;

        uint64_t section2Begin{};
        in >> section2Begin >> tmp;

        uint64_t section2End{};
        in >> section2End;

#ifdef PART2
        if ((section1End >= section2Begin && section1End <= section2End) ||
                (section2End >= section1Begin && section2End <= section1End)) {
            overlap++;
        }
#else
        if ((section1Begin <= section2Begin && section1End >= section2End) ||
            (section2Begin <= section1Begin && section2End >= section1End)) {
            fullyContained++;
        }
#endif
    }

#ifdef PART2
    std::cout << overlap << std::endl;
#else
    std::cout << fullyContained << std::endl;
#endif
}