#include "Collections.h"
#include "GPIOHelper.h"

#ifndef CONTROL_H
#define CONTROL_H

class Control {
    public:
    Control(uint8_t startPinNumber, uint8_t endPinNumber);
    Control() {};
    ~Control() {};

    bool checkFromStartToEndDirection();
    bool checkIfTriggered();
    bool checkIfFreed();
    bool checkIfStateChanged();
    
    void checkIfControllerTriggered(bool controllerA, bool controllerB);
    void checkIfControllerFreed(bool controllerA, bool controllerB);
    void updateStates();
    void setState(ControllerState newState);

    ControllerState getState();

    virtual void update() = 0;

    protected:
    bool fromStartToEndAnimation;
    bool freed;
    bool triggered;
    bool stateChanged;
    ControllerState state;
    GPIOHelper *startPin, *endPin;
    int dependecyCounter;
};

#endif //CONTROL_H