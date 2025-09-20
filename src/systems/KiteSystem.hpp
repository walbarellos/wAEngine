#pragma once
#include "ecs/Registry.hpp"
#include "ecs/components/Position.hpp"
#include "ecs/components/Velocity.hpp"
#include "ecs/components/Kite.hpp"
#include "ecs/components/Wind.hpp"
#include "engine/Input.hpp"

class KiteSystem {
public:
    void update(Registry& reg, Input& input, double dt);
};
