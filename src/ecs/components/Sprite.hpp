#pragma once
#include <string>

struct Sprite {
    std::string path; // caminho da imagem PNG
    int width  = 32;
    int height = 32;
    float scale = 1.0f;
};
