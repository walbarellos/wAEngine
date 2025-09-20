// src/ecs/systems/RenderSystem.cpp
#include "ecs/systems/RenderSystem.hpp"
#include <sstream>
#include <iomanip>

void RenderSystem::update(Registry& reg, Renderer& renderer, HUD& hud, double fps, bool paused) {
    renderer.clear(0.1f, 0.1f, 0.15f);

    // Desenhar entidades com Position + Renderable
    auto view = reg.view<Position>();
    for (auto& [e, pos] : view) {
        if (reg.hasComponent<Renderable>(e)) {
            auto& rend = reg.getComponent<Renderable>(e);
            renderer.setColor(rend.r, rend.g, rend.b);
            renderer.drawQuad(pos->x, pos->y, rend.size);
        }
    }

    // HUD básico
    hud.clear();
    std::ostringstream oss;
    oss << "FPS: " << std::fixed << std::setprecision(1) << fps;
    if (paused) oss << " [PAUSED]";
    hud.drawText(oss.str(), 10, 10);
    hud.present();
}
