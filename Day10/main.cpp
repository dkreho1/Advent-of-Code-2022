#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#define PART2

void updateCRT(std::vector<std::string>& CRT, uint64_t cycleCount, int64_t rx) {
    uint64_t CRTposition{};
    CRTposition = (cycleCount - 1) % 40;
    if (CRTposition == rx  || CRTposition == rx - 1 || CRTposition == rx + 1) {
        CRT.at((cycleCount - 1)  / 40).at(CRTposition ) = '#';
    }
}

int main() {
    std::ifstream in(R"(C:\Users\User\CLionProjects\AdventOfCode\Day10\inputDay10.txt)");

    int64_t rx{ 1 };
    uint64_t cycleCount{};

#ifdef PART2
    std::vector<std::string> CRT(6, std::string(40, '.'));
#else
    uint64_t signalStrengthsSum{};
#endif

    while (true) {
        std::string instruction;
        in >> instruction;

        if (in.eof()) {
            break;
        }


        if (instruction == "noop") {
            cycleCount++;
#ifdef PART2
            updateCRT(CRT, cycleCount, rx);
#else
            if (cycleCount % 40 == 20) {
                signalStrengthsSum += cycleCount * rx;
                if (cycleCount == 220) {
                    break;
                }
            }
#endif
        } else {
            int64_t value{};
            in >> value;

            for (int i{}; i < 2; i++) {
                cycleCount++;
#ifdef PART2
                updateCRT(CRT, cycleCount, rx);
#else
                if (cycleCount % 40 == 20) {
                    signalStrengthsSum += cycleCount * rx;
                    if (cycleCount == 220) {
                        break;
                    }
                }
#endif
            }
            rx += value;
        }
    }


#ifdef PART2
    for (const auto& row : CRT) {
        for (int i{}; i < row.length(); i++) {
            std::cout << row.at(i);
            if ((i + 1) % 5 == 0) {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
#else
    std::cout << signalStrengthsSum;
#endif

    return 0;
}