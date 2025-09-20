#pragma once
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <stdexcept>

class Application {
    SDL_Window* window = nullptr;
    SDL_GLContext glctx = nullptr;
    int width, height;

public:
    Application(const char* title, int w, int h) : width(w), height(h) {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
            throw std::runtime_error(SDL_GetError());

        // Cria janela com suporte a OpenGL
        window = SDL_CreateWindow(title,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

        if (!window)
            throw std::runtime_error(SDL_GetError());

        // Cria contexto OpenGL
        glctx = SDL_GL_CreateContext(window);
        SDL_GL_SetSwapInterval(1); // V-Sync ligado

        // Configura viewport e projeção ortográfica
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, w, h, 0, -1, 1); // origem (0,0) no canto superior esquerdo
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // ===========================
        // Habilita transparência (blending)
        // ===========================
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Habilita texturas 2D (pra sprites)
        glEnable(GL_TEXTURE_2D);
    }

    ~Application() {
        SDL_GL_DeleteContext(glctx);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    SDL_Window* getWindow() const { return window; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};
