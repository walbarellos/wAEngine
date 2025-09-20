#pragma once
#include <GL/gl.h>
#include <string>
#include <map>
#include <stdexcept>

class TextureManager {
    inline static std::map<std::string, GLuint> textures;

public:
    static GLuint load(const std::string& path);
    static void unloadAll();
};
