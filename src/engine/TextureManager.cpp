#include "engine/TextureManager.hpp"

// stb_image deve ser implementado em um único .cpp
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdexcept>
#include <iostream>

GLuint TextureManager::load(const std::string& path) {
    // Se já carregamos esta textura, retorna cache
    if (textures.count(path)) return textures[path];

    int w, h, channels;
    stbi_set_flip_vertically_on_load(true); // vira textura (OpenGL usa origem no canto inferior)
    unsigned char* data = stbi_load(path.c_str(), &w, &h, &channels, STBI_rgb_alpha);

    if (!data) {
        throw std::runtime_error(
            "Erro ao carregar sprite: " + path + " | Motivo: " + std::string(stbi_failure_reason())
        );
    }

    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    // Garante alinhamento correto
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, data);

    // Filtros – atualmente NEAREST (pixel art)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Se quiser mipmaps (textura redimensionada):
    // glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    textures[path] = texID;

    std::cout << "[TextureManager] Carregado: " << path
              << " (" << w << "x" << h << ")\n";

    return texID;
}

void TextureManager::unloadAll() {
    for (auto& [path, id] : textures) {
        glDeleteTextures(1, &id);
    }
    textures.clear();
    std::cout << "[TextureManager] Todas as texturas foram liberadas.\n";
}
