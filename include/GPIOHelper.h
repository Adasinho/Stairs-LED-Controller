#include <Arduino.h>

#ifndef GPIO_HELPER
#define GPIO_HELPER

class GPIOHelper {
    public:
    GPIOHelper(uint8_t pinNumber, uint8_t mode);
    int getValue();
    void setValue(uint8_t value);

    private:
    int pinNumberGPIO;
};

#endif //GPIO_HELPER