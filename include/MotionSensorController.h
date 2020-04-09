//
// Created by adirm on 02.04.2020.
//

#include "MotionSensor.h"
#include "GPIOHelper.h"

#ifndef STAIRSLEDS_MOTIONSENSORCONTROLLER_H
#define STAIRSLEDS_MOTIONSENSORCONTROLLER_H

class MotionSensorController {

public:
    MotionSensorController(uint8_t startPinNumber, uint8_t endPinNumber);
    void update();
    void updateStates();
    bool checkIfTriggered();
    bool checkIfFreed();
    bool checkFromStartToEndDirection();
    bool checkIfStateChanged();
    SensorState getState();
    void setState(SensorState newState);

private:
    MotionSensor *sensorA, *sensorB;
    GPIOHelper *startPin, *endPin;

    bool triggered;
    bool freed;
    bool fromStartToEndAnimation;
    bool stateChanged;
    int dependecyCounter;
    SensorState state;
};


#endif //STAIRSLEDS_MOTIONSENSORCONTROLLER_H
