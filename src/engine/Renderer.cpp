#include "Renderer.hpp"
#include <GL/gl.h>
#include <stdexcept>
#include <memory>

// ----------------------------
// Implementação de clear()
// ----------------------------
void Renderer::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// ----------------------------
// Geometria OpenGL imediata
// ----------------------------
void Renderer::drawQuad(float x, float y, float s) {
    glColor4f(currentR, currentG, currentB, currentA);
    glBegin(GL_QUADS);
        glVertex2f(x - s, y - s);
        glVertex2f(x + s, y - s);
        glVertex2f(x + s, y + s);
        glVertex2f(x - s, y + s);
    glEnd();
}

void Renderer::drawLine(float x1, float y1, float x2, float y2) {
    glColor4f(currentR, currentG, currentB, currentA);
    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

void Renderer::drawPolyline(const std::vector<std::pair<float,float>>& pts) {
    if (pts.empty()) return;
    glColor4f(currentR, currentG, currentB, currentA);
    glBegin(GL_LINE_STRIP);
    for (const auto& p : pts) {
        glVertex2f(p.first, p.second);
    }
    glEnd();
}

void Renderer::drawCross(float x, float y, float s) {
    glColor4f(currentR, currentG, currentB, currentA);
    glBegin(GL_LINES);
        glVertex2f(x - s, y); glVertex2f(x + s, y);
        glVertex2f(x, y - s); glVertex2f(x, y + s);
    glEnd();
}

void Renderer::fillRect(float x, float y, float w, float h,
                        float r, float g, float b, float a) {
    glColor4f(r, g, b, a);
    glBegin(GL_QUADS);
        glVertex2f(x,     y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x,     y + h);
    glEnd();
}

void Renderer::drawSprite(GLuint tex, float x, float y, float scale,
                          int width, int height) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);

    float w = width * scale;
    float h = height * scale;

    // sprites ignoram cor global
    glColor4f(1.f, 1.f, 1.f, 1.f);

    glBegin(GL_QUADS);
        glTexCoord2f(0.f, 0.f); glVertex2f(x,   y);
        glTexCoord2f(1.f, 0.f); glVertex2f(x+w, y);
        glTexCoord2f(1.f, 1.f); glVertex2f(x+w, y+h);
        glTexCoord2f(0.f, 1.f); glVertex2f(x,   y+h);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// ----------------------------
// Integração SFML
// ----------------------------
void Renderer::drawSFML(const sf::Drawable& drawable) {
    // Em SFML 3, RenderTexture é criado pelo construtor
    static std::unique_ptr<sf::RenderTexture> rt;

    if (!rt) {
        rt = std::make_unique<sf::RenderTexture>(sf::Vector2u{1280, 720});
        if (!rt) {
            throw std::runtime_error("Falha ao criar RenderTexture (SFML 3.x)");
        }
    }

    rt->clear(sf::Color::Transparent);
    rt->draw(drawable);
    rt->display();

    GLuint texId = rt->getTexture().getNativeHandle();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);
    glBegin(GL_QUADS);
        glTexCoord2f(0.f, 0.f); glVertex2f(-1.f, -1.f);
        glTexCoord2f(1.f, 0.f); glVertex2f( 1.f, -1.f);
        glTexCoord2f(1.f, 1.f); glVertex2f( 1.f,  1.f);
        glTexCoord2f(0.f, 1.f); glVertex2f(-1.f,  1.f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
