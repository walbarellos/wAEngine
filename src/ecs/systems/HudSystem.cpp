// ============================================================================
// File: /mnt/data/SteamLibrary/Engine/src/ecs/systems/HudSystem.cpp
// ============================================================================
#include "ecs/systems/HudSystem.hpp"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath> // std::lerp

SDL_Color HudSystem::colorGradient(float percent, SDL_Color low, SDL_Color high) {
    auto lerp8 = [](Uint8 a, Uint8 b, float t)->Uint8 { return static_cast<Uint8>(a + (b - a) * t); };
    percent = std::clamp(percent, 0.0f, 1.0f);
    return SDL_Color{
        lerp8(low.r,  high.r,  percent),
        lerp8(low.g,  high.g,  percent),
        lerp8(low.b,  high.b,  percent),
        255
    };
}

void HudSystem::update(Registry& reg, HUD& hud, double fps, bool paused, bool debugEnabled, Input& input) {
    // Toggle de modo (edge detection em H)
    static bool prevH = false;
    bool hNow = input.isDown(SDLK_h);
    if (hNow && !prevH) {
        mode = (mode == Full ? Compact : Full);
    }
    prevH = hNow;

    // Pega componentes por ENDEREÇO seguro dentro do Registry
    Kite* kite = nullptr;
    Wind* wind = nullptr;
    for (auto& [e, k] : reg.view<Kite>()) { kite = &reg.getComponent<Kite>(e); break; }
    for (auto& [e, w] : reg.view<Wind>()) { wind = &reg.getComponent<Wind>(e); break; }

    hud.clear();

    if (!kite || !wind) {
        hud.drawText("HUD: entidades ausentes", 10, 20);
        hud.present();
        return;
    }

    float durability = std::clamp(kite->durability, 0.0f, 1.0f);
    float tension    = std::clamp(kite->tension,    0.0f, 1.0f);
    float windForce  = std::clamp((wind->force + 1.0f) * 0.5f, 0.0f, 1.0f);
    float energy     = std::clamp(0.5f * kite->tension + 0.5f * durability, 0.0f, 1.0f);

    // Suavização
    const float t = 0.15f;
    durabilitySmoothed = std::lerp(durabilitySmoothed, durability, t);
    tensionSmoothed    = std::lerp(tensionSmoothed,    tension,    t);
    windSmoothed       = std::lerp(windSmoothed,       windForce,  t);
    energySmoothed     = std::lerp(energySmoothed,     energy,     t);

    // Layout
    int x = 10, y = 20, wBar = 200, hBar = 20, line = 24;

    if (mode == Full) {
        hud.drawBar(durabilitySmoothed, x, y, wBar, hBar,
                    colorGradient(durabilitySmoothed, {255,0,0,255}, {0,255,0,255}));
        hud.drawText("Durabilidade", x + wBar + 20, y);
        y += line;

        hud.drawBar(tensionSmoothed, x, y, wBar, hBar,
                    colorGradient(tensionSmoothed, {0,0,128,255}, {0,128,255,255}));
        hud.drawText("Tensao", x + wBar + 20, y);
        y += line;

        hud.drawBar(windSmoothed, x, y, wBar, hBar, {0,255,255,255});
        hud.drawText("Vento", x + wBar + 20, y);
        y += line;

        hud.drawBar(energySmoothed, x, y, wBar, hBar, {255,200,0,255});
        hud.drawText("Energia", x + wBar + 20, y);
        y += line + 10;
    } else { // Compact
        hud.drawBar(energySmoothed, x, y, wBar, hBar, {255,200,0,255});
        std::ostringstream s;
        s << "D:" << int(durabilitySmoothed*100)
          << "%  T:" << int(tensionSmoothed*100)
          << "%  W:" << int(windSmoothed*100) << "%";
        hud.drawText(s.str(), x + wBar + 20, y);
        y += line + 10;
    }

    // Rodapé
    hud.drawText("FPS: " + std::to_string(static_cast<int>(fps + 0.5)), x, y);
    hud.drawText(paused ? "PAUSADO" : "RODANDO", x + 120, y);
    if (debugEnabled) hud.drawText("DEBUG ON", x, y + line);

    hud.present();
}
