#pragma once
#ifndef STAIRSLEDS_CLASSICSWITCHCONTROLLER_H
#define STAIRSLEDS_CLASSICSWITCHCONTROLLER_H

#include "Control.h"
#include "StateController.h"

class ClassicSwitchController : public Control {
    public:
    ClassicSwitchController();
    ~ClassicSwitchController();

    void update(bool stateA, bool stateB) override;

    private:
    StateController *switchA, *switchB;
    bool stateSwitchA, stateSwitchB;
    bool active;
};

#endif //STAIRSLEDS_CLASSICSWITCHCONTROLLER_H