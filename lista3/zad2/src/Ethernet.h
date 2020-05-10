#ifndef NETWORK_H
#define NETWORK_H


#include <vector>

#include "Device.h"
#include "Field.h"

class Ethernet {
public:
    Ethernet(int devicesAmount, std::vector<int> coordinate, int wireLength, double probability, int roundsAmount);
    void run();

private:
    std::vector<Device> devices;
    std::vector<Field> wire;
    double probability;
    int roundsAmount;

    void moveFrames();
    void sendNewFrames();
    void printWire();
};


#endif //NETWORK_H
