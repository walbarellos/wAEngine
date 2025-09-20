#pragma once
#include "ecs/Registry.hpp"
#include "ecs/components/LineComponent.hpp"

class LineSystem {
public:
    void update(Registry& reg, float dt);
};
