#ifndef DEVICE_H
#define DEVICE_H


#include <vector>

#include "Frame.h"

class Device {
public:
    Device(int number, int position, int interval);
    Device() {}
    int getPosition() const;
    bool ifCollision() const;
    void setCollision(bool collision);
    void setWaiting(bool waiting);
    void setCollisionWhileWaiting(bool value);
    int getBroadcastTime() const;
    void stillWaiting();

    void startBroadcast();
    std::vector<Frame> getFrames();
    bool ifBroadcast() const;
    bool ifWaiting() const;
    bool ifCollisionWhileWaiting() const;
    int getNoCheckCollisionTime() const;

    void update();

private:
    int interval;
    int number;
    int position;
    bool broadcast;
    int broadcastTime;
    bool waiting;
    int waitingTime;
    bool collision;
    int variableToCollision;
    bool collisionWhileWaiting;
    int waitingAfterBroadcast;
    int noCheckCollisionTime;
};


#endif //DEVICE_H
