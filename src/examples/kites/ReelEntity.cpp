#include "ReelEntity.hpp"

ReelEntity::ReelEntity(sf::Vector2f position) {
    // Base retangular (madeira)
    base_.setSize({22.f, 42.f});
    base_.setFillColor(sf::Color(139, 69, 19)); // marrom
    base_.setOrigin({base_.getSize().x * 0.5f, base_.getSize().y * 0.5f});
    base_.setPosition(position);

    // Núcleo (carretel)
    core_.setRadius(11.f);
    core_.setOrigin({core_.getRadius(), core_.getRadius()});
    core_.setFillColor(sf::Color(40, 40, 40));
    core_.setPosition({position.x, position.y + coreYOffset_});
}

void ReelEntity::update(float dt) {
    if (angularSpeed_ != 0.f) {
        angle_ += angularSpeed_ * dt;
        core_.setRotation(sf::degrees(angle_));
    }
}

void ReelEntity::draw(sf::RenderTarget& rt) const {
    rt.draw(base_);
    rt.draw(core_);
}
