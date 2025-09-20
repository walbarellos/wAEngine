#pragma once
#include "ecs/Registry.hpp"
#include "ecs/components/Position.hpp"
#include "ecs/components/Velocity.hpp"
#include <iostream>

class MovementSystem {
public:
    void update(Registry& registry, float dt);
};
