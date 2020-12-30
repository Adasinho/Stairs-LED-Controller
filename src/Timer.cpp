#include "Timer.h"
#include <chrono>

using namespace std::chrono;

Timer::Timer(int duration) {
    this->busy = false;
    this->startTime = 0;
    this->duration = duration;
}

bool Timer::isBusy() {
    return busy;
}

void Timer::setTimer() {
    this->startTime = getActualTime();
    this->busy = true;
}

void Timer::update() {
    if(busy) {
        if((startTime + duration) < getActualTime()) {
            busy = false;
        }
    }
}

int64_t Timer::getActualTime() {
    milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    return ms.count();
}