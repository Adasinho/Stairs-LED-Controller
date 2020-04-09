//
// Created by adirm on 02.04.2020.
//

#include "../include/MotionSensor.h"

MotionSensor::MotionSensor() {
    this->motionStatus = false;
    this->state = idleState;
}

void MotionSensor::update(bool state) {
    bool actualMotionStatus = state;

    if(motionStatus != actualMotionStatus) {
        motionStatus = actualMotionStatus;

        if(motionStatus) {
            this->state = triggeredState;
        } else this->state = freedState;
    }
}

bool MotionSensor::checkIfTriggered() {
    if(this->state == triggeredState) {
        this->state = activeState;
        return true;
    } else return false;
}

bool MotionSensor::checkIfFreed() {
    if(this->state == freedState) {
        this->state = activeState;
        return true;
    } else return false;
}