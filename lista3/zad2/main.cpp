#include <cstdio>
#include <vector>
#include <algorithm>

#include "src/Ethernet.h"

int main() {
    int wireLength = 0;
    int devicesAmount = 0;
    float probability;
    int roundsAmount;

    do {
        printf("Wire length (minimum 10) : ");
        scanf("%d", &wireLength);
    } while (wireLength < 10);

    do {
        printf("Number of devices (from 2 to 9) : ");
        scanf("%d", &devicesAmount);
    } while (devicesAmount < 2 || devicesAmount > 9);

    std::vector<int> coordinate(devicesAmount, 0);
    coordinate[0] = 0;
    coordinate[1] = wireLength - 1;

    for (int i = 2; i < devicesAmount; i++) {
        int position;

        do {
            printf("Position of %d device (from 1 to %d) : ", i + 1, wireLength - 2);
            scanf("%d", &position);
        } while (position < 0 || position >= wireLength || std::count(coordinate.begin(), coordinate.end(), position) > 0);

        coordinate[i] = position;
    }

    do {
        printf("Broadcast probability (from 0 to 1) : ");
        scanf("%f", &probability);
    } while (probability <= 0 || probability >= 1);

    do {
        printf("Number of rounds : ");
        scanf("%d", &roundsAmount);
    } while (roundsAmount < 0);

    Ethernet network(devicesAmount, coordinate, wireLength, probability, roundsAmount);
    network.run();

    return 0;
}
