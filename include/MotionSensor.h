//
// Created by adirm on 02.04.2020.
//

#ifndef STAIRS_LEDS_MOTIONSENSOR_H
#define STAIRS_LEDS_MOTIONSENSOR_H

#include "Collections.h"

class MotionSensor {

public:
    MotionSensor();
    void update(bool state);
    bool checkIfTriggered();
    bool checkIfFreed();

private:
    bool motionStatus;
    SensorState state;
};


#endif //STAIRS_LEDS_MOTIONSENSORCONTROLLER_H
