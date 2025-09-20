#pragma once
#include <SFML/Graphics.hpp>

class KiteEntity {
public:
    enum class Model { Losango, Raia };

    explicit KiteEntity(sf::Vector2f position, sf::Color fill, Model model = Model::Losango);

    void setVelocity(sf::Vector2f v) { velocity_ = v; }
    sf::Vector2f getPosition() const { return shape_.getPosition(); }
    void setPosition(sf::Vector2f p) { shape_.setPosition(p); }

    // Rotação na API do SFML 3 usa sf::Angle
    void setRotation(float deg) { shape_.setRotation(sf::degrees(deg)); }
    void rotate(float deg) { shape_.rotate(sf::degrees(deg)); }

    // “Força” simples para alterar a velocidade (acumula)
    void addForce(sf::Vector2f f) { velocity_.x += f.x; velocity_.y += f.y; }

    void update(float dt);
    void draw(sf::RenderTarget& rt) const;

private:
    sf::ConvexShape shape_;
    sf::Vector2f velocity_{0.f, 0.f};

    void buildLosango_();
    void buildRaia_();
    static sf::Vector2f averagePoints_(const sf::ConvexShape& s);
};
