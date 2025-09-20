#pragma once
#include <string>
#include <GL/gl.h>

class TextureLoader {
public:
    static GLuint load(const std::string& path);
};
