#include "ClassicSwitchController.h"

ClassicSwitchController::ClassicSwitchController() : Control() {
    switchA = new StateController();
    switchB = new StateController();

    active = false;
    stateSwitchB = false;
    stateSwitchA = false;
}

ClassicSwitchController::~ClassicSwitchController() {
    delete switchA;
    delete switchB;
}

void ClassicSwitchController::update(bool stateA, bool stateB) {
    ControllerState lastState = state;

    switchA->update(stateA);
    switchB->update(stateB);

    bool switchATriggered = switchA->checkIfTriggered();
    bool switchBTriggered = switchB->checkIfTriggered();
    bool switchAFreed = switchA->checkIfFreed();
    bool switchBFreed = switchB->checkIfFreed();

    bool switchAChanged = switchATriggered || switchAFreed;
    bool switchBChanged = switchBTriggered || switchBFreed;

    if(switchAChanged || switchBChanged) {
        switch(lastState) {
            case IDLE_STATE:
                state = !stateA && !stateB ? IDLE_STATE :
                        switchATriggered ? TRIGGERED_A_STATE :
                        switchBTriggered ? TRIGGERED_B_STATE :
                        switchAFreed ? TRIGGERED_A_STATE :
                        switchBFreed ? TRIGGERED_B_STATE :
                        IDLE_STATE;
            break;
            case TRIGGERED_A_STATE:
                state = switchATriggered || switchAFreed ? FREED_A_STATE :
                        switchBTriggered || switchBFreed ? FREED_FROM_A_TO_B_STATE :
                        IDLE_STATE;
            break;
            case TRIGGERED_B_STATE:
                state = switchAFreed || switchATriggered ? FREED_FROM_B_TO_A_STATE :
                        switchBFreed || switchBTriggered ? FREED_B_STATE :
                        IDLE_STATE;
            break;
            case FREED_A_STATE:
                state = switchATriggered ? TRIGGERED_A_STATE :
                        switchBTriggered ? TRIGGERED_FROM_B_TO_A_STATE :
                        ACTIVE_STATE;
            break;
            case FREED_B_STATE:
                state = switchBTriggered ? TRIGGERED_B_STATE :
                        switchATriggered ? TRIGGERED_FROM_A_TO_B_STATE :
                        ACTIVE_STATE;
            break;
            case TRIGGERED_FROM_A_TO_B_STATE:
            break;
            case TRIGGERED_FROM_B_TO_A_STATE:
            break;
            case FREED_FROM_A_TO_B_STATE:
            break;
            case FREED_FROM_B_TO_A_STATE:
            break;
            case ACTIVE_STATE:
                state = switchAFreed ? FREED_A_STATE :
                        switchBFreed ? FREED_B_STATE :
                        switchATriggered ? FREED_A_STATE :
                        switchBTriggered ? FREED_B_STATE :
                        ACTIVE_STATE;
            break;
        }
    }

    if(lastState != state) stateChanged = true;
}