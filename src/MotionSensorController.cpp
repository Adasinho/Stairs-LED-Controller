//
// Created by adirm on 02.04.2020.
//

#include "../include/MotionSensorController.h"

MotionSensorController::MotionSensorController() : Control() {
    sensorA = new StateController();
    sensorB = new StateController();
}

MotionSensorController::~MotionSensorController() {
    delete sensorA;
    delete sensorB;
}

void MotionSensorController::update(bool stateA, bool stateB) {
    bool sensorAValue = stateA;
    bool sensorBValue = stateB;

    ControllerState lastState = state;

    sensorA->update(sensorAValue);
    sensorB->update(sensorBValue);

    bool sensorATriggered = sensorA->checkIfTriggered();
    bool sensorBTriggered = sensorB->checkIfTriggered();

    checkIfControllerTriggered(sensorATriggered, sensorBTriggered);

    bool sensorAFreed = sensorA->checkIfFreed();
    bool sensorBFreed = sensorB->checkIfFreed();

    checkIfControllerFreed(sensorAFreed, sensorBFreed);

    if(lastState != state) stateChanged = true;
}