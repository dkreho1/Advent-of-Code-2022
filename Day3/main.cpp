#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <cctype>
#include <map>
#define PART2

void countLetterOccurrences(const std::string& str, std::map<char, int> &letters) {
    std::set<char> lettersSet;

    for (char c : str) {
        lettersSet.insert(c);
    }

    for (char c : lettersSet) {
        letters[c] += 1;
    }
}


int main() {
    std::ifstream in(R"(C:\Users\User\CLionProjects\AdventOfCode\Day3\inputDay3.txt)");

    uint64_t result{};

    while (!in.eof()) {
#ifdef PART2
        std::map<char, int> letters;

        for (int i{}; i < 3; i++) {
            std::string input;
            in >> input;

            countLetterOccurrences(input, letters);
        }

        for (const auto& pair : letters) {
            if (pair.second == 3) {
                if (std::isupper(pair.first)) {
                    result += pair.first - 'A' + 27;
                } else {
                    result += pair.first - 'a' + 1;
                }
                break;
            }
        }
#else
        std::set<char> letters;

        std::string input;
        in >> input;

        for (uint64_t i{}; i < input.length() / 2; i++) {
            letters.insert(input.at(i));
        }

        for (uint64_t i{input.length() / 2}; i < input.length(); i++) {
            if (letters.find(input.at(i)) != letters.end()) {
                if (std::isupper(input.at(i))) {
                    result += input.at(i) - 'A' + 27;
                } else {
                    result += input.at(i) - 'a' + 1;
                }
                break;
            }
        }
#endif
    }

    std::cout << result << std::endl;

    return 0;
}