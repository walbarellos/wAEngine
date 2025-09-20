#pragma once
#include "ecs/Registry.hpp"
#include "engine/Renderer.hpp"
#include "ecs/components/Position.hpp"
#include "ecs/components/Renderable.hpp"
#include "ecs/components/Sprite.hpp"
#include "engine/TextureManager.hpp"
#include <SDL2/SDL.h>

class RenderSystem {
public:
    void update(Registry& reg, Renderer& renderer);
};
