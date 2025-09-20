#include "game/Game.hpp"
#include "engine/Screenshot.hpp"
#include <iostream>
#include <iomanip>

Game::Game(SDL_Window* win)
    : window(win), hud(win) {}

void Game::handleEvent(const SDL_Event& ev, bool& running) {
    if (ev.type == SDL_QUIT) running = false;

    if (ev.type == SDL_KEYDOWN) {
        switch (ev.key.keysym.sym) {
            case SDLK_ESCAPE: running = false; break;
            case SDLK_r: state.reset(); line = Line(); break;
            case SDLK_F12: {
                int w, h;
                SDL_GetWindowSize(window, &w, &h);
                Screenshot::save(w, h);
            } break;
            case SDLK_p: state.paused = !state.paused; break;
        }
    }

    input.handleEvent(ev);
}

void Game::update(double dt) {
    acc += dt;
    elapsedTime += dt;

    hudSystem.update(
        registry,
        hud,
        (dt > 0.0 ? 1.0 / dt : 0.0),
        state.paused,
        debugSystem.isEnabled(),   // ✅ agora passa o debug
        input
    );
}

void Game::render() {
    renderer.clear(0.0f, 0.0f, 0.0f);
    // TODO: renderizar line, kite etc.
    SDL_GL_SwapWindow(window);
}
