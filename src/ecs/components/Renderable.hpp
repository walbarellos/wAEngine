#pragma once
#include <variant>
#include <SFML/Graphics.hpp>

// Componente que marca que a entidade pode ser renderizada
struct Renderable {
    std::variant<std::monostate, sf::ConvexShape*, sf::Sprite*, sf::Text*> drawable;

    Renderable() = default;
    explicit Renderable(sf::ConvexShape* shape) : drawable(shape) {}
    explicit Renderable(sf::Sprite* sprite) : drawable(sprite) {}
    explicit Renderable(sf::Text* text) : drawable(text) {}
};
