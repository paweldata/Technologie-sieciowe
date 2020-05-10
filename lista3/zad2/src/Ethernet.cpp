#include <cstdio>
#include <random>

#include "Ethernet.h"

Ethernet::Ethernet(int devicesAmount, std::vector<int> coordinate, int wireLength, double probability, int roundsAmount) {
    this->devices = std::vector<Device>(devicesAmount);

    for (int i = 0; i < devicesAmount; i++)
        this->devices[i] = *(new Device(i + 1, coordinate[i], wireLength * 2));

    this->wire = std::vector<Field>(wireLength, Field());
    this->probability = probability;
    this->roundsAmount = roundsAmount;
}

void Ethernet::run() {
    for (int round = 1; round <= this->roundsAmount; round++) {
        this->moveFrames();
        this->sendNewFrames();
        this->printWire();
    }
}

void Ethernet::moveFrames() {
    int size = this->wire.size();

    for (int i = 0; i < size; i++) {
        for (Frame &frame : this->wire[i].getFrames(left)) {
            this->wire[i].removeFrame(frame);

            if (i > 0) {
                this->wire[i - 1].addFrame(frame);
            }
        }
    }

    for (int i = size - 1; i >= 0; i--) {
        for (Frame &frame : this->wire[i].getFrames(right)) {
            this->wire[i].removeFrame(frame);

            if (i < size - 1) {
                this->wire[i + 1].addFrame(frame);
            }
        }
    }
}

void Ethernet::sendNewFrames() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> randFrom0to1(0.0, 1.0);

    for (Device &device : this->devices) {

        if (device.ifBroadcast()) {
            if (device.getBroadcastTime() < this->wire.size() * 2 || this->wire[device.getPosition()].ifEmpty()) {
                if (!device.ifCollision() && !this->wire[device.getPosition()].ifEmpty())
                    device.setCollision(true);

                std::vector<Frame> frames = device.getFrames();
                this->wire[device.getPosition()].addFrame(frames[0]);
                this->wire[device.getPosition()].addFrame(frames[1]);
            } else {
                device.stillWaiting();
            }
        } else if (device.ifWaiting()) {
            if (device.getNoCheckCollisionTime() == 0 && !device.ifCollision()
            && !device.ifCollisionWhileWaiting() && this->wire[device.getPosition()].ifCollision()) {
                device.setCollisionWhileWaiting(true);
            }
        } else if (!this->wire[device.getPosition()].ifEmpty()) {
            device.setWaiting(true);
        } else if (this->probability >= randFrom0to1(generator)) {
            device.startBroadcast();
        }

        device.update();
    }
}

void Ethernet::printWire() {
    for (Field field : this->wire) {
        if (field.ifCollision()) {
            printf("X");
        } else if (field.ifCollision2()) {
            printf("Y");
        } else if (field.getFrames().empty()) {
            printf("0");
        } else {
            printf("%d", field.getFrames()[0].getOwner());
        }
    }

    printf("\n");
}
