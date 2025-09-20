// ============================================================================
// File: /mnt/data/SteamLibrary/Engine/src/ecs/systems/HudSystem.hpp
// ============================================================================
#pragma once
#include "ecs/Registry.hpp"
#include "engine/HUD.hpp"
#include "engine/Input.hpp"
#include "ecs/components/Kite.hpp"
#include "ecs/components/Wind.hpp"
#include <SDL2/SDL.h>

class HudSystem {
public:
    enum Mode { Compact, Full };

    // Mantém a mesma assinatura usada no main
    void update(Registry& reg, HUD& hud, double fps, bool paused, bool debugEnabled, Input& input);

private:
    // valores suavizados
    float durabilitySmoothed = 1.0f;
    float tensionSmoothed    = 0.0f;
    float windSmoothed       = 0.0f;
    float energySmoothed     = 0.0f;

    Mode mode = Full; // padrão

    SDL_Color colorGradient(float percent, SDL_Color low, SDL_Color high);
};
