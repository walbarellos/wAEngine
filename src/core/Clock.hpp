#pragma once
#include <chrono>

class Clock {
    using clock = std::chrono::high_resolution_clock;
    clock::time_point last;
public:
    Clock() { reset(); }
    void reset() { last = clock::now(); }

    double delta() {
        auto now = clock::now();
        std::chrono::duration<double> diff = now - last;
        last = now;
        return diff.count();
    }
};
