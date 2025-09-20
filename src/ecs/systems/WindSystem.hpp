#pragma once
#include "ecs/Registry.hpp"
#include "ecs/components/Wind.hpp"
#include "game/WindNoise.hpp"

class WindSystem {
public:
    WindSystem();

    void update(Registry& reg, double dt);

private:
    double time;
    WindNoise noise;
};
