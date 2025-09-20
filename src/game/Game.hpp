#pragma once
#include "core/Clock.hpp"
#include "engine/Renderer.hpp"
#include "engine/Input.hpp"
#include "engine/HUD.hpp"
#include "engine/Screenshot.hpp"
#include "game/Line.hpp"
#include "game/WindGenerator.hpp"
#include "game/LineShape.hpp"
#include "ecs/systems/HudSystem.hpp"
#include "ecs/debug/DebugSystem.hpp"   // ✅ agora incluímos o DebugSystem
#include "core/GameState.hpp"

#include <SDL2/SDL.h>
#include <string>

// =============================
// Configuração do jogo
// =============================
struct GameConfig {
    static constexpr double FIXED_DT = 1.0 / 120.0;
    static constexpr float kiteSpeed = 1.5f;
    static constexpr float spoolX = 0.0f;
    static constexpr float spoolY = -0.9f;

    static constexpr int lineSegments = 25;
    static constexpr LineShape::CurveType lineCurve = LineShape::CurveType::Parabola;

    // HUD layout
    static constexpr int hudX = 10;
    static constexpr int hudY = 10;
    static constexpr int hudW = 200;
    static constexpr int hudH = 12;
};

class Game {
    SDL_Window* window;
    HUD hud;
    HudSystem hudSystem;
    Renderer renderer;
    Registry registry;
    Input input;

    Line line;
    WindGenerator wind;
    GameState state;

    DebugSystem debugSystem;   // ✅ agora Game possui DebugSystem

    double acc = 0.0;
    double elapsedTime = 0.0;

public:
    explicit Game(SDL_Window* window);
    void handleEvent(const SDL_Event& ev, bool& running);
    void update(double dt);
    void render();
};
