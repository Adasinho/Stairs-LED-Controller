#include "Adafruit_NeoPixel.h"
#include "Animation.h"
#include "Control.h"

template <typename ControlerType>
class AnimationController {
    public:
    AnimationController(int numPixels, int pinNumberLEDStrip, int sensorAPin, int sensorBPin, int delayValue);
    void update();
    private:
    void triggeredAnimation();
    void freedAnimation();
    bool checkTime();

    Adafruit_NeoPixel *pixels;
    Animation *animation;
    ControlerType *controller;
    uint8_t delayValue;
    unsigned long lastTime;
};