#include "ecs/systems/RenderSystem.hpp"
#include "ecs/Registry.hpp"
#include "ecs/components/Renderable.hpp"
#include "engine/Renderer.hpp"
#include <SFML/Graphics.hpp>

void RenderSystem::update(Registry& reg, Renderer& renderer) {
    auto rs = reg.view<Renderable>();
    for (auto& [e, rend] : rs) {
        if (!rend) continue;

        // suportes básicos
        if (auto p = std::get_if<sf::ConvexShape*>(&rend->drawable)) {
            if (*p) renderer.drawSFML(**p);
        } else if (auto sp = std::get_if<sf::Sprite*>(&rend->drawable)) {
            if (*sp) renderer.drawSFML(**sp);
        } else if (auto tp = std::get_if<sf::Text*>(&rend->drawable)) {
            if (*tp) renderer.drawSFML(**tp);
        }
    }
}
