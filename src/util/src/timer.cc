// timer.cc

#include <timer.h>

Timer::Timer():
    isActive(false)
{}

void Timer::start() {
    
    isActive = true;
    startTime = std::chrono::system_clock::now();
}

int64_t Timer::elapsed() {
    if (!isActive) {
        return 0;
    }

    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();

    return duration;
}

void Timer::stop() {
    isActive = false;
}
