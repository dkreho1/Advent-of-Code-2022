#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <cmath>
#define PART2

struct Point {
    int64_t x{};
    int64_t y{};
};

using Sensor = Point;
using Beacon = Point;

inline int64_t getManhattanDistance(Point p1, Point p2) {
    return std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y);
}

void updateRange(int64_t &edge1, int64_t& edge2, const int64_t &value) {
    if (value < edge1) {
        edge1 = value;
    }
    if (value > edge2) {
        edge2 = value;
    }
}

int main() {
    FILE* in = std::fopen(R"(C:\Users\User\CLionProjects\AdventOfCode\Day15\inputDay15.txt)", "r");

    Sensor sensor;
    Beacon beacon;
    std::vector<std::pair<Sensor, Beacon>> sensorsAndBeacons;

    int64_t edgeUp{INT64_MAX}, edgeDown{INT64_MIN}, edgeLeft{INT64_MAX}, edgeRight{INT64_MIN},
        maxDistance{};

    while (!std::feof(in)) {
        fscanf(in, "Sensor at x=%lld, y=%lld: closest beacon is at x=%lld, y=%lld\n",
               &sensor.x, &sensor.y, &beacon.x, &beacon.y);

        updateRange(edgeUp, edgeDown, sensor.y);
        updateRange(edgeUp, edgeDown, beacon.y);
        updateRange(edgeLeft, edgeRight, sensor.x);
        updateRange(edgeLeft, edgeRight, beacon.x);

        if (maxDistance < getManhattanDistance(sensor, beacon)) {
            maxDistance = getManhattanDistance(sensor, beacon);
        }

        sensorsAndBeacons.push_back({sensor, beacon});
    }

    std::fclose(in);

    edgeLeft -= maxDistance;
    edgeRight += maxDistance;
    edgeUp -= maxDistance;
    edgeDown += maxDistance;

#ifdef PART2
    edgeLeft = (edgeLeft < 0) ? (0) : (edgeLeft);
    edgeUp = (edgeUp < 0) ? (0) : (edgeUp);
    edgeRight = (edgeRight > 4000000) ? (4000000) : (edgeRight);
    edgeDown = (edgeDown > 4000000) ? (4000000) : (edgeDown);

    for (int64_t i{edgeLeft}; i <= edgeRight; i++) {
        for (int64_t j{edgeUp}; j <= edgeDown; j++) {
            bool covered{false};
            for (const auto sensorAndBeacon : sensorsAndBeacons) {
                if (sensorAndBeacon.second.x == i && sensorAndBeacon.second.y == j) {
                    continue;
                }

                if (getManhattanDistance(sensorAndBeacon.first, {i, j}) <=
                    getManhattanDistance(sensorAndBeacon.first, sensorAndBeacon.second)) {
                    covered = true;
                    break;
                }
            }

            if (!covered) {
                std::cout << i * 4000000 + j;
            }
        }
    }

#else
    uint64_t coveredCount{};
    int64_t y{2000000};

    for (int64_t i{edgeLeft}; i <= edgeRight; i++) {
        bool covered{false};
        for (const auto sensorAndBeacon : sensorsAndBeacons) {
            if (sensorAndBeacon.second.x == i && sensorAndBeacon.second.y == y) {
                continue;
            }

            if (getManhattanDistance(sensorAndBeacon.first, {i, y}) <=
                getManhattanDistance(sensorAndBeacon.first, sensorAndBeacon.second)) {
                covered = true;
                break;
            }
        }

        coveredCount += covered;
    }

    std::cout << coveredCount;
#endif


    return 0;
}
