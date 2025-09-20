#pragma once
#include "Registry.hpp"

class System {
public:
    virtual void update(Registry& reg, double dt) = 0;
    virtual ~System() = default;
};
