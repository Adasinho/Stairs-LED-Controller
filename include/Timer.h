 #include <stdint.h>

#ifndef TIMER
#define TIMER

class Timer {
    public:
    Timer(int duration);
    ~Timer() {};

    void setTimer();
    void update();
    
    bool isBusy();

    private:
    int64_t getActualTime();

    int64_t startTime;
    int duration;

    bool busy;
};

#endif //TIMER