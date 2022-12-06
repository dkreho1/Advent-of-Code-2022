#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#define PART2

#ifdef PART2
const int markerSize{ 14 };
#else
const int markerSize{ 4 };
#endif

int main() {
    std::ifstream in(R"(C:\Users\User\CLionProjects\AdventOfCode\Day6\inputDay6.txt)");

    std::vector<char> letters(markerSize);

    for (char& c : letters) {
        in >> c;
    }

    uint64_t position{ markerSize };

    while (!in.eof()) {
        std::set<char> set;
        for (char c : letters) {
            set.insert(c);
        }

        if (set.size() == markerSize) {
            break;
        }

        for (int i {}; i + 1 < letters.size(); i++) {
            letters.at(i) = letters.at(i + 1);
        }

        position++;
        in >> letters.at(letters.size() - 1) ;
    }

    std::cout << position;

    return 0;
}