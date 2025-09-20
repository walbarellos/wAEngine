#include "ecs/systems/KiteSystem.hpp"
#include "ecs/components/Kite.hpp"
#include "ecs/components/Velocity.hpp"
#include "ecs/components/Wind.hpp"
#include <algorithm> // std::clamp

void KiteSystem::update(Registry& reg, Input& input, double dt) {
    auto view = reg.view<Kite>();
    auto winds = reg.view<Wind>();

    if (winds.empty()) return;
    Wind* wind = winds.begin()->second; // vento global

    for (auto& [e, kite] : view) {
        if (!reg.hasComponent<Velocity>(e)) continue;
        auto& vel = reg.getComponent<Velocity>(e);

        // -----------------------
        // Tensão da linha (SPACE)
        // -----------------------
        if (input.isDown(SDLK_SPACE)) {
            kite->pulling = true;
            kite->tension += static_cast<float>(dt * 0.1f);
        } else {
            kite->pulling = false;
            kite->tension -= static_cast<float>(dt * 0.05f);
        }

        // -----------------------
        // Física: vento altera velocidade
        // -----------------------
        float accelX = wind->force * (0.5f + kite->tension); // vento puxa no X
        float accelY = -0.2f * kite->tension;               // tensão segura no Y

        vel.vx += accelX * dt;
        vel.vy += accelY * dt;

        // -----------------------
        // Desgaste natural
        // -----------------------
        kite->durability -= static_cast<float>(dt * 0.02f);

        // -----------------------
        // Limites
        // -----------------------
        kite->tension    = std::clamp(kite->tension, 0.0f, 1.0f);
        kite->durability = std::clamp(kite->durability, 0.0f, 1.0f);
    }
}
