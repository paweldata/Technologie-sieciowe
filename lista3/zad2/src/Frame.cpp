#include "Frame.h"

Frame::Frame(int owner, Direction direction, bool collision) {
    this->owner = owner;
    this->direction = direction;
    this->collision = collision;
}

int Frame::getOwner() const {
    return this->owner;
}

Direction Frame::getDirection() const {
    return this->direction;
}

bool Frame::ifCollision() const {
    return this->collision;
}
