#include "ecs/systems/KiteSystem.hpp"
#include <SDL2/SDL.h>
#include <iostream>

void KiteSystem::update(Registry& reg, Input& input, double dt) {
    // Iterar sobre todas as entidades que têm um componente Kite
    for (auto& [e, kite] : reg.view<Kite>()) {
        auto* pos = reg.get<Position>(e);
        auto* vel = reg.get<Velocity>(e);
        auto* wind = reg.get<Wind>(e);

        if (!pos || !kite) continue;

        // Movimento por input
        if (input.isDown(SDLK_UP))    pos->y += (vel ? vel->vy : 1.0f) * dt;
        if (input.isDown(SDLK_DOWN))  pos->y -= (vel ? vel->vy : 1.0f) * dt;
        if (input.isDown(SDLK_LEFT))  pos->x -= (vel ? vel->vx : 1.0f) * dt;
        if (input.isDown(SDLK_RIGHT)) pos->x += (vel ? vel->vx : 1.0f) * dt;

        // Vento empurrando
        if (wind) pos->x += wind->force * dt;

        // Puxar linha
        kite->pulling = input.isDown(SDLK_SPACE);
        if (kite->pulling) {
            kite->tension += 0.5f * dt;
            kite->durability -= 0.1f * dt;
        } else {
            kite->tension -= 0.2f * dt;
        }

        // Clamp dos valores
        if (kite->tension < 0.0f) kite->tension = 0.0f;
        if (kite->durability < 0.0f) kite->durability = 0.0f;

        // Se a linha quebrou → destruir a pipa
        if (kite->durability <= 0.0f) {
            std::cout << "⚠️ Linha quebrou! Destruindo pipa (Entity " << e << ")\n";
            reg.destroy(e);
        }
    }
}
