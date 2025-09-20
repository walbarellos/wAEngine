#pragma once
#include "ecs/Registry.hpp"
#include "engine/Input.hpp"

class KiteSystem {
public:
    void update(Registry& reg, Input& input, double dt);
};
