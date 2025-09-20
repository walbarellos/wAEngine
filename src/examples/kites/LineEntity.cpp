#include "LineEntity.hpp"
#include <cmath>

LineEntity::LineEntity()
: line_(sf::PrimitiveType::LineStrip, 2) {
    line_[0].color = sf::Color::White;
    line_[1].color = sf::Color::White;
}

void LineEntity::setEndpoints(sf::Vector2f start, sf::Vector2f end) {
    line_[0].position = start;
    line_[1].position = end;
    currentLength_ = distance(start, end);
}

void LineEntity::update(float) {
    // Futuro: curvatura pelo vento (Bezier) ou segmentação
}

void LineEntity::draw(sf::RenderTarget& rt) const {
    rt.draw(line_);
}

float LineEntity::distance(sf::Vector2f a, sf::Vector2f b) {
    const float dx = b.x - a.x;
    const float dy = b.y - a.y;
    return std::sqrt(dx*dx + dy*dy);
}
