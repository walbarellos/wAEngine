#include "ecs/MovementSystem.hpp"
#include "ecs/components/Position.hpp"
#include "ecs/components/Velocity.hpp"
#include "ecs/components/Gravity.hpp"
#include <iostream>
#include <algorithm>

void MovementSystem::update(Registry& reg, float dt) {
    auto positions = reg.view<Position>();
    for (auto& [e, pos] : positions) {
        if (reg.hasComponent<Velocity>(e)) {
            auto& vel = reg.getComponent<Velocity>(e);

            // aplica gravidade se existir
            if (reg.hasComponent<Gravity>(e)) {
                auto& g = reg.getComponent<Gravity>(e);
                vel.vy -= g.value * dt;
            }

            // aplica movimento
            pos->x += vel.vx * dt;
            pos->y += vel.vy * dt;

            // limites da "arena"
            pos->y = std::clamp(pos->y, -1.0f, 1.0f); // chão e teto
            pos->x = std::clamp(pos->x, -2.0f, 2.0f); // lateral

            std::cout << "Entity " << e
                      << " -> (" << pos->x << ", " << pos->y << ")\n";
        }
    }
}
