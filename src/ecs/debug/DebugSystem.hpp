#pragma once
#include "ecs/Registry.hpp"
#include "engine/Renderer.hpp"
#include "core/Clock.hpp"
#include <SFML/Graphics.hpp>

class DebugSystem {
public:
    DebugSystem();

    void update(Registry& reg, Renderer& renderer, Clock& clock);

    void toggle() { enabled = !enabled; }
    bool isEnabled() const { return enabled; }
    void requestDumpOnce() { dumpOnce = true; }

private:
    bool enabled      = true;
    bool dumpOnce     = false;
    int  frameCounter = 0;

    sf::Font font;
    sf::Text text; // sfml3: precisa de font no ctor (feito no .cpp)
};
