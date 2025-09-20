#pragma once
#include <SFML/Graphics.hpp>

// Componente que representa uma pipa controlada pelo ECS
struct KiteComponent {
    // Estado lógico
    float tension{0.f};       // 0..1 intensidade da puxada
    float durability{1.f};    // 0..1 vida útil da pipa
    bool pulling{false};      // se está tensionando

    // Velocidade já existe em Velocity.hpp, este guarda só o shape
    sf::ConvexShape shape;

    KiteComponent() {
        // Modelo losango padrão
        shape.setPointCount(4);
        shape.setPoint(0, {  0.f, -50.f});
        shape.setPoint(1, { 30.f,   0.f});
        shape.setPoint(2, {  0.f,  50.f});
        shape.setPoint(3, {-30.f,   0.f});
        shape.setFillColor(sf::Color(220, 20, 60));
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(2.f);

        // Centralizar origem
        sf::Vector2f c(0.f, 0.f);
        for (size_t i = 0; i < shape.getPointCount(); ++i) {
            c += shape.getPoint(i);
        }
        c.x /= shape.getPointCount();
        c.y /= shape.getPointCount();
        shape.setOrigin(c);
    }
};
