#ifndef FRAME_H
#define FRAME_H


#include "Direction.h"

class Frame {
public:
    Frame(int owner, Direction direction, bool collision);
    int getOwner() const;
    Direction getDirection() const;
    bool ifCollision() const;

    bool operator==(const Frame &frame) const {
        return (frame.owner == this->owner && frame.direction == this->direction);
    }

private:
    int owner;
    Direction direction;
    bool collision;
};


#endif //FRAME_H
