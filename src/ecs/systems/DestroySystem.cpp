// src/ecs/systems/DestroySystem.cpp
#include "ecs/systems/DestroySystem.hpp"
#include <iostream>
#include <vector>
#include "ecs/components/Kite.hpp"

void DestroySystem::update(Registry& reg) {
    std::vector<Entity> toRemove;

    // marca para remoção
    for (auto& [e, kite] : reg.view<Kite>()) {
        if (kite->durability <= 0.0f) {
            toRemove.push_back(e);
        }
    }

    // remove e loga
    for (auto e : toRemove) {
        reg.destroy(e);
        std::cout << "Entity " << e << " destroyed (kite broke)\n";
    }
}
