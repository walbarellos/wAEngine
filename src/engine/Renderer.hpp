#pragma once
#include <GL/gl.h>
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>

class Renderer {
    float currentR = 1, currentG = 1, currentB = 1, currentA = 1;
public:
    void setColor(float r, float g, float b, float a = 1.0f);
    void clear(float r, float g, float b, float a = 1.0f);

    void drawQuad(float x, float y, float s);
    void drawLine(float x1, float y1, float x2, float y2);
    void drawPolyline(const std::vector<std::pair<float,float>>& pts);
    void drawCross(float x, float y, float s = 0.05f);
    void fillRect(float x, float y, float w, float h, float r, float g, float b, float a = 1.0f);
    void drawSprite(GLuint tex, float x, float y, float scale, int width = 32, int height = 32);

    // ponte para shapes/textos SFML
    void drawSFML(const sf::Drawable& drawable);
};
