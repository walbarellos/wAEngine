#pragma once
#include <random>

class WindGenerator {
public:
    WindGenerator() : dist(-1.0f, 1.0f) {}

    float generate() {
        return dist(rng);
    }

private:
    std::mt19937 rng{std::random_device{}()};
    std::uniform_real_distribution<float> dist;
};
