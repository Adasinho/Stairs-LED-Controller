#include "Collections.h"

#ifndef CONTROL_H
#define CONTROL_H

class Control {
    public:
    Control();
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

    virtual void update(bool stateA, bool stateB) = 0;

    protected:
    bool fromStartToEndAnimation;
    bool freed;
    bool triggered;
    bool stateChanged;
    ControllerState state;
    int dependecyCounter;
};

#endif //CONTROL_H