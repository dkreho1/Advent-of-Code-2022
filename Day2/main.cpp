#include <iostream>
#include <fstream>
#define PART2


uint64_t calculateOutcome(char opponent, char mine) {
    uint64_t result{};

    opponent -= 'A';
    mine -= 'X';

    char outcome =  opponent - mine;

    if (outcome == -1 || outcome == 2) {
        result += 6;
    } else if (outcome == 0) {
        result += 3;
    }

    result += mine + 1;

    return result;
}


int main() {
    std::ifstream in(R"(C:\Users\User\CLionProjects\AdventOfCode\Day2\inputDay2.txt)");

    uint64_t result{};

    while (true) {
        char opponent, mine;

        in >> opponent >> mine;

        if (in.eof()) {
            break;
        }

#ifdef PART2
        switch(mine) {
            case 'X':
                for (char mine_ : {'X', 'Y', 'Z'}) {
                    if (calculateOutcome(opponent, mine_) == mine_ - 'X' + 1) {
                        result += mine_ - 'X' + 1;
                        break;
                    }
                }
                break;
            case 'Y':
                result += calculateOutcome(opponent, opponent - 'A' + 'X' );
                break;
            case 'Z':
                for (char mine_ : {'X', 'Y', 'Z'}) {
                    if (calculateOutcome(opponent, mine_) == mine_ - 'X' + 7) {
                        result += mine_ - 'X' + 7;
                        break;
                    }
                }
                break;
        }
#else
        result += calculateOutcome(opponent, mine);
#endif
    }

    std::cout << result << std::endl;
}
