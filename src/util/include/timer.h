#ifndef TIMER_HEADER
#define TIMER_HEADER

#include <chrono>

// Timer in milliseconds
struct Timer {
    Timer();

    void start();
    int64_t elapsed();
    void stop();

private:
    bool isActive;

    std::chrono::time_point<std::chrono::system_clock> startTime;
};

#endif // TIMER_HEADER
