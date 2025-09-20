#pragma once
#include <GL/gl.h>
#include <vector>
#include <utility>

class Renderer {
    float currentR = 1.0f, currentG = 1.0f, currentB = 1.0f, currentA = 1.0f;

public:
    // ============================
    // Controle de cor
    // ============================
    void setColor(float r, float g, float b, float a = 1.0f) {
        currentR = r; currentG = g; currentB = b; currentA = a;
        glColor4f(r, g, b, a);
    }

    void clear(float r, float g, float b, float a = 1.0f) {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    // ============================
    // Primitivas geométricas
    // ============================
    void drawQuad(float x, float y, float s) {
        glColor4f(currentR, currentG, currentB, currentA);
        glBegin(GL_QUADS);
        glVertex2f(x-s, y-s);
        glVertex2f(x+s, y-s);
        glVertex2f(x+s, y+s);
        glVertex2f(x-s, y+s);
        glEnd();
    }

    void drawLine(float x1, float y1, float x2, float y2) {
        glColor4f(currentR, currentG, currentB, currentA);
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }

    void drawPolyline(const std::vector<std::pair<float,float>>& pts) {
        if (pts.empty()) return;
        glColor4f(currentR, currentG, currentB, currentA);
        glBegin(GL_LINE_STRIP);
        for (const auto& p : pts) {
            glVertex2f(p.first, p.second);
        }
        glEnd();
    }

    void drawCross(float x, float y, float s = 0.05f) {
        glColor4f(currentR, currentG, currentB, currentA);
        glBegin(GL_LINES);
        glVertex2f(x-s, y); glVertex2f(x+s, y);
        glVertex2f(x, y-s); glVertex2f(x, y+s);
        glEnd();
    }

    // ============================
    // Retângulo preenchido (com alfa)
    // ============================
    void fillRect(float x, float y, float w, float h,
                  float r, float g, float b, float a = 1.0f) 
    {
        glColor4f(r, g, b, a);
        glBegin(GL_QUADS);
        glVertex2f(x,     y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x,     y + h);
        glEnd();
    }

    // ============================
    // Sprites
    // ============================
    void drawSprite(GLuint tex, float x, float y, float scale,
                    int width = 32, int height = 32) 
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex);

        float w = width * scale;
        float h = height * scale;

        glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // sprites não usam cor global

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x,   y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x+w, y);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x+w, y+h);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x,   y+h);
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
};
