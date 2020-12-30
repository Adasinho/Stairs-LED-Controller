//
// Created by adirm on 02.04.2020.
//

#include "StateController.h"

#include "Control.h"

#pragma once
#ifndef STAIRSLEDS_MOTIONSENSORCONTROLLER_H
#define STAIRSLEDS_MOTIONSENSORCONTROLLER_H

class MotionSensorController : public Control {

public:
    MotionSensorController(uint8_t startPinNumber, uint8_t endPinNumber);
    ~MotionSensorController();
    void update();
    
private:
    StateController *sensorA, *sensorB;
};


#endif //STAIRSLEDS_MOTIONSENSORCONTROLLER_H
