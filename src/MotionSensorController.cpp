//
// Created by adirm on 02.04.2020.
//

#include "../include/MotionSensorController.h"

MotionSensorController::MotionSensorController(uint8_t startPinNumber, uint8_t endPinNumber) {
    startPin = new GPIOHelper(startPinNumber, INPUT);
    endPin = new GPIOHelper(endPinNumber, INPUT);

    sensorA = new MotionSensor();
    sensorB = new MotionSensor();

    dependecyCounter = 0;
    fromStartToEndAnimation = true;
    triggered = false;
    freed = false;
}

void MotionSensorController::update() {
    bool sensorAValue = startPin->getValue();
    bool sensorBValue = endPin->getValue();

    SensorState lastState = state;

    sensorA->update(sensorAValue);
    sensorB->update(sensorBValue);

    if(sensorA->checkIfTriggered()) {
        if(!triggered) {
            fromStartToEndAnimation = true;
            triggered = true;
            if(state == triggeredBState) state = triggeredState;
            else state = triggeredAState;
        }

        dependecyCounter++;
    }

    if(sensorB->checkIfTriggered()) {
        if(!triggered) {
            fromStartToEndAnimation = false;
            triggered = true;
            if(state == triggeredAState) state = triggeredState;
            else state = triggeredBState;
        }

        dependecyCounter++;
    }

    if(sensorA->checkIfFreed()) {
        dependecyCounter--;
        if(dependecyCounter == 0) {
            freed = true;
            state = freedAState;
        }
    }

    if(sensorB->checkIfFreed()) {
        dependecyCounter--;
        if(dependecyCounter == 0) {
            freed = true;
            state = freedBState;
        }
    }

    if(lastState != state) stateChanged = true;
}

bool MotionSensorController::checkIfFreed() {
    if(freed) {
        freed = false;
        return true;
    } else return false;
}

bool MotionSensorController::checkIfTriggered() {
    if(triggered) {
        triggered = false;
        return true;
    } else return false;
}

bool MotionSensorController::checkIfStateChanged() {
    if(stateChanged) {
        stateChanged = false;
        return true;
    } else return false;
}

void MotionSensorController::updateStates() {
    checkIfTriggered();
    checkIfFreed();
}

bool MotionSensorController::checkFromStartToEndDirection() {
    return fromStartToEndAnimation;
}

SensorState MotionSensorController::getState() {
    return state;
}

void MotionSensorController::setState(SensorState newState) {
    this->state = newState;
}