#include "ecs/debug/DebugSystem.hpp"
#include "ecs/components/Renderable.hpp"

DebugSystem::DebugSystem()
: text(font, "", 16) // SFML 3: Text(font, string, size)
{
    // use uma fonte sua em assets/ (ou troque o path)
    if (!font.openFromFile("assets/DejaVuSans.ttf")) {
        // se não achar, segue sem HUD
    }
    text.setFillColor(sf::Color::Green);
}

void DebugSystem::update(Registry& reg, Renderer& renderer, Clock& clock) {
    if (!enabled && !dumpOnce) return;

    // sem getFPS: calcula pelo delta
    float fps = 1.f / static_cast<float>(clock.delta());
    int entities = static_cast<int>(reg.countEntities());

    text.setString(
        "FPS: " + std::to_string(static_cast<int>(fps)) +
        "\nEntidades: " + std::to_string(entities)
    );
    text.setPosition({10.f, 10.f});

    renderer.drawSFML(text);

    if (dumpOnce) dumpOnce = false;
}
