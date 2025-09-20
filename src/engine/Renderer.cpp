#include "Renderer.hpp"
#include <GL/gl.h> // depende do teu include path

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
