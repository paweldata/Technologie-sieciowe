#include <algorithm>

#include "Field.h"

Field::Field() {
    this->frames = std::vector<Frame>();
}

std::vector<Frame> Field::getFrames(Direction direction) {
    std::vector<Frame> answer{};

    for (Frame frame : this->frames)
        if (frame.getDirection() == direction)
            answer.push_back(frame);

    return answer;
}

std::vector<Frame> Field::getFrames() {
    return this->frames;
}

void Field::addFrame(Frame frame) {
    this->frames.push_back(frame);
}

void Field::removeFrame(Frame frame) {
    this->frames.erase(std::remove(this->frames.begin(), this->frames.end(), frame), this->frames.end());
}

bool Field::ifCollision() {
    for (Frame frame : this->frames)
        if (frame.ifCollision())
            return true;

    return false;
}

bool Field::ifCollision2() {
    if (this->frames.empty())
        return false;

    int owner = this->frames[0].getOwner();

    for (Frame frame : frames)
        if (frame.getOwner() != owner)
            return true;

    return false;
}

bool Field::ifEmpty() {
    return this->frames.empty();
}
