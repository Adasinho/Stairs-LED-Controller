#include "GPIOHelper.h"

GPIOHelper::GPIOHelper(uint8_t pinNumber, uint8_t mode) {
    this->pinNumberGPIO = pinNumber;
    pinMode(this->pinNumberGPIO, mode);
}

int GPIOHelper::getValue() {
    return digitalRead(this->pinNumberGPIO);
}

void GPIOHelper::setValue(uint8_t value) {
    digitalWrite(this->pinNumberGPIO, value);
}