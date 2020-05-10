#ifndef FIELD_H
#define FIELD_H


#include <vector>

#include "Frame.h"

class Field {
public:
    Field();
    std::vector<Frame> getFrames(Direction direction);
    std::vector<Frame> getFrames();
    void addFrame(Frame frame);
    void removeFrame(Frame frame);
    bool ifCollision();
    bool ifCollision2();
    bool ifEmpty();

private:
    std::vector<Frame> frames;
};


#endif //FIELD_H
