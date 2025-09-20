#include "KiteEntity.hpp"

KiteEntity::KiteEntity(sf::Vector2f position, sf::Color fill, Model model) {
    if (model == Model::Losango) {
        buildLosango_();
    } else {
        buildRaia_();
    }
    shape_.setFillColor(fill);
    shape_.setOutlineColor(sf::Color::Black);
    shape_.setOutlineThickness(2.f);

    // Centraliza a origem no centro geométrico dos pontos
    shape_.setOrigin(averagePoints_(shape_));

    shape_.setPosition(position);
}

void KiteEntity::buildLosango_() {
    // Losango vetorial (local space)
    shape_.setPointCount(4);
    shape_.setPoint(0, {  0.f, -50.f});
    shape_.setPoint(1, { 30.f,   0.f});
    shape_.setPoint(2, {  0.f,  50.f});
    shape_.setPoint(3, {-30.f,   0.f});
}

void KiteEntity::buildRaia_() {
    // Losango com “rabicho” curto (raia)
    shape_.setPointCount(6);
    shape_.setPoint(0, {  0.f, -55.f});
    shape_.setPoint(1, { 32.f,   0.f});
    shape_.setPoint(2, {  0.f,  42.f});
    shape_.setPoint(3, {-32.f,   0.f});
    shape_.setPoint(4, { -6.f,  58.f});
    shape_.setPoint(5, {  6.f,  58.f});
}

sf::Vector2f KiteEntity::averagePoints_(const sf::ConvexShape& s) {
    sf::Vector2f c{0.f, 0.f};
    const std::size_t n = s.getPointCount();
    if (n == 0) return c;
    for (std::size_t i = 0; i < n; ++i) {
        c.x += s.getPoint(i).x;
        c.y += s.getPoint(i).y;
    }
    c.x /= static_cast<float>(n);
    c.y /= static_cast<float>(n);
    return c;
}

void KiteEntity::update(float dt) {
    // Atrito leve para estabilizar
    velocity_.x *= 0.995f;
    velocity_.y *= 0.995f;

    // Move p/ dt explícito (evita depender de operators do Vector2)
    shape_.move({velocity_.x * dt, velocity_.y * dt});
}

void KiteEntity::draw(sf::RenderTarget& rt) const {
    rt.draw(shape_);
}
