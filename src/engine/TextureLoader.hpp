#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <stdexcept>

class TextureLoader {
public:
    static GLuint load(const char* path) {
        SDL_Surface* surface = IMG_Load(path);
        if (!surface)
            throw std::runtime_error(IMG_GetError());

        // Garante RGBA
        SDL_Surface* conv = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ABGR8888, 0);
        SDL_FreeSurface(surface);

        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                     conv->w, conv->h, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, conv->pixels);

        SDL_FreeSurface(conv);

        return tex;
    }
};
