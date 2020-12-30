//
// Created by adirm on 02.04.2020.
//
#pragma once
#ifndef STAIRS_LEDS_MOTIONSENSOR_H
#define STAIRS_LEDS_MOTIONSENSOR_H

#include "Collections.h"

class StateController {

public:
    StateController();
    void update(bool state);
    bool checkIfTriggered();
    bool checkIfFreed();

protected:
    bool triggered;
    ControllerState state;
};


#endif //STAIRS_LEDS_MOTIONSENSOR_H
