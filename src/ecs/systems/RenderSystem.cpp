#include "ecs/systems/RenderSystem.hpp"
#include "ecs/components/Position.hpp"

void RenderSystem::update(Registry& reg, Renderer& renderer) {
    auto positions = reg.view<Position>();
    if (positions.empty()) return;

    // desenha entidades (pipa como cruz verde)
    for (auto& [e, pos] : positions) {
        float size = 0.02f;

        renderer.setColor(0.0f, 1.0f, 0.0f); // verde normalizado
        renderer.drawLine(pos->x - size, pos->y, pos->x + size, pos->y);
        renderer.drawLine(pos->x, pos->y - size, pos->x, pos->y + size);
    }

    // pega a primeira entidade como "pipa"
    auto kitePos = positions.begin()->second;

    // linha da pipa em cinza
    renderer.setColor(0.78f, 0.78f, 0.78f); // cinza claro (200/255)
    renderer.drawLine(0.0f, -0.9f, kitePos->x, kitePos->y);
}
