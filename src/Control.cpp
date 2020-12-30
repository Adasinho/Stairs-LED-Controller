#include "Control.h"

Control::Control(uint8_t startPinNumber, uint8_t endPinNumber) {
    startPin = new GPIOHelper(startPinNumber, INPUT);
    endPin = new GPIOHelper(endPinNumber, INPUT);

    dependecyCounter = 0;
    freed = false;
    fromStartToEndAnimation = true;
    triggered = false;
}

ControllerState Control::getState() {
    return state;
}

void Control::setState(ControllerState newState) {
    this->state = newState;
}

void Control::updateStates() {
    checkIfTriggered();
    checkIfFreed();
}

bool Control::checkIfFreed() {
    if(freed) {
        freed = false;
        return true;
    } else return false;
}

bool Control::checkIfTriggered() {
    if(triggered) {
        triggered = false;
        return true;
    } else return false;
}

bool Control::checkFromStartToEndDirection() {
    return fromStartToEndAnimation;
}

bool Control::checkIfStateChanged() {
    if(stateChanged) {
        stateChanged = false;
        return true;
    } else return false;
}

void Control::checkIfControllerTriggered(bool controllerA, bool controllerB) {
    if(controllerA) {
        if(!triggered) {
            fromStartToEndAnimation = true;
            triggered = true;
            if(state == TRIGGERED_B_STATE) state = TRIGGERED_STATE;
            else state = TRIGGERED_A_STATE;
        }

        dependecyCounter++;
    }

    if(controllerB) {
        if(!triggered) {
            fromStartToEndAnimation = false;
            triggered = true;
            if(state == TRIGGERED_A_STATE) state = TRIGGERED_STATE;
            else state = TRIGGERED_B_STATE;
        }

        dependecyCounter++;
    }
}

void Control::checkIfControllerFreed(bool controllerA, bool controllerB) {
    if(controllerA) {
        dependecyCounter--;
        if(dependecyCounter == 0) {
            freed = true;
            state = FREED_A_STATE;
        }
    }

    if(controllerB) {
        dependecyCounter--;
        if(dependecyCounter == 0) {
            freed = true;
            state = FREED_B_STATE;
        }
    }
}