#pragma once
#include <SFML/Graphics.hpp>

class ReelEntity {
public:
    explicit ReelEntity(sf::Vector2f position);

    sf::Vector2f getPosition() const { return base_.getPosition(); }
    void setPosition(sf::Vector2f p) {
        base_.setPosition(p);
        core_.setPosition({p.x, p.y + coreYOffset_});
    }

    // Anima rotação do carretel conforme tensão/ação
    void setAngularSpeed(float degPerSec) { angularSpeed_ = degPerSec; }

    void update(float dt);
    void draw(sf::RenderTarget& rt) const;

private:
    sf::RectangleShape base_;
    sf::CircleShape core_;
    float coreYOffset_{10.f};
    float angle_{0.f};          // graus
    float angularSpeed_{0.f};   // graus/segundo
};
