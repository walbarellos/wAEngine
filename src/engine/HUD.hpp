// ============================================================================
// File: /mnt/data/SteamLibrary/Engine/src/engine/HUD.hpp
// ============================================================================
#pragma once
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string>
#include <stdexcept>
#include <algorithm>   // ✅ necessário para std::clamp

class HUD {
    TTF_Font*     font = nullptr;
    SDL_Renderer* sdlRenderer = nullptr;
    SDL_Window*   window = nullptr;

public:
    HUD(SDL_Window* win) : window(win) {
        if (TTF_Init() < 0) throw std::runtime_error("Falha ao inicializar SDL_ttf");

        // Se quiser outra fonte, troque o caminho abaixo:
        font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf", 16);
        if (!font) throw std::runtime_error("Fonte não encontrada");

        sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!sdlRenderer) throw std::runtime_error("Falha ao criar SDL_Renderer");

        SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND);
    }

    ~HUD() {
        if (sdlRenderer) SDL_DestroyRenderer(sdlRenderer);
        if (font)        TTF_CloseFont(font);
        TTF_Quit();
    }

    // texto UTF-8 com blending (acentos corretos)
    void drawText(const std::string& text, int x, int y) {
        SDL_Color white = {255,255,255,255};
        SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), white);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);

        SDL_Rect dest = {x, y, surface->w, surface->h};
        SDL_FreeSurface(surface);

        SDL_RenderCopy(sdlRenderer, texture, nullptr, &dest);
        SDL_DestroyTexture(texture);
    }

    void drawBar(float value, int x, int y, int w, int h, SDL_Color color) {
        value = std::clamp(value, 0.0f, 1.0f);  // ✅ agora funciona

        SDL_Rect bg = {x, y, w, h};
        SDL_SetRenderDrawColor(sdlRenderer, 50, 50, 50, 255);
        SDL_RenderFillRect(sdlRenderer, &bg);

        SDL_Rect fg = {x, y, int(w * value), h};
        SDL_SetRenderDrawColor(sdlRenderer, color.r, color.g, color.b, 255);
        SDL_RenderFillRect(sdlRenderer, &fg);
    }

    void present() {
        SDL_RenderPresent(sdlRenderer);
    }

    void clear() {
        SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 0);
        SDL_RenderClear(sdlRenderer);
    }
};
