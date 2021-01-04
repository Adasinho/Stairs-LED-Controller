#include <Arduino.h>
#include "Collections.h"

String getStateStringName(ControllerState state) {
    switch (state)
    {
    case TRIGGERED_A_STATE:
        return "TRIGGERED_A_STATE";
    case TRIGGERED_B_STATE:
        return "TRIGGERED_B_STATE";
    case TRIGGERED_FROM_A_TO_B_STATE:
        return "TRIGGERED_FROM_A_TO_B_STATE";
    case TRIGGERED_FROM_B_TO_A_STATE:
        return "TRIGGERED_FROM_B_TO_A_STATE";
    case TRIGGERED_STATE:
        return "TRIGGERED_STATE";
    case ACTIVE_STATE:
        return "ACTIVE_STATE";
    case FREED_A_STATE:
        return "FREED_A_STATE";
    case FREED_B_STATE:
        return "FREED_B_STATE";
    case FREED_FROM_A_TO_B_STATE:
        return "FREED_FROM_A_TO_B_STATE";
    case FREED_FROM_B_TO_A_STATE:
        return "FREED_FROM_B_TO_A_STATE";
    case FREED_STATE:
        return "FREED_STATE";
    case IDLE_STATE:
        return "IDLE_STATE";
    default:
        return " ";
    }
}