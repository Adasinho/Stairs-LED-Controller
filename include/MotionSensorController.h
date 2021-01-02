//
// Created by adirm on 02.04.2020.
//

#pragma once
#ifndef STAIRSLEDS_MOTIONSENSORCONTROLLER_H
#define STAIRSLEDS_MOTIONSENSORCONTROLLER_H

#include "StateController.h"
#include "Control.h"

class MotionSensorController : public Control {

public:
    MotionSensorController();
    ~MotionSensorController();
    void update(bool stateA, bool stateB);
    
private:
    StateController *sensorA, *sensorB;
};


#endif //STAIRSLEDS_MOTIONSENSORCONTROLLER_H
