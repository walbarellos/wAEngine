#include "ecs/debug/DebugSystem.hpp"
#include "ecs/components/Position.hpp"
#include "ecs/components/Velocity.hpp"
#include "ecs/components/Wind.hpp"
#include "ecs/components/Kite.hpp"
#include <iostream>

void DebugSystem::tick(Registry& reg, bool force) {
    // só roda se estiver ativado, ou se pediram dumpOnce, ou se for forçado
    if (!enabled && !force && !dumpOnce) return;

    frameCounter++;
    if (!force && !dumpOnce && frameCounter % 60 != 0) return;

    std::cout << "=== Debug Frame " << frameCounter << " ===\n";

    for (auto [e, pos] : reg.view<Position>()) {
        std::cout << "Entity " << e << " -> Pos(" << pos->x << ", " << pos->y << ")\n";

        if (reg.hasComponent<Velocity>(e)) {
            auto& vel = reg.getComponent<Velocity>(e);
            std::cout << "Entity " << e << " -> Vel(" << vel.vx << ", " << vel.vy << ")\n";
        }
        if (reg.hasComponent<Kite>(e)) {
            auto& kite = reg.getComponent<Kite>(e);
            std::cout << "Entity " << e << " -> Kite(pulling=" << kite.pulling
                      << ", tension=" << kite.tension
                      << ", durability=" << kite.durability << ")\n";
        }
    }

    for (auto [e, wind] : reg.view<Wind>()) {
        std::cout << "Entity " << e << " -> Wind(force=" << wind->force << ")\n";
    }

    dumpOnce = false; // reseta flag de dump único
}
