#pragma once
#include "ecs/Registry.hpp"
#include "ecs/components/Kite.hpp"

class DestroySystem {
public:
    // Se a durabilidade <= 0, destrói a entidade com componente Kite
    void update(Registry& reg);
};
