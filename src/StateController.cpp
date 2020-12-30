//
// Created by adirm on 02.04.2020.
//

#include "../include/StateController.h"

StateController::StateController() {
    this->triggered = false;
    this->state = IDLE_STATE;
}

void StateController::update(bool state) {
    bool actualMotionStatus = state;

    if(triggered != actualMotionStatus) {
        triggered = actualMotionStatus;

        if(triggered) {
            this->state = TRIGGERED_STATE;
        } else this->state = FREED_STATE;
    }
}

bool StateController::checkIfTriggered() {
    if(this->state == TRIGGERED_STATE) {
        this->state = ACTIVE_STATE;
        return true;
    } else return false;
}

bool StateController::checkIfFreed() {
    if(this->state == FREED_STATE) {
        this->state = IDLE_STATE;
        return true;
    } else return false;
}