#include "ecs/systems/KiteSystem.hpp"
#include "ecs/Registry.hpp"
#include "ecs/components/KiteComponent.hpp"
#include "ecs/components/Velocity.hpp"
#include "ecs/components/Wind.hpp"
#include "ecs/components/Renderable.hpp"
#include "engine/Input.hpp"
#include <SDL2/SDL.h>
#include <algorithm>

void KiteSystem::update(Registry& reg, Input& input, double dt) {
    auto winds = reg.view<Wind>();
    if (winds.empty()) return;
    Wind* wind = winds.begin()->second; // ponteiro (ecs::Registry)

    auto view = reg.view<KiteComponent>();
    for (auto& [eid, kite] : view) {
        if (!reg.hasComponent<Velocity>(eid)) continue;
        auto* vel = reg.get<Velocity>(eid);
        if (!vel) continue;

        // tensão da linha (SPACE)
        if (input.isDown(SDLK_SPACE)) {
            kite->pulling = true;
            kite->tension += static_cast<float>(dt * 0.1f);
        } else {
            kite->pulling = false;
            kite->tension -= static_cast<float>(dt * 0.05f);
        }

        // física do vento
        float accelX = wind->force * (0.5f + kite->tension);
        float accelY = -0.2f * kite->tension;
        vel->vx += accelX * dt;
        vel->vy += accelY * dt;

        kite->shape.move({
            static_cast<float>(vel->vx * dt),
            static_cast<float>(vel->vy * dt)
        });

        kite->durability -= static_cast<float>(dt * 0.02f);
        kite->tension    = std::clamp(kite->tension, 0.0f, 1.0f);
        kite->durability = std::clamp(kite->durability, 0.0f, 1.0f);

        // garante Renderable
        if (!reg.hasComponent<Renderable>(eid)) {
            reg.add<Renderable>(eid, Renderable(&kite->shape));
        }
    }
}
