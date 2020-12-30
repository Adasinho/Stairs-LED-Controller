//
// Created by adirm on 02.04.2020.
//

#include "../include/MotionSensorController.h"

MotionSensorController::MotionSensorController(uint8_t startPinNumber, uint8_t endPinNumber) : Control(startPinNumber, endPinNumber) {
    sensorA = new StateController();
    sensorB = new StateController();
}

MotionSensorController::~MotionSensorController() {
    delete sensorA;
    delete sensorB;
}

void MotionSensorController::update() {
    bool sensorAValue = startPin->getValue();
    bool sensorBValue = endPin->getValue();

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