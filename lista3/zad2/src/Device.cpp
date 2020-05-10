#include <random>

#include "Device.h"

Device::Device(int number, int position, int interval) {
    this->number = number;
    this->position = position;
    this->interval = interval;
    this->collision = false;
    this->variableToCollision = 1;
    this->broadcast = false;
    this->broadcastTime = 0;
    this->waiting = false;
    this->waitingTime = 0;
    this->collisionWhileWaiting = false;
    this->waitingAfterBroadcast = interval / 2;
    this->noCheckCollisionTime = 0;
}

int Device::getPosition() const {
    return this->position;
}

std::vector<Frame> Device::getFrames() {
    return std::vector<Frame>{Frame(this->number, left, this->collision), Frame(this->number, right, this->collision)};
}

bool Device::ifCollision() const {
    return this->collision;
}

bool Device::ifBroadcast() const {
    return this->broadcast;
}

bool Device::ifWaiting() const {
    return this->waiting;
}

void Device::setCollision(bool collision) {
    this->collision = collision;

    if (this->collision && !this->broadcast) {
        this->waitingTime += interval * this->variableToCollision;
    }
}

void Device::setWaiting(bool waiting) {
    this->waiting = waiting;
    this->waitingTime = interval;
}

void Device::startBroadcast() {
    this->broadcast = true;
    this->broadcastTime = interval;
}

void Device::update() {
    if (this->broadcast) {
        if (--this->broadcastTime <= 0) {
            this->broadcast = false;
            if (this->collision) {
                // collision, choose my time to broadcast
                std::random_device rd;
                std::mt19937 generator(rd());
                std::uniform_int_distribution<int> randInterval(0, pow(2, this->variableToCollision) - 1);
                this->waiting = true;
                int randValue = randInterval(generator);
                this->waitingTime = this->interval * randValue;
                this->waitingAfterBroadcast = int((pow(2, this->variableToCollision) - randValue))* this->interval;
                this->variableToCollision++;
            } else {
                // end of broadcast, wait some time and try to broadcast again
                this->waiting = true;
                this->waitingTime = std::max(this->waitingAfterBroadcast, this->interval / 2);
                this->waitingAfterBroadcast = this->interval / 2;
                this->variableToCollision = 1;
            }
        }
    } else if (this->waiting) {
        if (this->noCheckCollisionTime > 0)
            this->noCheckCollisionTime--;

        if (--this->waitingTime <= 0) {
            // end of waiting
            if (this->collisionWhileWaiting) {
                // collision while waiting, wait again
                this->waitingTime = int(pow(2, this->variableToCollision++) - 1) * this->interval;
                this->collisionWhileWaiting = false;
                this->noCheckCollisionTime = this->interval;
            } else {
                // no collision while waiting
                this->waiting = false;
                this->variableToCollision = 1;
                if (this->collision) {
                    // my time to broadcast after previous collision
                    this->broadcast = true;
                    this->broadcastTime = interval;
                    this->collision = false;
                }
            }
        }
    }
}

void Device::setCollisionWhileWaiting(bool value) {
    this->collisionWhileWaiting = value;
}

bool Device::ifCollisionWhileWaiting() const {
    return this->collisionWhileWaiting;
}

int Device::getBroadcastTime() const {
    return this->broadcastTime;
}

void Device::stillWaiting() {
    this->broadcastTime++;
}

int Device::getNoCheckCollisionTime() const {
    return this->noCheckCollisionTime;
}
