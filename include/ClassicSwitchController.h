#include "Control.h"
#include "StateController.h"

#pragma once
#ifndef STAIRSLEDS_CLASSICSWITCHCONTROLLER_H
#define STAIRSLEDS_CLASSICSWITCHCONTROLLER_H

class ClassicSwitchController : public Control {
    public:
    ClassicSwitchController(uint8_t startPinNumber, uint8_t endPinNumber);
    ~ClassicSwitchController();

    void update();

    private:
    StateController *switchA, *switchB;
    bool stateSwitchA, stateSwitchB;
    bool active;
};

#endif //STAIRSLEDS_CLASSICSWITCHCONTROLLER_H